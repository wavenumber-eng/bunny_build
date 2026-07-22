"""Extract encoding ground truth from the bunny_build encoder header.

Usage:  uv run python isa/tools/extract_header.py [out.json]

Parses every `static inline void E_*(...)` in include/bunny_build__instr.h and
recovers, by numeric probing (no C parsing heuristics beyond the expression
grab):

  - base:   the emitted word with every argument = 0 (cond args use EU)
  - fields: per argument, a map value_bit -> [instr_bits], found by probing the
            argument with each single bit 1<<k and diffing against base

The header formulas do not mask their arguments, so probing an argument past its
architectural width shifts bits into base/neighbor positions. A probe whose diff
collides with base bits is therefore treated as out-of-range and simply not
recorded; the DB comparison later only consults the value bits the DB declares.

The JSON output is the header side of the three-way verify-encodings diff
(ISA db vs this header vs the original fsl header).
"""
from __future__ import annotations

import json
import re
import sys
import tomllib
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
HEADER = ROOT.parent / "include" / "bunny_build__instr.h"

# Body = optional pass-1 warning printf (the header author's "DOUBLE CHECK ENCODING" notes),
# then exactly one add_instruction call.
FUNC = re.compile(
    r"static inline void\s+(E_\w+)\s*\(([^)]*)\)\s*\{\s*"
    r"(?:if\s*\(bunny_build__pass_num\)\s*\{[^{}]*\}\s*)?"
    r"bunny_build__add_instruction\((.*?)\);\s*\}",
    re.S,
)
# Every inline E_* declaration, matched loosely — used to reconcile against FUNC
# so a body shape FUNC doesn't understand fails loudly instead of dropping out.
DECL = re.compile(r"^static inline void\s+(E_\w+)\s*\(", re.M)
M32 = 0xFFFFFFFF


def env_base() -> dict[str, int]:
    arch = tomllib.loads((ROOT / "ezh_b" / "arch.toml").read_text(encoding="utf-8"))
    env = {name: r["value"] for name, r in arch["registers"].items()}
    env.update({name: c["value"] for name, c in arch["conditions"].items()})
    env.update({name: b["value"] for name, b in arch["bit_slice_cfg"].items()})
    return env


def extract() -> tuple[dict[str, dict], list[str]]:
    """Return (inventory, errors) for the bunny_build encoder header."""
    text = HEADER.read_text(encoding="utf-8", errors="replace")
    base_env = env_base()
    out: dict[str, dict] = {}
    errors: list[str] = []

    matches = FUNC.findall(text)
    declared = set(DECL.findall(text))
    dropped = declared - {name for name, _, _ in matches}
    for name in sorted(dropped):
        errors.append(f"{name}: declaration found but body shape not understood by extractor")

    for name, argspec, expr in matches:
        args = [a.split()[-1].lstrip("*") for a in argspec.split(",") if a.strip() and a.strip() != "void"]
        pyexpr = expr.replace("//", "#").split("#")[0]

        def ev(overrides: dict[str, int]) -> int:
            env = dict(base_env)
            env.update({a: 0 for a in args})
            env.update(overrides)
            return eval(pyexpr, {"__builtins__": {}}, env) & M32  # noqa: S307 - trusted repo header

        try:
            base = ev({})
        except Exception as e:  # unparseable formula: surface, don't skip silently
            errors.append(f"{name}: cannot evaluate ({e})")
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

        out[name] = {"args": args, "base": base, "fields": fields}

    return out, errors


def main() -> int:
    out, errors = extract()
    for e in errors:
        print(f"ERROR {e}")

    dest = Path(sys.argv[1]) if len(sys.argv) > 1 else None
    payload = json.dumps(out, indent=0, sort_keys=True)
    if dest:
        dest.write_text(payload, encoding="utf-8")
        print(f"{len(out)} functions -> {dest}")
    else:
        print(payload)
    if errors:
        print(f"{len(errors)} anomalies")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
