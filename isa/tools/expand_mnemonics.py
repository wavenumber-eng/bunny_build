"""Expand the db's mnemonic patterns and verify them against the fsl name list.

Usage:  uv run python isa/tools/expand_mnemonics.py [--header PATH] [--verbose]

The ADR (isa-adr-0001, Mnemonic patterns) requires that expanding every form's
pattern reproduces the historical E_* name list exactly.  The fsl header is
that list's ground truth (1502 macros, via extract_fsl).  This tool checks a
strictly stronger property: every expanded name must ALSO predict its macro's
base encoding word bit-for-bit from the pattern's field bindings.  A pattern
that spells the right names with the wrong bindings cannot pass.

Pattern notation (v2 — extends the ADR's original notation; see the
isa/README.md mnemonic section):

  literal      copied to the name
  [TEXT]       optional token, bound to a field: one name with TEXT (field=1;
               for cond: the COND_ form taking a cond argument) and one
               without (field=0 / unconditional)
  {A|B|...}    alternation, bound to a field: one name per alternative, the
               bound field taking the alternative's value (its index by
               default; `NAME=n` sets it explicitly; an empty alternative
               contributes no text)

Bracket groups bind positionally to `binds` entries, left to right.  A form
may declare `mnemonic = {...}` or `mnemonics = [{...}, ...]`; each entry may
carry `when = { field = value, ... }` fixing fields non-positionally (used
where token ORDER depends on a field, e.g. rshift's RLSL_ADD vs ADD_RLSL).
Aliases expand as `E_[COND_]<name>` when their form has a cond modifier.

Reading a green result, two caveats:

  - Zero-valued bindings contribute no bits to the predicted base word, so a
    binding whose every enumerated value is 0 is not exercised by the base
    check (harmless - zero means "token absent" - but a green run only
    verifies the nonzero side of each binding).
  - For the 9 known-defective fsl macros (extract_fsl.DEFECTS), prediction is
    checked against the *repaired* intended encoding, not the uncompilable
    text as written - those remain adjudication items regardless of this
    check's result.
"""
from __future__ import annotations

import re
import sys
from itertools import product
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import extract_fsl  # noqa: E402
from validate import load  # noqa: E402
from verify_encodings import encode, form_mask_match  # noqa: E402

GROUP = re.compile(r"\[([^]]*)\]|\{([^}]*)\}")


def parse_pattern(pattern: str) -> list:
    """Split into ('lit', text) / ('opt', text) / ('alt', [(text, value), ...])."""
    parts: list = []
    pos = 0
    for m in GROUP.finditer(pattern):
        if m.start() > pos:
            parts.append(("lit", pattern[pos : m.start()]))
        if m.group(1) is not None:
            parts.append(("opt", m.group(1)))
        else:
            alts = []
            for i, alt in enumerate(m.group(2).split("|")):
                text, _, val = alt.partition("=")
                alts.append((text, int(val) if val else i))
            parts.append(("alt", alts))
        pos = m.end()
    if pos < len(pattern):
        parts.append(("lit", pattern[pos:]))
    return parts


def expand(pattern: str, binds: list[str], when: dict[str, int]) -> list[tuple[str, dict]]:
    """Return [(name, {field: value, ...}), ...] for every combination.

    cond is special: value None means the COND_ token is present and the value
    comes from a macro argument (not baked into the base word).
    """
    parts = parse_pattern(pattern)
    groups = [p for p in parts if p[0] != "lit"]
    if len(groups) != len(binds):
        raise ValueError(f"{pattern}: {len(groups)} groups but {len(binds)} binds")

    choices: list[list[tuple[str, int | None]]] = []
    for (kind, payload), field in zip(groups, binds):
        if kind == "opt":
            absent = ("", None if field == "cond" else 0)
            present = (payload, None) if field == "cond" else (payload, 1)
            choices.append([absent, present])
        else:
            choices.append([(text, val) for text, val in payload])

    out = []
    for combo in product(*choices):
        name = ""
        values: dict[str, int] = dict(when)
        sel: list[tuple[str, object]] = [(f, v) for f, v in when.items()]
        gi = 0
        skip = False
        for kind, payload in parts:
            if kind == "lit":
                name += payload
                continue
            text, val = combo[gi]
            field = binds[gi]
            gi += 1
            name += text
            if field == "cond":
                if text:  # COND_ token present; cond value comes from an argument
                    values["cond"] = None
                    sel.append(("cond", None))
                continue
            if field in values and values[field] != val:
                skip = True  # when-guard pins this field to a different value
                break
            values[field] = val
            sel.append((field, val))
        if not skip:
            out.append((name, values, sel))
    return out


