"""Discover EZH/SmartDMA platform facts from pinned MCUXpresso SDK headers.

Usage:
    uv run python isa/tools/discover_parts.py
    uv run python isa/tools/discover_parts.py --self-test
    uv run python isa/tools/discover_parts.py --check
    uv run python isa/tools/discover_parts.py --require-complete

This is stage 1/2 of the platform-data pipeline. It follows the pinned
mcuxsdk-manifests device submanifests, scans feature headers for EZH/SmartDMA
presence, then extracts IRQ and base-address facts from the matching COMMON
headers. Pin mux and INPUTMUX enrichment are intentionally left for the later
nxp-monkey stage.
"""

from __future__ import annotations

import argparse
from functools import lru_cache
import json
import re
import shutil
import sys
import tempfile
import urllib.error
import urllib.request
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[2]
DEFAULT_OUT = ROOT / "isa" / "ezh_b" / "platform"
SENTINEL = ".ezh-platform-generated"

MANIFEST_REPO = "nxp-mcuxpresso/mcuxsdk-manifests"
DEFAULT_MANIFEST_REV = "d00fe90aef626b082bbd0a5358620625c9297afb"
DEVICE_MANIFESTS = {
    "MCX": "submanifests/devices/MCX.yml",
    "LPC": "submanifests/devices/LPC.yml",
    "RT": "submanifests/devices/RT.yml",
}

SMARTDMA_COUNT_RE = re.compile(
    r"(?m)^\s*#define\s+FSL_FEATURE_SOC_SMARTDMA_COUNT\s+\((\d+)\)"
)
EZH_COUNT_RE = re.compile(
    r"(?m)^\s*#define\s+(FSL_FEATURE_SOC_EZH\w*_COUNT)\s+\((\d+)\)"
)
EZH_ARCH_B_RE = re.compile(
    r"(?m)^\s*#define\s+(EZH_ARCH_B)\b(?:\s+\(?(\d+)\)?)?"
)
LPC_BROAD_EZH_RE = re.compile(r"\bEZH\b|LPC_EZH_ARCH_B|EZH_ARCH_B")
IRQ_RE = re.compile(
    r"(?m)^\s*([A-Z0-9_]+_IRQn)\s*=\s*(-?\d+)\s*,?\s*(?:/\*[*!]<\s*(.*?)\s*\*/)?"
)
BASE_RE = re.compile(
    r"(?m)^\s*#define\s+({prefix}[A-Z0-9_]*BASE(?:_NS)?)\s+"
    r"\((0x[0-9A-Fa-f]+)[uUlL]*\)"
)


class DiscoveryError(RuntimeError):
    """Raised when platform discovery cannot complete."""


@lru_cache(maxsize=None)
def fetch_text(url: str) -> str:
    req = urllib.request.Request(
        url,
        headers={
            "Accept": "application/vnd.github+json",
            "User-Agent": "bunny-build-platform-discovery",
        },
    )
    try:
        with urllib.request.urlopen(req, timeout=60) as response:
            return response.read().decode("utf-8", errors="replace")
    except urllib.error.HTTPError as exc:
        raise DiscoveryError(f"{url}: HTTP {exc.code}") from exc
    except urllib.error.URLError as exc:
        raise DiscoveryError(f"{url}: {exc.reason}") from exc


def fetch_json(url: str) -> Any:
    return json.loads(fetch_text(url))


def raw_url(repo: str, revision: str, path: str) -> str:
    return f"https://raw.githubusercontent.com/{repo}/{revision}/{path}"


def parse_project_manifest(text: str, project_name: str) -> dict[str, str]:
    in_project = False
    out: dict[str, str] = {"name": project_name}
    for line in text.splitlines():
        if re.match(r"\s*-\s+name:\s+", line):
            in_project = re.search(rf"\bname:\s+{re.escape(project_name)}\s*$", line) is not None
            continue
        if not in_project:
            continue
        revision = re.match(r"\s+revision:\s+(\S+)\s*$", line)
        path = re.match(r"\s+path:\s+(\S+)\s*$", line)
        track = re.match(r"\s+track_branch:\s+(\S+)\s*$", line)
        if revision:
            out["revision"] = revision.group(1)
        elif path:
            out["path"] = path.group(1)
        elif track:
            out["track_branch"] = track.group(1)
    missing = sorted({"revision", "path"} - set(out))
    if missing:
        raise DiscoveryError(f"{project_name}: manifest missing {', '.join(missing)}")
    return out


