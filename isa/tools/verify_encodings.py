"""Verify the ISA database against the bunny_build encoder header, name-free.

Usage:  uv run python isa/tools/verify_encodings.py [--verbose]

Consumes the probe inventory produced by extract_header.py (re-derived on the
fly) and checks, for EVERY encoder function in include/bunny_build__instr.h:

  1. its base word (all args 0, cond = EU) is exactly explained by one form of
     the matching opcode file: fixed bits match, and every remaining set bit
     belongs to a declared modifier field — or by one alias (form + baked
     preset values);
  2. every function argument's probed value-bit -> instr-bit map agrees with
     exactly one operand field's slices (compared over the DB-declared value
     width; probe bits beyond it are unmasked-argument artifacts and ignored);
  3. COND_ variants map their cond argument onto the cond field slices.

No mnemonic grammar involved: matching is purely structural, so a wrong bit in
the DB cannot hide behind a name. Exit code 1 on any unmatched or ambiguous
function or any form with zero header coverage (dead form).
"""
from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import extract_header  # noqa: E402
from validate import load, parse_range  # noqa: E402


def field_map(field: dict) -> dict[int, list[int]]:
    """value bit -> sorted instruction bits (replicated slices give several)."""
    out: dict[int, list[int]] = {}
    for s in field["slices"]:
        imsb, ilsb = parse_range(s["instr"])
        vmsb, vlsb = parse_range(s["value"])
        for off in range(vmsb - vlsb + 1):
            out.setdefault(vlsb + off, []).append(ilsb + off)
    return {v: sorted(b) for v, b in out.items()}


def encode(field: dict, value: int) -> int:
    word = 0
    for s in field["slices"]:
        imsb, ilsb = parse_range(s["instr"])
        vmsb, vlsb = parse_range(s["value"])
        word |= ((value >> vlsb) & ((1 << (vmsb - vlsb + 1)) - 1)) << ilsb
    return word


def bits_of(field: dict) -> int:
    m = 0
    for s in field["slices"]:
        imsb, ilsb = parse_range(s["instr"])
        m |= ((1 << (imsb - ilsb + 1)) - 1) << ilsb
    return m


def form_mask_match(form: dict) -> tuple[int, int]:
    mask = match = 0
    for fx in form.get("fixed", []):
        msb, lsb = parse_range(fx["bits"])
        mask |= ((1 << (msb - lsb + 1)) - 1) << lsb
        match |= fx["value"] << lsb
    return mask, match


def arg_matches(arg_map: dict, dbmap: dict[int, list[int]]) -> bool:
    """Every DB-declared value bit must be present in the probe map and agree."""
    for vbit, ibits in dbmap.items():
        if arg_map.get(vbit, arg_map.get(str(vbit))) != ibits:
            return False
    return True


def try_form(form: dict, fn: dict, cond_used: bool, fields: dict) -> dict | None:
    """Match a probed function against one form; return match info or None."""
    mask, match = form_mask_match(form)
    base = fn["base"]
    if base & mask != match:
        return None
    mod_bits = 0
    for m in form.get("modifiers", []):
        mod_bits |= bits_of(fields[m])
    if base & ~mask & ~mod_bits:
        return None
    args = [a for a in fn["args"] if a != "cond"]
    operands = list(form.get("operands", []))
    used: set[str] = set()
    for a in args:
        hit = [o for o in operands if o not in used and arg_matches(fn["fields"][a], field_map(fields[o]))]
        if len(hit) != 1:
            return None
        used.add(hit[0])
    if cond_used and "cond" not in form.get("modifiers", []):
        return None
    return {"label": form["name"], "form": form["name"], "operands_used": used}


def try_alias(op: dict, alias: dict, fn: dict, cond_used: bool, fields: dict) -> dict | None:
    """Match a probed function against one alias; return match info or None."""
    form = next(f for f in op["forms"] if f["name"] == alias["form"])
    _, match = form_mask_match(form)
    word = match
    for key, val in alias.get("preset", {}).items():
        word |= encode(fields[key], val)
    if fn["base"] != word:
        return None
    args = [a for a in fn["args"] if a != "cond"]
    ops = list(alias.get("operands", []))
    if len(args) != len(ops):
        return None
    used: set[str] = set()
    for a in args:
        hit = [o for o in ops if o not in used and arg_matches(fn["fields"][a], field_map(fields[o]))]
        if len(hit) != 1:
            return None
        used.add(hit[0])
    if cond_used and "cond" not in form.get("modifiers", []):
        return None
    return {"label": f"alias:{alias['name']}", "form": alias["form"], "alias": alias["name"]}


