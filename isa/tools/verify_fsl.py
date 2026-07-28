"""Three-way encoding verification: fsl header vs ISA database vs bunny_build.

Usage:  uv run python isa/tools/verify_fsl.py [--header PATH] [--verbose]

The fsl header (`fsl_ezh_armclang.h`, hand-created by the original EZH owner) is authority
#1 for encodings.  This tool closes the verify-encodings loop:

  1. constants: every register / condition / bit-slice value in arch.toml must
     equal the header's own #define (aliases included);
  2. structure: every fsl macro's probed base + argument maps must match
     exactly one form or alias of the ISA db, name-free (same matcher used by
     verify_encodings.py for the bunny_build side);
  3. cross-diff: for every E_* name present in both headers, base words and
     positional argument bit-maps must agree (compared over probe bits both
     sides recovered);
  4. coverage: across the full fsl expansion, every form must be hit, every
     declared modifier must be observed set at least once (cond counts via
     COND_ variants), and every declared operand must be exercised by some
     argument — a phantom modifier/operand in the db cannot pass silently;
  5. known-defect review report: known-defective macros (uncompilable as written)
     and name-set asymmetries between the two headers, printed for source, bench,
     or owner review — informational, not failures, since the db already records them.

Exit code 1 on any constant mismatch, structural mismatch, ambiguous match,
cross-diff disagreement, dead form, phantom modifier, or phantom operand.
"""
from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import extract_fsl  # noqa: E402
import extract_header  # noqa: E402
from validate import load  # noqa: E402
from verify_encodings import arg_matches, bits_of, field_map, try_alias, try_form  # noqa: E402

# Present in fsl as macros but deliberately not inline functions in
# bunny_build__instr.h (GOTO needs two-pass label resolution; NOP and GOSUB
# are emitted directly).  verify_encodings.py checks their bunny_build
# formulas; here they still verify structurally against the db.
KNOWN_NON_INLINE = {
    "E_NOP",
    "E_GOSUB",
    "E_GOTO",
    "E_GOTOL",
    "E_GOTO_REG",
    "E_GOTO_REGL",
    "E_COND_GOTO",
    "E_COND_GOTOL",
    "E_COND_GOTO_REG",
    "E_COND_GOTO_REGL",
}


def check_constants(arch: dict, consts: dict[str, int]) -> int:
    errors = 0
    for table in ("registers", "conditions", "bit_slice_cfg"):
        for name, ent in arch[table].items():
            for alias in [name, *ent.get("alias", [])]:
                got = consts.get(alias)
                if got is None:
                    print(f"FAIL const {table}.{alias}: not defined in fsl header")
                    errors += 1
                elif got != ent["value"]:
                    print(
                        f"FAIL const {table}.{alias}: db=0x{ent['value']:x} "
                        f"fsl=0x{got:x}"
                    )
                    errors += 1
    return errors


def cross_diff(fsl: dict, bb: dict, verbose: bool) -> int:
    errors = 0
    common = sorted(fsl.keys() & bb.keys())
    for name in common:
        f, b = fsl[name], bb[name]
        if f["base"] != b["base"]:
            print(f"FAIL diff {name}: base fsl=0x{f['base']:08x} bunny_build=0x{b['base']:08x}")
            errors += 1
            continue
        if len(f["args"]) != len(b["args"]):
            print(
                f"FAIL diff {name}: arg count fsl={len(f['args'])} "
                f"bunny_build={len(b['args'])}"
            )
            errors += 1
            continue
        for fa, ba in zip(f["args"], b["args"]):
            fmap, bmap = f["fields"][fa], b["fields"][ba]
            shared = fmap.keys() & bmap.keys()
            bad = {k: (fmap[k], bmap[k]) for k in shared if fmap[k] != bmap[k]}
            if bad:
                print(f"FAIL diff {name}.{fa}: value-bit maps disagree: {bad}")
                errors += 1
    if verbose:
        print(f"cross-diff: {len(common)} shared names compared")
    return errors