def load_device_projects(manifest_rev: str, selected: set[str]) -> dict[str, dict[str, str]]:
    projects: dict[str, dict[str, str]] = {}
    for series, manifest_path in DEVICE_MANIFESTS.items():
        if series not in selected:
            continue
        project_name = f"mcux-devices-{series.lower()}"
        text = fetch_text(raw_url(MANIFEST_REPO, manifest_rev, manifest_path))
        project = parse_project_manifest(text, project_name)
        project.update(
            {
                "series": series,
                "repo": f"nxp-mcuxpresso/{project_name}",
                "manifest_path": manifest_path,
            }
        )
        projects[series] = project
    return projects


def load_tree(repo: str, revision: str) -> list[dict[str, Any]]:
    url = f"https://api.github.com/repos/{repo}/git/trees/{revision}?recursive=1"
    payload = fetch_json(url)
    if payload.get("truncated"):
        raise DiscoveryError(f"{repo}@{revision}: GitHub tree response was truncated")
    return list(payload.get("tree", []))


def feature_presence(text: str) -> dict[str, Any] | None:
    smartdma = SMARTDMA_COUNT_RE.search(text)
    if smartdma and int(smartdma.group(1)) > 0:
        return {
            "block_name": "SMARTDMA",
            "probe": "FSL_FEATURE_SOC_SMARTDMA_COUNT",
            "count": int(smartdma.group(1)),
        }
    for ezh_count in EZH_COUNT_RE.finditer(text):
        count = int(ezh_count.group(2))
        if count > 0:
            return {
                "block_name": "EZH",
                "probe": ezh_count.group(1),
                "count": count,
            }
    ezh_arch_b = EZH_ARCH_B_RE.search(text)
    if ezh_arch_b:
        count = int(ezh_arch_b.group(2) or "1")
        if count > 0:
            return {
                "block_name": "EZH",
                "probe": ezh_arch_b.group(1),
                "count": count,
            }
    return None


def part_and_core(path: str) -> tuple[str, str]:
    p = Path(path)
    part = p.parent.name
    stem = p.name.removesuffix("_features.h")
    if stem == part:
        return part, "default"
    prefix = f"{part}_"
    if stem.startswith(prefix):
        return part, stem[len(prefix) :]
    return part, stem


def expected_common_path(feature_path: str) -> str:
    return feature_path.removesuffix("_features.h") + "_COMMON.h"


def expected_chip_path(feature_path: str) -> str:
    return str(Path(feature_path).parent / "chip.yml").replace("\\", "/")


def strip_comment(text: str | None) -> str:
    if not text:
        return ""
    return re.sub(r"\s+", " ", text).strip()


def irq_candidates(block_name: str, text: str) -> list[dict[str, Any]]:
    out: list[dict[str, Any]] = []
    for match in IRQ_RE.finditer(text):
        name, number, comment = match.group(1), int(match.group(2)), strip_comment(match.group(3))
        name_key = name.upper()
        comment_key = comment.upper()
        if block_name == "SMARTDMA":
            is_match = (
                "SMARTDMA" in name_key
                or name_key == "SDMA_IRQN"
                or "SMARTDMA" in comment_key
                or "SMART DMA" in comment_key
            )
        else:
            is_match = "EZH" in name_key or "EZH" in comment_key
        if is_match:
            out.append({"name": name, "number": number, "description": comment})
    return sorted(out, key=lambda item: (item["number"], item["name"]))


def base_prefixes(block_name: str) -> list[str]:
    if block_name == "SMARTDMA":
        return ["SMARTDMA"]
    return ["LPC_EZH_ARCH_B", "EZH"]


