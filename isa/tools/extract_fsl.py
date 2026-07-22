"""Extract encoding values from a supplied reference macro header.

Usage:  uv run python isa/tools/extract_fsl.py [--header PATH] [out.json]

Parses every `#define E_*` macro in the reference header and recovers,
by the same numeric probing extract_header.py uses on the bunny_build encoders:

  - base:   the emitted word with every argument = 0 (cond = EU = 0)
  - fields: per argument, value_bit -> [instr_bits]

Uses the bundled reference header by default. Override it with --header or
BUNNY_BUILD_REFERENCE_HEADER.

Macro body shapes handled (anything else is a loud ERROR, never a silent drop):

  - function-like `%c0` constant-expression form (the ~1490 common case)
  - object-like `%c0` form (E_NOP)
  - stringized gas-expression form (E_GOTO family): the `.word` string is
    reassembled with gas precedence, where `<<` binds tighter than `+` (the
    opposite of C), so `" #a21 "<<9"` becomes `(a21<<9)`
  - E_DCD / E_DCD_VAL / E_LABEL are assembler-directive wrappers, not
    instructions: recorded under "excluded"

Known-defective macros (see DEFECTS) are parsed as *intended* — with the
minimal documented repair applied — and carry a `"defect"` note describing why
the macro as written cannot compile/expand.  They are review items, not silent
fixes: verify_fsl.py lists them in its known-defect review report.

Register/condition/bit-slice constants are taken from the header's own
#defines so the extraction is self-consistent; verify_fsl.py separately diffs
those constants against arch.toml.
"""
from __future__ import annotations

import json
import os
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BUNDLED_HEADER = ROOT / "test/camera_reference_generator__320_240_whole_buf/320_240_whole_buf/source/fsl_ezh_armclang.h"
DEFAULT_HEADER = Path(os.environ.get("BUNNY_BUILD_REFERENCE_HEADER", str(BUNDLED_HEADER)))
DIRECTIVES = {"E_DCD", "E_DCD_VAL", "E_LABEL"}
M32 = 0xFFFFFFFF

# Macros that are broken as written in the header.  Each entry: the defect
# description (goes into the JSON and known-defect review report) and regex
# repairs applied to the expression so the *intended* encoding can be probed.
ANDOR_DEFECT = (
    "missing '+' between (rsrc<<14) and (rand<<20) - expands to (int)(int), "
    "cannot compile; '+' assumed"
)
DEFECTS: dict[str, tuple[str, list[tuple[str, str]]]] = {
    "E_ANDOR": (ANDOR_DEFECT, [(r"\)\s+\(", ") + (")]),
    "E_ANDORS": (ANDOR_DEFECT, [(r"\)\s+\(", ") + (")]),
    "E_COND_ANDOR": (ANDOR_DEFECT, [(r"\)\s+\(", ") + (")]),
    "E_COND_ANDORS": (ANDOR_DEFECT, [(r"\)\s+\(", ") + (")]),
    "E_MODIFY_GPO_BYTE": (
        "body uses ordmask/xordmask but parameters are ormask/xormask - "
        "undeclared identifiers, cannot compile; parameters assumed",
        [(r"\bordmask\b", "ormask"), (r"\bxordmask\b", "xormask")],
    ),
}
# Every COND+NRA hold variant shares the same copy-paste defect: a space
# before the parameter list makes it an object-like macro that can never
# expand as intended.
SPACE_DEFECT = (
    "space before parameter list makes this an object-like macro that "
    "can never expand; function-like intent assumed"
)
for _n in (
    "E_COND_VECTORED_HOLD_NRA",
    "E_COND_VECTORED_HOLD_LV_NRA",
    "E_COND_ACC_VECTORED_HOLD_NRA",
    "E_COND_ACC_VECTORED_HOLD_LV_NRA",
):
    DEFECTS[_n] = (SPACE_DEFECT, [])

CONST = re.compile(r"^#define\s+(\w+)\s+(0[xX][0-9a-fA-F]+|\d+)\s*$")
DEFINE = re.compile(r"^#define\s+(E_\w+)(.*)$", re.S)