def main() -> int:
    verbose = "--verbose" in sys.argv
    arch, fields, opcodes = load()
    by_value = {op["opcode"]["value"]: (name, op) for name, op in opcodes.items()}

    inv, exterrors = extract_header.extract()
    if exterrors:
        for e in exterrors:
            print(f"ERROR {e}")
        return 1

    cond_map = field_map(fields["cond"])
    errors = 0
    coverage: dict[str, int] = {}

    for fname, fn in sorted(inv.items()):
        cond_used = "cond" in fn["args"]
        if cond_used and not arg_matches(fn["fields"]["cond"], cond_map):
            print(f"FAIL {fname}: cond argument does not land on the cond field")
            errors += 1
            continue
        opval = fn["base"] & 0x1F
        if opval not in by_value:
            print(f"FAIL {fname}: no opcode file for value 0x{opval:02x}")
            errors += 1
            continue
        opname, op = by_value[opval]
        hits = []
        for form in op.get("forms", []):
            r = try_form(form, fn, cond_used, fields)
            if r:
                hits.append(r["label"])
        for alias in op.get("aliases", []):
            r = try_alias(op, alias, fn, cond_used, fields)
            if r:
                hits.append(r["label"])
        if len(hits) == 1:
            key = f"{opname}/{hits[0]}"
            coverage[key] = coverage.get(key, 0) + 1
            if verbose:
                print(f"ok   {fname:32s} -> {key}")
        elif not hits:
            print(f"FAIL {fname}: base=0x{fn['base']:08x} matches no form/alias of {opname}")
            errors += 1
        else:
            print(f"FAIL {fname}: ambiguous, matches {hits}")
            errors += 1

    # Dead forms: every non-alias form should explain at least one function.
    # (NOP and GOSUB are not inline functions; they are checked directly.)
    nop = opcodes["nop"]
    m, mt = form_mask_match(next(f for f in nop["forms"] if f["name"] == "nop"))
    if 0x12 & m != mt:
        print("FAIL canonical E_NOP word 0x12 does not decode as NOP/nop")
        errors += 1
    coverage.setdefault("nop/nop", 1)
    gosub = opcodes["gosub"]
    m, mt = form_mask_match(gosub["forms"][0])
    if (m, mt) != (0x3, 0x3):
        print("FAIL GOSUB form must fix exactly bits [1:0] = 0b11")
        errors += 1
    coverage.setdefault("gosub/default", 1)

    # GOTO lives in src/bunny_build__instr.c (two-pass label resolution), not
    # the header, so it is outside the probe universe: check the formulas here.
    goto = opcodes["goto"]
    gforms = {f["name"]: f for f in goto["forms"]}
    addr, reg, cond = 0x0012_3456 & 0x1FFFFC, 0x3, 0x7
    checks = [
        ("E_GOTO", form_mask_match(gforms["imm"])[1] | encode(fields["goto_addr21"], addr),
         0x15 + (1 << 9) + ((addr & 0x1FFFFF) << 9)),
        ("E_GOTOL", form_mask_match(gforms["imm"])[1] | encode(fields["goto_addr21"], addr) | encode(fields["link"], 1),
         0x15 + (1 << 10) + (1 << 9) + ((addr & 0x1FFFFF) << 9)),
        ("E_COND_GOTO_REG", form_mask_match(gforms["reg"])[1] | encode(fields["src1"], reg) | encode(fields["cond"], cond),
         0x15 + (reg << 14) + (cond << 5)),
        ("E_GOTO_REGL", form_mask_match(gforms["reg"])[1] | encode(fields["src1"], reg) | encode(fields["link"], 1),
         0x15 + (reg << 14) + (1 << 10)),
    ]
    for name, got, want in checks:
        if got != want:
            print(f"FAIL {name}: isa=0x{got:08x} bunny_build=0x{want:08x}")
            errors += 1
    coverage.setdefault("goto/imm", 1)
    coverage.setdefault("goto/reg", 1)

    for name, op in opcodes.items():
        for form in op.get("forms", []):
            key = f"{op['opcode']['name']}/{form['name']}"
            key2 = f"{name}/{form['name']}"
            n = coverage.get(key2, 0)
            if n == 0:
                print(f"FAIL {key}: no header function matches this form (dead form)")
                errors += 1

    total = len(inv)
    matched = sum(coverage.values())
    print(f"\n{total} header functions checked; per-form coverage:")
    for key in sorted(coverage):
        print(f"  {key:24s} {coverage[key]:4d}")
    if errors:
        print(f"\n{errors} error(s)")
        return 1
    print("\nAll header encodings verified against the ISA database.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
