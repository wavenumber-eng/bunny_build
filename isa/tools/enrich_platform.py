"""Extract compact EZH/SmartDMA platform enrichment from nxp-monkey mirrors.

Usage:
    uv run python isa/tools/enrich_platform.py --part MCXN947 --fetch
    uv run python isa/tools/enrich_platform.py --part MCXN947 --input build/nxp-monkey-probe
    uv run python isa/tools/enrich_platform.py --part MCXN947 --check --input build/nxp-monkey-probe

This is stage 3 of the platform-data pipeline. It does not commit the raw
MCUXpresso Config Tools tree; it consumes the JSON mirror produced by
nxp-monkey and writes the small public facts the static guide needs.
"""

from __future__ import annotations

import argparse
import json
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[2]
DEFAULT_INPUT = ROOT / "build" / "nxp-monkey-enrich"
DEFAULT_OUT = ROOT / "isa" / "ezh_b" / "platform_enrichment"
SENTINEL = ".ezh-platform-enrichment-generated"
GENERATOR = "isa/tools/enrich_platform.py"

MIRROR_PATTERNS = [
    "**/registers/SMARTDMA0.xml",
    "**/registers/INPUTMUX0.xml",
    "**/signal_configuration.xml",
    "**/resource_tables/interrupts.xml",
]


class EnrichmentError(RuntimeError):
    """Raised when chip-data enrichment cannot complete."""


def as_list(value: Any) -> list[Any]:
    if value is None:
        return []
    if isinstance(value, list):
        return value
    return [value]


def load_json(path: Path) -> Any:
    return json.loads(path.read_text(encoding="utf-8"))


def json_text(data: Any) -> str:
    return json.dumps(data, indent=2, sort_keys=True) + "\n"