def strip_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    return re.sub(r"//[^\n]*", "", text)


def balanced(text: str, start: int) -> tuple[str, int]:
    """Return the contents of the paren group opening at text[start] == '('."""
    assert text[start] == "(", text[start : start + 20]
    depth = 0
    for i in range(start, len(text)):
        if text[i] == "(":
            depth += 1
        elif text[i] == ")":
            depth -= 1
            if depth == 0:
                return text[start + 1 : i], i + 1
    raise ValueError(f"unbalanced parens at {start}")


def gas_expr(asm_arg: str) -> str:
    """Rebuild the expression from a stringized `.word` gas line.

    Tokens are quoted string pieces and `#arg` stringize operators.  gas gives
    `<<` higher precedence than `+`, so a `#arg` immediately followed by a
    string piece starting with `<<N` is folded into `(arg<<N)`.
    """
    parts = re.findall(r'"([^"]*)"|#\s*(\w+)', asm_arg)
    expr = ""
    for literal, arg in parts:
        expr += f"\x00{arg}\x00" if arg else literal
    if not expr.startswith(".word"):
        raise ValueError(f"not a .word string: {asm_arg!r}")
    expr = expr[len(".word") :]
    expr = re.sub(r"\x00(\w+)\x00\s*<<\s*(\w+)", r"(\1<<\2)", expr)
    return re.sub(r"\x00(\w+)\x00", r"(\1)", expr)


def direct_word_wrapper(text: str) -> bool:
    """Accept one unconditional E_DCD definition (a file include guard is OK)."""
    guard = re.match(r"\s*#ifndef\s+(\w+)\s*\n\s*#define\s+\1\b", text)
    guard_name = guard.group(1) if guard else None
    conditional = []
    definitions = []
    for line in text.splitlines():
        directive = re.match(r"\s*#\s*(\w+)\b(.*)", line)
        if not directive:
            continue
        command, rest = directive.groups()
        if command in {"if", "ifdef", "ifndef"}:
            conditional.append(command == "ifndef" and not conditional and rest.strip() == guard_name)
        elif command in {"else", "elif"} and conditional:
            conditional[-1] = False
        elif command == "endif" and conditional:
            conditional.pop()
        elif command == "undef" and rest.strip() == "E_DCD":
            return False
        elif command == "define" and re.match(r"\s+E_DCD\b", rest):
            if conditional and conditional != [True]:
                return False
            definitions.append(line)
    return len(definitions) == 1 and bool(re.fullmatch(
        r'\s*#define\s+E_DCD\((\w+)\)\s*__asm\("\.word "\s*#\1\)\s*',
        definitions[0],
    ))


