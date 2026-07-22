"""Validate the EZH ISA description and demo-emit C / Verilog from it.

Usage:  uv run python isa/tools/validate.py [--emit]

Checks per form:
  - slice widths match between instr and value ranges, bits within word width
  - no instruction bit claimed twice (fixed vs operand vs modifier fields)
  - operand/modifier names resolve in fields.toml
  - provenance sources resolve in arch.toml
  - form's fixed low bits agree with the file's [opcode].value (typo guard;
    GOSUB-style forms may fix fewer than 5 low bits, but what they fix must match)
Global checks:
  - every field in fields.toml is structurally valid even if unreferenced;
    unreferenced fields are reported as warnings
  - opcode values are unique across files
Derives decode mask/match per form. With --emit, prints a C encode macro and a
Verilog decode snippet per form — demonstrating that the same data drives both.

Self-test: encodes E_MOV(R1, R2) and E_PER_WRITE(R3, 0x32200) through the slice
model and compares against the known bunny_build encoder formulas.
"""
from __future__ import annotations

import re
import sys
import tomllib
from pathlib import Path

# Bracket groups in a mnemonic pattern: [X] optional token, {A|B} alternation.
MNEM_GROUP = re.compile(r"\[[A-Z0-9_]+\]|\{[A-Z0-9_]+(?:\|[A-Z0-9_]+)+\}")

ROOT = Path(__file__).resolve().parent.parent
EZH = ROOT / "ezh_b"


def parse_range(spec: str) -> tuple[int, int]:
    msb, lsb = (int(x) for x in spec.split(":"))
    if msb < lsb:
        raise ValueError(f"range {spec!r}: msb < lsb")
    return msb, lsb


def width(spec: str) -> int:
    msb, lsb = parse_range(spec)
    return msb - lsb + 1


def load() -> tuple[dict, dict, dict[str, dict]]:
    arch = tomllib.loads((EZH / "arch.toml").read_text(encoding="utf-8"))
    fields = tomllib.loads((EZH / "fields.toml").read_text(encoding="utf-8"))["fields"]
    opcodes = {}
    for f in sorted((EZH / "opcodes").glob("*.toml")):
        opcodes[f.stem] = tomllib.loads(f.read_text(encoding="utf-8"))
    return arch, fields, opcodes


def field_bits(field: dict) -> set[int]:
    bits: set[int] = set()
    for s in field["slices"]:
        imsb, ilsb = parse_range(s["instr"])
        vmsb, vlsb = parse_range(s["value"])
        if imsb - ilsb != vmsb - vlsb:
            raise ValueError(f"slice width mismatch: instr {s['instr']} vs value {s['value']}")
        bits |= set(range(ilsb, imsb + 1))
    return bits


def encode_field(field: dict, value: int) -> int:
    word = 0
    for s in field["slices"]:
        imsb, ilsb = parse_range(s["instr"])
        vmsb, vlsb = parse_range(s["value"])
        chunk = (value >> vlsb) & ((1 << (vmsb - vlsb + 1)) - 1)
        word |= chunk << ilsb
    return word


def c_expr(field: dict, var: str) -> str:
    parts = []
    for s in field["slices"]:
        imsb, ilsb = parse_range(s["instr"])
        vmsb, vlsb = parse_range(s["value"])
        mask = (1 << (vmsb - vlsb + 1)) - 1
        parts.append(f"(((({var}) >> {vlsb}) & 0x{mask:x}u) << {ilsb})")
    return " | ".join(parts)


def verilog_decode(field_name: str, field: dict) -> list[str]:
    lines = []
    for s in field["slices"]:
        lines.append(f"assign {field_name}[{s['value']}] = instr[{s['instr']}];")
    return lines


def validate_form(name: str, form: dict, fields: dict, word_width: int) -> tuple[int, int]:
    claimed: dict[int, str] = {}

    def claim(bits: set[int], owner: str) -> None:
        for b in bits:
            if b >= word_width or b < 0:
                raise ValueError(f"{name}: bit {b} out of range ({owner})")
            if b in claimed:
                raise ValueError(f"{name}: bit {b} claimed by both {claimed[b]} and {owner}")
            claimed[b] = owner

    mask = match = 0
    for fx in form.get("fixed", []):
        msb, lsb = parse_range(fx["bits"])
        w = msb - lsb + 1
        if fx["value"] >= (1 << w):
            raise ValueError(f"{name}: fixed value 0x{fx['value']:x} wider than {fx['bits']}")
        claim(set(range(lsb, msb + 1)), f"fixed {fx['bits']}")
        mask |= ((1 << w) - 1) << lsb
        match |= fx["value"] << lsb

    for group in ("operands", "modifiers"):
        for fname in form.get(group, []):
            if fname not in fields:
                raise ValueError(f"{name}: unknown field {fname!r} in {group}")
            claim(field_bits(fields[fname]), fname)

    return mask, match