def base_addresses(block_name: str, text: str) -> list[dict[str, Any]]:
    found: dict[tuple[str, str], dict[str, Any]] = {}
    for prefix in base_prefixes(block_name):
        regex = re.compile(BASE_RE.pattern.format(prefix=re.escape(prefix)))
        for match in regex.finditer(text):
            macro, address = match.group(1), match.group(2).lower()
            if macro.endswith("_BASE_ADDRS"):
                continue
            if macro.endswith("_NS"):
                space = "nonsecure_alias"
            elif address.startswith("0x5"):
                space = "secure_or_cmse"
            else:
                space = "default_or_nonsecure"
            found[(macro, address)] = {
                "macro": macro,
                "address": address,
                "address_int": int(address, 16),
                "space": space,
            }
    return sorted(found.values(), key=lambda item: (item["macro"], item["address_int"]))


def lpc_broad_ezh_sweep(
    repo: str,
    revision: str,
    paths: set[str],
    feature_paths: list[str],
) -> dict[str, Any]:
    scan_paths: set[str] = set()
    for feature_path in feature_paths:
        scan_paths.add(feature_path)
        common_path = expected_common_path(feature_path)
        chip_path = expected_chip_path(feature_path)
        if common_path in paths:
            scan_paths.add(common_path)
        if chip_path in paths:
            scan_paths.add(chip_path)
    scan_paths.update(path for path in paths if "EZH" in path.upper())

    candidates: list[dict[str, Any]] = []
    for path in sorted(scan_paths):
        path_match = "EZH" in path.upper()
        text = fetch_text(raw_url(repo, revision, path))
        text_match = LPC_BROAD_EZH_RE.search(text) is not None
        if path_match or text_match:
            candidate = {
                "path": path,
                "reason": "path" if path_match else "content",
            }
            if path.endswith("_COMMON.h"):
                candidate["irqs"] = irq_candidates("EZH", text)
                candidate["base_addresses"] = base_addresses("EZH", text)
            candidates.append(candidate)
    return {
        "broad_ezh_files_scanned": len(scan_paths),
        "broad_ezh_candidates": len(candidates),
        "unconfirmed_candidates": candidates,
    }


def discover_series(series: str, project: dict[str, str]) -> tuple[list[dict[str, Any]], dict[str, Any]]:
    repo = project["repo"]
    revision = project["revision"]
    tree = load_tree(repo, revision)
    paths = {entry["path"] for entry in tree if entry.get("type") == "blob"}
    feature_paths = sorted(path for path in paths if path.endswith("_features.h"))
    parts: dict[str, dict[str, Any]] = {}
    confirmed_core_views = 0
    broad_scan = (
        lpc_broad_ezh_sweep(repo, revision, paths, feature_paths)
        if series == "LPC"
        else {
            "broad_ezh_files_scanned": 0,
            "broad_ezh_candidates": 0,
            "unconfirmed_candidates": [],
        }
    )

    for feature_path in feature_paths:
        feature_text = fetch_text(raw_url(repo, revision, feature_path))
        presence = feature_presence(feature_text)
        if presence is None:
            continue
        confirmed_core_views += 1
        part, core = part_and_core(feature_path)
        common_path = expected_common_path(feature_path)
        common_text = fetch_text(raw_url(repo, revision, common_path)) if common_path in paths else ""
        core_record = {
            "core": core,
            "features_header": feature_path,
            "common_header": common_path if common_path in paths else None,
            "presence": presence,
            "irqs": irq_candidates(presence["block_name"], common_text),
            "base_addresses": base_addresses(presence["block_name"], common_text),
        }
        part_record = parts.setdefault(
            part,
            {
                "part": part,
                "series": series,
                "family": Path(feature_path).parts[0],
                "repo": repo,
                "repo_revision": revision,
                "repo_path": str(Path(feature_path).parent).replace("\\", "/"),
                "manifest_path": project["manifest_path"],
                "manifest_revision": "",
                "track_branch": project.get("track_branch"),
                "status": "sdk_feature_confirmed",
                "stage": "sdk_headers",
                "cores": [],
                "enrichment": {
                    "pin_mux": "pending_nxp_monkey",
                    "inputmux_triggers": "pending_nxp_monkey",
                    "register_block": "pending_nxp_monkey",
                },
            },
        )
        part_record["cores"].append(core_record)

    for part in parts.values():
        part["cores"].sort(key=lambda item: item["core"])

    stats = {
        "feature_headers_scanned": len(feature_paths),
        "confirmed_core_views": confirmed_core_views,
        "confirmed_parts": len(parts),
        "tree_entries": len(tree),
        **broad_scan,
    }
    return sorted(parts.values(), key=lambda item: item["part"]), stats