def parse_header(path: Path) -> tuple[dict[str, int], dict[str, dict], dict[str, int], list[str]]:
    """Return (constants, macros, excluded_lines, errors)."""
    raw = path.read_text(encoding="utf-8", errors="replace")
    text = strip_comments(raw.replace("\\\n", " "))
    # An E_DCD wrapper is equivalent only when it emits its argument unchanged.
    direct_word = direct_word_wrapper(text)
    consts: dict[str, int] = {}
    macros: dict[str, dict] = {}
    excluded: dict[str, int] = {}
    errors: list[str] = []

    for lineno, line in enumerate(text.splitlines(), 1):
        line = line.strip()
        if not line.startswith("#define"):
            continue
        m = CONST.match(line)
        if m:
            consts[m.group(1)] = int(m.group(2), 0)
            continue
        m = DEFINE.match(line)
        if not m:
            continue  # non-E_ function-like helpers, include guard, etc.
        name, rest = m.group(1), m.group(2)
        if name in DIRECTIVES:
            excluded[name] = lineno
            continue

        args: list[str] = []
        space_defect = False
        if rest.startswith("("):  # function-like: no space before the paren
            argspec, end = balanced(rest, 0)
            args = [a.strip() for a in argspec.split(",") if a.strip()]
            rest = rest[end:]
        else:
            rest = rest.lstrip()
            if rest.startswith("("):  # space crept in: broken object-like macro
                argspec, end = balanced(rest, 0)
                inner = [a.strip() for a in argspec.split(",") if a.strip()]
                if inner and all(re.fullmatch(r"\w+", a) for a in inner):
                    args = inner
                    rest = rest[end:].lstrip()
                    if name not in DEFECTS:
                        errors.append(
                            f"line {lineno}: {name}: object-like macro with "
                            "parameter-list-shaped body not in DEFECTS"
                        )
                        continue
                    space_defect = True

        i = rest.find("__asm")
        directive = re.fullmatch(r"\s*E_DCD\s*(\(.*\))\s*", rest)
        if i < 0 and not directive:
            errors.append(f"line {lineno}: {name}: no __asm in body")
            continue
        try:
            if directive:
                if not direct_word:
                    raise ValueError("E_DCD must emit its argument unchanged")
                expr, _ = balanced(directive.group(1), 0)
            else:
                asm_arg, _ = balanced(rest, rest.index("(", i))
                if "%c0" in asm_arg:
                    j = asm_arg.index('"i"')
                    expr, _ = balanced(asm_arg, asm_arg.index("(", j))
                else:
                    expr = gas_expr(asm_arg)
        except (ValueError, AssertionError) as e:
            errors.append(f"line {lineno}: {name}: {e}")
            continue
        defect = SPACE_DEFECT if space_defect else None
        if name in DEFECTS:
            description, repairs = DEFECTS[name]
            for pat, rep in repairs:
                expr, n = re.subn(pat, rep, expr)
                if n:
                    defect = description
        macros[name] = {"args": args, "expr": expr, "line": lineno, "defect": defect}

    return consts, macros, excluded, errors


def probe(macros: dict[str, dict], consts: dict[str, int]) -> tuple[dict[str, dict], list[str]]:
    out: dict[str, dict] = {}
    errors: list[str] = []
    for name, mac in macros.items():
        args = mac["args"]

        def ev(overrides: dict[str, int]) -> int:
            env = dict(consts)
            env.update({a: 0 for a in args})
            env.update(overrides)
            return eval(mac["expr"], {"__builtins__": {}}, env) & M32  # noqa: S307 - trusted header

        try:
            base = ev({})
        except Exception as e:
            errors.append(f"{name} (line {mac['line']}): cannot evaluate ({e})")
            continue

        fields: dict[str, dict[int, list[int]]] = {}
        for a in args:
            fmap: dict[int, list[int]] = {}
            for k in range(32):
                word = ev({a: 1 << k})
                diff = word ^ base
                if not diff or diff & base:
                    continue  # no effect, or out-of-range probe carried into base
                fmap[k] = [b for b in range(32) if diff >> b & 1]
            fields[a] = fmap

        entry = {"args": args, "base": base, "fields": fields, "line": mac["line"]}
        if mac["defect"]:
            entry["defect"] = mac["defect"]
        out[name] = entry
    return out, errors


def extract(header: Path = DEFAULT_HEADER):
    """Return (constants, inventory, excluded, errors) for the fsl header."""
    if header is None:
        raise ValueError("Supply --header or set BUNNY_BUILD_REFERENCE_HEADER")
    consts, macros, excluded, errors = parse_header(header)
    inv, perrors = probe(macros, consts)
    return consts, inv, excluded, errors + perrors


def main() -> int:
    argv = sys.argv[1:]
    header = DEFAULT_HEADER
    if "--header" in argv:
        i = argv.index("--header")
        header = Path(argv[i + 1])
        del argv[i : i + 2]

    consts, inv, excluded, errors = extract(header)
    for e in errors:
        print(f"ERROR {e}")
    payload = json.dumps(
        {"constants": consts, "macros": inv, "excluded": excluded}, indent=0, sort_keys=True
    )
    if argv:
        Path(argv[0]).write_text(payload, encoding="utf-8")
        print(f"{len(inv)} macros -> {argv[0]}")
    else:
        print(payload)
    if errors:
        print(f"{len(errors)} anomalies")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