def main() -> int:
    emit = "--emit" in sys.argv
    arch, fields, opcodes = load()
    word_width = arch["arch"]["instruction_width"]
    sources = set(arch.get("sources", {}))
    errors = 0

    # Structural check on every field, referenced or not, so a staged field
    # can't sit in fields.toml with a width mismatch nobody has hit yet.
    for fname, field in fields.items():
        try:
            field_bits(field)
        except ValueError as e:
            print(f"ERROR fields.{fname}: {e}")
            errors += 1

    referenced: set[str] = set()
    opcode_values: dict[int, str] = {}

    for opname, op in opcodes.items():
        opval = op["opcode"]["value"]
        if opval in opcode_values:
            print(f"ERROR {opname}: opcode value 0x{opval:02x} already used by {opcode_values[opval]}")
            errors += 1
        else:
            opcode_values[opval] = opname
        for prov in op.get("provenance", []):
            if prov["source"] not in sources:
                print(f"ERROR {opname}: unknown provenance source {prov['source']!r}")
                errors += 1
        for form in op.get("forms", []):
            fq = f"{op['opcode']['name']}/{form['name']}"
            try:
                mask, match = validate_form(fq, form, fields, word_width)
            except ValueError as e:
                print(f"ERROR {e}")
                errors += 1
                continue
            referenced.update(form.get("operands", []))
            referenced.update(form.get("modifiers", []))
            mnem = form.get("mnemonic")
            if mnem is None:
                print(f"ERROR {fq}: missing mnemonic pattern (isa-adr-0001)")
                errors += 1
            else:
                groups = MNEM_GROUP.findall(mnem["pattern"])
                binds = mnem.get("binds", [])
                form_fields = form.get("operands", []) + form.get("modifiers", [])
                if len(groups) != len(binds):
                    print(
                        f"ERROR {fq}: mnemonic pattern has {len(groups)} bracket "
                        f"group(s) but {len(binds)} bind(s)"
                    )
                    errors += 1
                for b in binds:
                    if b not in form_fields:
                        print(f"ERROR {fq}: mnemonic bind {b!r} is not an operand/modifier of this form")
                        errors += 1
            low_mask = mask & 0x1F
            if low_mask == 0:
                print(f"ERROR {fq}: no fixed bits in [4:0] — opcode not encoded")
                errors += 1
            elif (match & low_mask) != (opval & low_mask):
                print(
                    f"ERROR {fq}: fixed low bits 0x{match & low_mask:02x} "
                    f"disagree with [opcode].value 0x{opval:02x}"
                )
                errors += 1
            print(f"OK  {fq:<18} mask=0x{mask:08x} match=0x{match:08x}")
            if emit:
                ops = form.get("operands", []) + form.get("modifiers", [])
                args = ", ".join(ops) if ops else "void"
                enc = [f"0x{match:x}u"] + [c_expr(fields[o], o) for o in ops]
                print(f"    C:  #define EZH_ENC_{op['opcode']['name']}_{form['name'].upper()}({args}) \\")
                print(f"          ( {' | '.join(enc)} )")
                print(f"    V:  wire is_{opname}_{form['name']} = ((instr & 32'h{mask:08X}) == 32'h{match:08X});")
                for o in form.get("operands", []):
                    for line in verilog_decode(o, fields[o]):
                        print(f"        {line}")

    # Aliases: named presets over a form (e.g. POP = LDR word writeback SP -1).
    for opname, op in opcodes.items():
        form_map = {f["name"]: f for f in op.get("forms", [])}
        for al in op.get("aliases", []):
            form = form_map.get(al.get("form"))
            if form is None:
                print(f"ERROR {opname}: alias {al.get('name')!r} references unknown form {al.get('form')!r}")
                errors += 1
                continue
            form_fields = form.get("operands", []) + form.get("modifiers", [])
            for key in list(al.get("preset", {})) + al.get("operands", []):
                if key not in form_fields:
                    print(f"ERROR {opname}: alias {al['name']!r} uses {key!r}, not a field of form {al['form']!r}")
                    errors += 1

    for fname in sorted(set(fields) - referenced):
        print(f"WARN fields.{fname} is not referenced by any form (staged for a future opcode file?)")

    # --- self-test against known bunny_build encoder formulas -----------------
    EU, R1, R2, R3 = 0x0, 0x1, 0x2, 0x3
    mov = opcodes["mov"]
    reg_form = next(f for f in mov["forms"] if f["name"] == "reg")
    _, match = validate_form("selftest", reg_form, fields, word_width)
    got = match | encode_field(fields["dest"], R1) | encode_field(fields["src1"], R2)
    want = 0x0 + (R2 << 14) + (R1 << 10) + (EU << 5)
    status = "PASS" if got == want else "FAIL"
    print(f"{status} selftest E_MOV(R1,R2): isa=0x{got:08x} bunny_build=0x{want:08x}")
    errors += status == "FAIL"

    pw = opcodes["per_write"]
    _, match = validate_form("selftest", pw["forms"][0], fields, word_width)
    addr = 0x32200
    got = match | encode_field(fields["src2"], R3) | encode_field(fields["per_addr20_w"], addr)
    want = 0x5 + (R3 << 20) + ((addr & 0x000FF000) << 12) + ((addr & 0x00000FFC) << 8) + (EU << 5)
    status = "PASS" if got == want else "FAIL"
    print(f"{status} selftest E_PER_WRITE(R3,0x32200): isa=0x{got:08x} bunny_build=0x{want:08x}")
    errors += status == "FAIL"

    # Field-only check for the staged PER_READ address field: E_PER_READ packs
    # (addr & 0xffffc) << 12, i.e. instr[31:14] <- value[19:2].
    got = encode_field(fields["per_addr20_r"], addr)
    want = (addr & 0x000FFFFC) << 12
    status = "PASS" if got == want else "FAIL"
    print(f"{status} selftest per_addr20_r(0x{addr:x}): isa=0x{got:08x} bunny_build=0x{want:08x}")
    errors += status == "FAIL"

    if errors:
        print(f"\n{errors} error(s)")
        return 1
    print("\nAll checks passed.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