def expected_base(form: dict, fields: dict, values: dict) -> int:
    _, match = form_mask_match(form)
    word = match
    for field, val in values.items():
        if val is None:  # cond supplied as a macro argument; base uses EU=0
            continue
        word |= encode(fields[field], val)
    return word


def main() -> int:
    argv = sys.argv[1:]
    verbose = "--verbose" in argv
    header = extract_fsl.DEFAULT_HEADER
    if "--header" in argv:
        header = Path(argv[argv.index("--header") + 1])

    arch, fields, opcodes = load()
    consts, inv, excluded, exterrors = extract_fsl.extract(header)
    for e in exterrors:
        print(f"ERROR {e}")
    errors = len(exterrors)

    produced: dict[str, tuple[str, int]] = {}  # name -> (origin, expected base)

    def emit(name: str, origin: str, base: int) -> None:
        nonlocal errors
        if name in produced:
            print(f"FAIL {name}: produced by both {produced[name][0]} and {origin}")
            errors += 1
            return
        produced[name] = (origin, base)

    for opname, op in opcodes.items():
        for form in op.get("forms", []):
            specs = form.get("mnemonics") or ([form["mnemonic"]] if "mnemonic" in form else [])
            if not specs:
                print(f"FAIL {opname}/{form['name']}: no mnemonic pattern")
                errors += 1
                continue
            for spec in specs:
                when = spec.get("when", {})
                try:
                    names = expand(spec["pattern"], spec.get("binds", []), when)
                except ValueError as e:
                    print(f"FAIL {opname}/{form['name']}: {e}")
                    errors += 1
                    continue
                for name, values, _sel in names:
                    emit(name, f"{opname}/{form['name']}", expected_base(form, fields, values))
        for alias in op.get("aliases", []):
            form = next(f for f in op["forms"] if f["name"] == alias["form"])
            base = expected_base(form, fields, {k: v for k, v in alias.get("preset", {}).items()})
            emit(f"E_{alias['name']}", f"{opname}/alias:{alias['name']}", base)
            if "cond" in form.get("modifiers", []):
                emit(f"E_COND_{alias['name']}", f"{opname}/alias:{alias['name']}", base)

    fsl_names = set(inv)
    missing = sorted(fsl_names - produced.keys())
    extra = sorted(produced.keys() - fsl_names)
    for name in missing:
        print(f"FAIL missing: fsl {name} (line {inv[name]['line']}) not produced by any pattern")
    for name in extra:
        print(f"FAIL extra: {name} (from {produced[name][0]}) not in fsl header")
    errors += len(missing) + len(extra)

    both = produced.keys() & fsl_names
    basefails = 0
    for name in sorted(both):
        want = inv[name]["base"]
        got = produced[name][1]
        if got != want:
            print(f"FAIL base {name}: pattern predicts 0x{got:08x}, fsl macro is 0x{want:08x}")
            basefails += 1
        elif verbose:
            print(f"ok   {name:36s} 0x{want:08x}  ({produced[name][0]})")
    errors += basefails

    print(
        f"\n{len(produced)} names expanded, {len(fsl_names)} in fsl header: "
        f"{len(missing)} missing, {len(extra)} extra, {basefails} base mismatches"
    )
    if errors:
        print(f"{errors} error(s)")
        return 1
    print("Mnemonic expansion reproduces the historical name list exactly, bases verified.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