def main() -> int:
    argv = sys.argv[1:]
    verbose = "--verbose" in argv
    header = extract_fsl.DEFAULT_HEADER
    if "--header" in argv:
        header = Path(argv[argv.index("--header") + 1])

    arch, fields, opcodes = load()
    by_value = {op["opcode"]["value"]: (name, op) for name, op in opcodes.items()}

    consts, inv, excluded, exterrors = extract_fsl.extract(header)
    for e in exterrors:
        print(f"ERROR {e}")
    errors = len(exterrors)

    errors += check_constants(arch, consts)

    cond_map = field_map(fields["cond"])
    coverage: dict[str, int] = {}
    # form key -> set of modifier names observed set / operand names exercised
    mods_seen: dict[str, set[str]] = {}
    opers_seen: dict[str, set[str]] = {}

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
                hits.append((r, form))
        for alias in op.get("aliases", []):
            r = try_alias(op, alias, fn, cond_used, fields)
            if r:
                form = next(f for f in op["forms"] if f["name"] == r["form"])
                hits.append((r, form))
        if len(hits) != 1:
            if not hits:
                print(f"FAIL {fname}: base=0x{fn['base']:08x} matches no form/alias of {opname}")
            else:
                print(f"FAIL {fname}: ambiguous, matches {[r['label'] for r, _ in hits]}")
            errors += 1
            continue
        r, form = hits[0]
        key = f"{opname}/{r['form']}"
        coverage[f"{opname}/{r['label']}"] = coverage.get(f"{opname}/{r['label']}", 0) + 1
        ms = mods_seen.setdefault(key, set())
        for m in form.get("modifiers", []):
            if m == "cond":
                if cond_used:
                    ms.add("cond")
            elif fn["base"] & bits_of(fields[m]):
                ms.add(m)
        opers_seen.setdefault(key, set()).update(r.get("operands_used", set()))
        if verbose:
            print(f"ok   {fname:36s} -> {opname}/{r['label']}")

    # Dead forms and phantom modifiers/operands over the full fsl expansion.
    for name, op in opcodes.items():
        for form in op.get("forms", []):
            key = f"{name}/{form['name']}"
            if coverage.get(key, 0) == 0 and not any(
                k.startswith(f"{name}/alias:") for k in coverage
            ):
                print(f"FAIL {key}: no fsl macro matches this form (dead form)")
                errors += 1
                continue
            if key not in mods_seen:  # only aliases hit it; skip phantom checks
                continue
            for m in form.get("modifiers", []):
                if m not in mods_seen[key]:
                    print(f"FAIL {key}: modifier '{m}' never observed set (phantom modifier)")
                    errors += 1
            for o in form.get("operands", []):
                if o not in opers_seen[key]:
                    print(f"FAIL {key}: operand '{o}' never exercised (phantom operand)")
                    errors += 1

    bb, bberrors = extract_header.extract()
    for e in bberrors:
        print(f"ERROR bunny_build: {e}")
    errors += len(bberrors)
    errors += cross_diff(inv, bb, verbose)

    # ----- known-defect review report (informational; recorded in db provenance) ---
    print("\n--- known-defect review report (source/bench/owner review) ---")
    defects = {n: m for n, m in sorted(inv.items()) if m.get("defect")}
    print(f"defective macros in fsl header: {len(defects)}")
    for n, m in defects.items():
        print(f"  {n} (line {m['line']}): {m['defect']}")
    only_fsl = sorted(inv.keys() - bb.keys() - KNOWN_NON_INLINE)
    only_bb = sorted(bb.keys() - inv.keys())
    print(f"excluded directive wrappers: {sorted(excluded)}")
    print(f"non-inline in bunny_build (verified separately): {len(KNOWN_NON_INLINE)}")
    if only_fsl:
        print(f"only in fsl header ({len(only_fsl)}): {only_fsl}")
    if only_bb:
        print(f"only in bunny_build ({len(only_bb)}): {only_bb}")

    print(f"\n{len(inv)} fsl macros checked; per-form coverage:")
    for key in sorted(coverage):
        print(f"  {key:24s} {coverage[key]:4d}")
    if errors:
        print(f"\n{errors} error(s)")
        return 1
    print("\nAll fsl header encodings verified: fsl <-> ISA db <-> bunny_build agree.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