def build_model(manifest_rev: str, selected: set[str]) -> tuple[dict[str, Any], list[dict[str, Any]]]:
    projects = load_device_projects(manifest_rev, selected)
    parts: list[dict[str, Any]] = []
    series_stats: dict[str, Any] = {}
    open_items: list[dict[str, str]] = []
    for series in sorted(projects):
        series_parts, stats = discover_series(series, projects[series])
        for part in series_parts:
            part["manifest_revision"] = manifest_rev
        parts.extend(series_parts)
        series_stats[series] = stats
        if series == "LPC" and not series_parts:
            open_items.append(
                {
                    "id": "lpc-current-sdk-no-ezh-probe",
                    "severity": "blocks_platform_guide_completeness",
                    "detail": (
                        "The pinned LPC device repo has "
                        f"{stats['feature_headers_scanned']} feature headers, "
                        "but none match FSL_FEATURE_SOC_SMARTDMA_COUNT or "
                        "EZH_ARCH_B. The LPC broad sweep checked "
                        f"{stats['broad_ezh_files_scanned']} feature/common/chip "
                        "metadata paths and found "
                        f"{stats['broad_ezh_candidates']} unconfirmed EZH marker "
                        "file(s). "
                        "Legacy LPC EZH rows need AN/RM/nxp-monkey confirmation."
                    ),
                }
            )
    parts.sort(key=lambda item: (item["series"], item["part"]))
    return {
        "schema": "ezh-platform-sdk-headers-v1",
        "generator": "isa/tools/discover_parts.py",
        "stage": "sdk_header_discovery",
        "manifest": {
            "repo": MANIFEST_REPO,
            "revision": manifest_rev,
            "device_manifests": {
                series: projects[series]["manifest_path"] for series in sorted(projects)
            },
        },
        "series": series_stats,
        "summary": {
            "confirmed_parts": len(parts),
            "confirmed_core_views": sum(
                len(part["cores"]) for part in parts
            ),
            "parts_missing_any_base_address": sum(
                any(not core["base_addresses"] for core in part["cores"]) for part in parts
            ),
            "cores_missing_irq": sum(
                not core["irqs"] for part in parts for core in part["cores"]
            ),
        },
        "part_files": [f"parts/{part['part']}.json" for part in parts],
        "open_items": open_items,
        "notes": [
            "Pin mux, INPUTMUX trigger maps, and register block extraction are deferred to the nxp-monkey enrichment stage.",
            "IRQ values are extracted from SDK COMMON.h IRQn_Type enums, not config-tool interrupt tables.",
        ],
        "projects": {series: projects[series] for series in sorted(projects)},
        "parts": [
            {
                "part": part["part"],
                "series": part["series"],
                "family": part["family"],
                "cores": [core["core"] for core in part["cores"]],
                "file": f"parts/{part['part']}.json",
            }
            for part in parts
        ],
    }, parts


def json_text(data: Any) -> str:
    return json.dumps(data, indent=2, sort_keys=True) + "\n"