def write_text(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8", newline="\n")


def parse_int(value: Any) -> int | None:
    if value is None:
        return None
    if isinstance(value, int):
        return value
    text = str(value).strip()
    if not text:
        return None
    return int(text, 0)


def format_hex(value: int | None) -> str:
    if value is None:
        return ""
    return f"0x{value:X}"


def short_path(path: Path, root: Path) -> str:
    return str(path.relative_to(root)).replace("\\", "/")


def nxp_monkey_version() -> str:
    cmd = ["nxp-monkey", "--version"]
    try:
        completed = subprocess.run(cmd, check=True, capture_output=True, text=True)
    except (OSError, subprocess.CalledProcessError):
        return ""
    return completed.stdout.strip()


def run_fetch(part: str, variant: str, work_dir: Path) -> None:
    cmd = [
        "nxp-monkey",
        "fetch",
        part,
        "--variant",
        variant,
        "--output",
        str(work_dir),
    ]
    for pattern in MIRROR_PATTERNS:
        cmd.extend(["--json-mirror-only", pattern])
    subprocess.run(cmd, cwd=ROOT, check=True)


def part_json_root(input_dir: Path, part: str) -> Path:
    candidates = [
        input_dir / part / "json",
        input_dir / part,
        input_dir,
    ]
    for candidate in candidates:
        if (candidate / f"{part}.json").is_file():
            return candidate
    raise EnrichmentError(
        f"cannot find nxp-monkey JSON mirror for {part} under {input_dir}"
    )


def find_one(root: Path, pattern: str, label: str) -> Path:
    matches = sorted(root.glob(pattern))
    if not matches:
        raise EnrichmentError(f"missing {label} in {root}")
    return matches[0]


def extract_fields(register: dict[str, Any]) -> list[dict[str, Any]]:
    fields: list[dict[str, Any]] = []
    for kind, name_default in (
        ("reserved_bit_field", "RESERVED"),
        ("bit_field", ""),
    ):
        for field in as_list(register.get(kind)):
            offset = parse_int(field.get("@offset"))
            width = parse_int(field.get("@width"))
            item = {
                "name": field.get("@name") or name_default,
                "offset": offset,
                "width": width,
                "bit_range": bit_range(offset, width),
                "kind": "reserved" if kind == "reserved_bit_field" else "field",
            }
            if "@access" in field:
                item["access"] = field.get("@access")
            if "@reset_value" in field:
                item["reset"] = field.get("@reset_value")
            if "@description" in field:
                item["description"] = field.get("@description")
            fields.append(item)
    return sorted(fields, key=lambda item: (item.get("offset") or 0, item["name"]))


def bit_range(offset: int | None, width: int | None) -> str:
    if offset is None or width is None:
        return ""
    if width == 1:
        return str(offset)
    return f"{offset + width - 1}:{offset}"


def extract_register_block(path: Path, json_root: Path) -> dict[str, Any]:
    peripheral = load_json(path).get("peripheral", {})
    registers = []
    for register in as_list(peripheral.get("register")):
        offset = parse_int(register.get("@offset"))
        registers.append(
            {
                "name": register.get("@name"),
                "offset": format_hex(offset),
                "offset_int": offset,
                "width": parse_int(register.get("@width")),
                "description": register.get("@description", ""),
                "fields": extract_fields(register),
            }
        )
    registers.sort(key=lambda item: (item.get("offset_int") or 0, item.get("name") or ""))
    return {
        "peripheral": "SMARTDMA0",
        "source": short_path(path, json_root),
        "register_count": len(registers),
        "registers": registers,
    }


def substitute_template(text: str, values: list[str]) -> str:
    out = text
    for index, value in enumerate(values):
        out = out.replace("{" + str(index) + "}", value)
    return out


def inputmux_template(peripheral: dict[str, Any]) -> dict[str, Any]:
    for template in as_list(peripheral.get("reg_template")):
        if str(template.get("@name", "")).startswith("SMARTDMAARCHB_INMUX"):
            return template
    raise EnrichmentError("INPUTMUX0.json has no SMARTDMAARCHB_INMUX template")


def extract_inputmux(path: Path, json_root: Path) -> dict[str, Any]:
    peripheral = load_json(path).get("peripheral", {})
    template = inputmux_template(peripheral)
    template_id = str(template.get("@rid"))
    field = as_list(template.get("bit_field"))[0]

    instances = []
    for instance in as_list(peripheral.get("reg_instance")):
        if str(instance.get("@rid")) != template_id:
            continue
        values = str(instance.get("@vals", "")).split()
        offset = parse_int(values[0]) if values else None
        channel = parse_int(values[1]) if len(values) > 1 else None
        instances.append(
            {
                "register": substitute_template(str(template.get("@name", "")), values),
                "offset": format_hex(offset),
                "offset_int": offset,
                "channel": channel,
            }
        )
    instances.sort(key=lambda item: (item.get("channel") or 0, item.get("offset_int") or 0))

    values = []
    for entry in as_list(field.get("bit_field_value")):
        raw_value = parse_int(entry.get("@value"))
        description = entry.get("@description", "")
        values.append(
            {
                "name": entry.get("@name", ""),
                "value": format_hex(raw_value),
                "value_int": raw_value,
                "description": description,
                "reserved": description.strip().lower() == "reserved",
            }
        )
    values.sort(key=lambda item: (item.get("value_int") if item.get("value_int") is not None else -1))

    return {
        "peripheral": "INPUTMUX0",
        "source": short_path(path, json_root),
        "register_template": template.get("@name"),
        "description": template.get("@description", ""),
        "field": {
            "name": field.get("@name"),
            "bit_range": bit_range(parse_int(field.get("@offset")), parse_int(field.get("@width"))),
            "width": parse_int(field.get("@width")),
            "reset": field.get("@reset_value"),
            "description": field.get("@description", ""),
        },
        "input_count": len(instances),
        "instances": instances,
        "value_count": len(values),
        "reserved_value_count": sum(1 for item in values if item["reserved"]),
        "values": values,
    }


def package_info(signal_configuration: dict[str, Any], package_id: str) -> dict[str, Any]:
    part_number = signal_configuration.get("part_information", {}).get("part_number", {})
    return {
        "package_id": package_id,
        "part_number": part_number.get("@id", package_id),
        "pin_count": parse_int(part_number.get("@pins")),
        "package": part_number.get("package", ""),
    }


def pin_label(pin_name: str) -> str:
    return pin_name.split("/", 1)[0]


def iter_pin_connections(pin: dict[str, Any]) -> list[dict[str, Any]]:
    connections = pin.get("connections")
    wrappers: list[Any]
    if isinstance(connections, dict) and "connection" in connections:
        wrappers = [{"connection": connections.get("connection")}]
    else:
        wrappers = as_list(connections)

    out: list[dict[str, Any]] = []
    for wrapper in wrappers:
        if not isinstance(wrapper, dict):
            continue
        for connection in as_list(wrapper.get("connection")):
            if isinstance(connection, dict):
                out.append(
                    {
                        "name_part": wrapper.get("@name_part", ""),
                        "package_function": wrapper.get("@package_function", ""),
                        "connection": connection,
                    }
                )
    return out


def collect_assigns(value: Any) -> list[dict[str, Any]]:
    assigns: list[dict[str, Any]] = []
    if isinstance(value, dict):
        if "assign" in value:
            assigns.extend(item for item in as_list(value["assign"]) if isinstance(item, dict))
        for key, child in value.items():
            if key == "assign":
                continue
            assigns.extend(collect_assigns(child))
    elif isinstance(value, list):
        for child in value:
            assigns.extend(collect_assigns(child))
    return assigns


def mux_assignments(configuration: Any) -> dict[str, Any]:
    assignments = collect_assigns(configuration)
    mux = next((item for item in assignments if item.get("@bit_field") == "MUX"), None)
    ibe = next((item for item in assignments if item.get("@bit_field") == "IBE"), None)
    return {
        "mux_register": mux.get("@register", "") if mux else "",
        "mux_value": mux.get("@bit_field_value", "") if mux else "",
        "input_buffer_register": ibe.get("@register", "") if ibe else "",
        "input_buffer_value": ibe.get("@bit_field_value", "") if ibe else "",
    }


def extract_package_pin_mux(path: Path, variant_root: Path) -> dict[str, Any]:
    package_id = path.parent.name
    signal_configuration = load_json(path).get("signal_configuration", {})
    package = package_info(signal_configuration, package_id)
    options = []

    pins = as_list(signal_configuration.get("pins", {}).get("pin"))
    for pin in pins:
        pin_name = pin.get("@name", "")
        for item in iter_pin_connections(pin):
            connection = item["connection"]
            ref = connection.get("peripheral_signal_ref", {})
            if ref.get("@peripheral") != "SMARTDMA0" or ref.get("@signal") != "SMARTDMA_PIO":
                continue
            channel = parse_int(ref.get("@channel"))
            option = {
                "signal": f"SMARTDMA_PIO{channel}" if channel is not None else "SMARTDMA_PIO",
                "channel": channel,
                "pin": pin_label(pin_name),
                "package_pin": pin.get("@coords", ""),
                "package_function": item.get("package_function", ""),
                "name_part": item.get("name_part", ""),
                **mux_assignments(connection.get("configuration")),
            }
            options.append(option)

    options.sort(
        key=lambda item: (
            item.get("channel") if item.get("channel") is not None else -1,
            item.get("pin") or "",
            item.get("package_pin") or "",
        )
    )
    package["source"] = short_path(path, variant_root.parent)
    package["option_count"] = len(options)
    package["signals"] = sorted(
        {item["signal"] for item in options},
        key=lambda name: parse_int(name.removeprefix("SMARTDMA_PIO")) or -1,
    )
    package["options"] = options
    return package


def extract_pin_mux(variant_root: Path, json_root: Path) -> dict[str, Any]:
    packages = []
    for path in sorted(variant_root.glob("*/signal_configuration.json")):
        packages.append(extract_package_pin_mux(path, variant_root))
    return {
        "source_root": short_path(variant_root, json_root),
        "package_count": len(packages),
        "option_count": sum(package["option_count"] for package in packages),
        "packages": packages,
    }


def extract_part(input_dir: Path, part: str, variant: str) -> dict[str, Any]:
    json_root = part_json_root(input_dir, part)
    details = load_json(json_root / f"{part}.json").get("details", {})
    variant_root = json_root / variant
    if not variant_root.is_dir():
        raise EnrichmentError(f"{part}: missing variant mirror {variant_root}")

    smartdma_path = find_one(variant_root, "*/registers/SMARTDMA0.json", "SMARTDMA0.json")
    inputmux_path = find_one(variant_root, "*/registers/INPUTMUX0.json", "INPUTMUX0.json")

    return {
        "schema": "ezh-platform-chipdata-enrichment-v1",
        "generator": GENERATOR,
        "source": "NXP MCUXpresso Config Tools chip data via nxp-monkey",
        "nxp_monkey_version": nxp_monkey_version(),
        "part": part,
        "variant": variant,
        "tool_data_version": details.get("version", ""),
        "default_part": details.get("header", {}).get("default_part", ""),
        "register_block": extract_register_block(smartdma_path, json_root),
        "inputmux": extract_inputmux(inputmux_path, json_root),
        "pin_mux": extract_pin_mux(variant_root, json_root),
    }


def guard_output_dir(out_dir: Path) -> Path:
    resolved = out_dir.resolve()
    default = DEFAULT_OUT.resolve()
    if resolved != default and not (resolved / SENTINEL).exists():
        raise EnrichmentError(
            f"refusing to write non-default output without {SENTINEL}: {out_dir}"
        )
    return resolved


def write_outputs(out_dir: Path, records: list[dict[str, Any]]) -> None:
    out_dir = guard_output_dir(out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    write_text(out_dir / SENTINEL, "Generated by isa/tools/enrich_platform.py; safe to replace.\n")
    for record in records:
        write_text(out_dir / f"{record['part']}.json", json_text(record))


def check_outputs(out_dir: Path, records: list[dict[str, Any]]) -> None:
    with tempfile.TemporaryDirectory(prefix="ezh-platform-enrich-") as tmp:
        temp_out = Path(tmp)
        write_text(temp_out / SENTINEL, "Generated by isa/tools/enrich_platform.py; safe to replace.\n")
        for record in records:
            write_text(temp_out / f"{record['part']}.json", json_text(record))

        expected = {path.name: path.read_text(encoding="utf-8") for path in temp_out.iterdir()}
        actual = {
            path.name: path.read_text(encoding="utf-8")
            for path in out_dir.iterdir()
            if path.is_file() and (path.name == SENTINEL or path.suffix == ".json")
        }
        if expected != actual:
            raise EnrichmentError(f"platform enrichment output is stale: {out_dir}")


def parse_args(argv: list[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--part", action="append", required=True, help="Part to enrich; repeatable")
    parser.add_argument("--variant", default="ksdk2_0", help="nxp-monkey SDK variant")
    parser.add_argument("--input", type=Path, default=DEFAULT_INPUT, help="nxp-monkey output root")
    parser.add_argument("--out", type=Path, default=DEFAULT_OUT, help="compact enrichment output root")
    parser.add_argument("--fetch", action="store_true", help="run nxp-monkey fetch before extracting")
    parser.add_argument("--check", action="store_true", help="fail if committed enrichment is stale")
    return parser.parse_args(argv)


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv or sys.argv[1:])
    try:
        input_dir = args.input.resolve()
        if args.fetch:
            for part in args.part:
                run_fetch(part, args.variant, input_dir)
        records = [extract_part(input_dir, part, args.variant) for part in args.part]
        if args.check:
            check_outputs(args.out, records)
            print(f"Platform enrichment is current: {len(records)} part(s).")
        else:
            write_outputs(args.out, records)
            print(f"Wrote platform enrichment: {len(records)} part(s) to {args.out}")
    except (EnrichmentError, subprocess.CalledProcessError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