def write_text(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8", newline="\n")


def guard_output_dir(out_dir: Path, *, allow_outside: bool = False) -> Path:
    resolved = out_dir.resolve()
    root = ROOT.resolve()
    if allow_outside:
        return resolved
    if not resolved.is_relative_to(root):
        raise DiscoveryError(f"--out must stay inside the repository: {out_dir}")
    default = DEFAULT_OUT.resolve()
    if resolved != default and not (resolved / SENTINEL).exists():
        raise DiscoveryError(
            f"refusing to write non-default output without {SENTINEL}: {out_dir}"
        )
    return resolved


def write_output(
    out_dir: Path,
    index: dict[str, Any],
    parts: list[dict[str, Any]],
    *,
    allow_outside: bool = False,
) -> None:
    out_dir = guard_output_dir(out_dir, allow_outside=allow_outside)
    out_dir.mkdir(parents=True, exist_ok=True)
    write_text(out_dir / SENTINEL, "generated by isa/tools/discover_parts.py\n")
    parts_dir = out_dir / "parts"
    if parts_dir.exists():
        resolved_parts = parts_dir.resolve()
        if not resolved_parts.is_relative_to(out_dir):
            raise DiscoveryError(f"refusing to clear unexpected parts directory: {parts_dir}")
        shutil.rmtree(parts_dir)
    for part in parts:
        write_text(parts_dir / f"{part['part']}.json", json_text(part))
    write_text(out_dir / "index.json", json_text(index))


def file_map(root: Path) -> dict[Path, Path]:
    return {
        path.relative_to(root): path
        for path in root.rglob("*")
        if path.is_file()
    }


def compare_dirs(left: Path, right: Path) -> list[str]:
    if not right.exists():
        return [f"missing output directory: {right}"]
    left_files = file_map(left)
    right_files = file_map(right)
    diffs: list[str] = []
    for rel in sorted(set(left_files) - set(right_files)):
        diffs.append(f"missing from committed output: {rel.as_posix()}")
    for rel in sorted(set(right_files) - set(left_files)):
        diffs.append(f"stale in committed output: {rel.as_posix()}")
    for rel in sorted(set(left_files) & set(right_files)):
        if left_files[rel].read_bytes() != right_files[rel].read_bytes():
            diffs.append(f"content differs: {rel.as_posix()}")
    return sorted(diffs)


def completeness_errors(index: dict[str, Any], parts: list[dict[str, Any]]) -> list[str]:
    errors: list[str] = []
    for item in index["open_items"]:
        errors.append(f"{item['id']}: {item['detail']}")
    for part in parts:
        for core in part["cores"]:
            label = f"{part['part']}:{core['core']}"
            if not core["irqs"]:
                errors.append(f"{label}: no SDK IRQn enum entry extracted")
            if not core["base_addresses"]:
                errors.append(f"{label}: no SDK base-address macro extracted")
    return errors


def parser_selftest() -> None:
    presence_cases = [
        (
            "smartdma zero count",
            "#define FSL_FEATURE_SOC_SMARTDMA_COUNT (0)\n",
            None,
        ),
        (
            "smartdma positive count",
            "#define FSL_FEATURE_SOC_SMARTDMA_COUNT (1)\n",
            {
                "block_name": "SMARTDMA",
                "probe": "FSL_FEATURE_SOC_SMARTDMA_COUNT",
                "count": 1,
            },
        ),
        (
            "ezh zero count",
            "#define FSL_FEATURE_SOC_EZH_ARCH_B_COUNT (0)\n",
            None,
        ),
        (
            "ezh positive count after zero count",
            (
                "#define FSL_FEATURE_SOC_EZH_ARCH_A_COUNT (0)\n"
                "#define FSL_FEATURE_SOC_EZH_ARCH_B_COUNT (2)\n"
            ),
            {
                "block_name": "EZH",
                "probe": "FSL_FEATURE_SOC_EZH_ARCH_B_COUNT",
                "count": 2,
            },
        ),
        (
            "ezh arch b implicit count",
            "#define EZH_ARCH_B\n",
            {"block_name": "EZH", "probe": "EZH_ARCH_B", "count": 1},
        ),
        (
            "ezh arch b zero value",
            "#define EZH_ARCH_B 0\n",
            None,
        ),
        (
            "ezh arch b parenthesized zero value",
            "#define EZH_ARCH_B (0)\n",
            None,
        ),
    ]
    for label, text, expected in presence_cases:
        actual = feature_presence(text)
        if actual != expected:
            raise DiscoveryError(
                f"parser self-test failed for {label}: expected {expected!r}, got {actual!r}"
            )

    irq_text = """
typedef enum IRQn {
  SDMA_IRQn                    = 73,
  DMA0_IRQn                    = 74, /*!< ordinary DMA */
  FLEXCOMM0_IRQn               = 75, /*!< Smart DMA wake */
} IRQn_Type;
"""
    smartdma_irqs = irq_candidates("SMARTDMA", irq_text)
    if smartdma_irqs != [
        {"name": "SDMA_IRQn", "number": 73, "description": ""},
        {"name": "FLEXCOMM0_IRQn", "number": 75, "description": "Smart DMA wake"},
    ]:
        raise DiscoveryError(
            "parser self-test failed for SmartDMA IRQ candidates: "
            f"got {smartdma_irqs!r}"
        )

    ezh_irqs = irq_candidates(
        "EZH",
        """
typedef enum IRQn {
  EZH_ARCH_B0_IRQn             = 30, /*!< EZH interrupt */
  SDMA_IRQn                    = 73,
} IRQn_Type;
""",
    )
    if ezh_irqs != [
        {"name": "EZH_ARCH_B0_IRQn", "number": 30, "description": "EZH interrupt"}
    ]:
        raise DiscoveryError(
            f"parser self-test failed for EZH IRQ candidates: got {ezh_irqs!r}"
        )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Discover EZH/SmartDMA platform facts from pinned SDK headers."
    )
    parser.add_argument("--self-test", action="store_true", help="run offline parser tests")
    parser.add_argument("--check", action="store_true", help="fail if generated output is stale")
    parser.add_argument("--out", type=Path, default=DEFAULT_OUT, help="output directory")
    parser.add_argument(
        "--manifest-rev",
        default=DEFAULT_MANIFEST_REV,
        help="mcuxsdk-manifests commit SHA to use",
    )
    parser.add_argument(
        "--series",
        choices=sorted(DEVICE_MANIFESTS),
        action="append",
        help="limit discovery to one or more device series",
    )
    parser.add_argument(
        "--require-complete",
        action="store_true",
        help="fail on unresolved open items, missing IRQs, or missing base addresses",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    selected = set(args.series or DEVICE_MANIFESTS)
    try:
        parser_selftest()
        if args.self_test:
            print("Platform discovery parser self-test passed.")
            return 0
        index, parts = build_model(args.manifest_rev, selected)
        if args.require_complete:
            errors = completeness_errors(index, parts)
            if errors:
                print("Platform extraction is incomplete:")
                for error in errors:
                    print(f"  - {error}")
                return 1
        if args.check:
            with tempfile.TemporaryDirectory(prefix="ezh-platform-") as tmp:
                tmp_out = Path(tmp) / "platform"
                write_output(tmp_out, index, parts, allow_outside=True)
                diffs = compare_dirs(tmp_out, args.out)
            if diffs:
                print("Generated platform data is stale:")
                for diff in diffs[:50]:
                    print(f"  - {diff}")
                if len(diffs) > 50:
                    print(f"  ... {len(diffs) - 50} more")
                return 1
            print(
                "Generated platform data is current: "
                f"{index['summary']['confirmed_parts']} parts, "
                f"{index['summary']['confirmed_core_views']} core views."
            )
            return 0
        write_output(args.out, index, parts)
    except DiscoveryError as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 1

    summary = index["summary"]
    print(
        f"Wrote {summary['confirmed_parts']} parts "
        f"({summary['confirmed_core_views']} core views) to {args.out}"
    )
    if index["open_items"]:
        print(f"Open items: {len(index['open_items'])}")
        for item in index["open_items"]:
            print(f"  - {item['id']}: {item['detail']}")
    if summary["parts_missing_any_base_address"] or summary["cores_missing_irq"]:
        print(
            "Incomplete extracts: "
            f"{summary['parts_missing_any_base_address']} part(s) missing a base address, "
            f"{summary['cores_missing_irq']} core view(s) missing an IRQ."
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
