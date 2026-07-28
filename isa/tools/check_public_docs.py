"""Scan generated public documentation for non-public source markers.

This is the last gate before publishing generated HTML. The prose linter checks
chapter source files before rendering; this tool checks the artifact that would
actually ship. It is meant to run from gen_docs.py --check after docs/html/ has
been generated.

Usage:
    uv run python isa/tools/check_public_docs.py docs/html
"""

from __future__ import annotations

import argparse
import sys
import tomllib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
PUBLIC_EXTS = {".html", ".css", ".js", ".json", ".txt", ".md", ".svg"}

NONPUBLIC_ALIASES = {
    "spec_b_06": {
        "Arch B spec",
        "Architecture B specification",
        "the architecture specification",
        "EZHandler Arch B",
        "PreRel0.6",
        "creator's spec",
        "creator review",
        "creator confirmation",
        "creator confirmation pending",
        "creator to adjudicate",
        "EZH creator",
        "EZH creator to adjudicate",
        "original header author",
        "hardware analysis",
        "hardware-adjudication",
        "advisory",
        "adjudication item",
        "adjudication list",
        "under adjudication",
        "internal source",
        "internal sources",
        "internal deck",
        "internal material",
        "spec-grounded",
    },
    "fsl_header": {
        "fsl_ezh_armclang.h",
    },
    "sv_tb": {
        "sv_tb",
        "ezh_tb_package.sv",
    },
}

CONFIDENTIAL_MARKERS = {
    "NXP confidential",
    "NXP proprietary",
}


def non_public_markers() -> set[str]:
    arch = tomllib.loads((ROOT / "isa/ezh_b/arch.toml").read_text(encoding="utf-8"))
    markers: set[str] = set(CONFIDENTIAL_MARKERS)
    for key, meta in arch.get("sources", {}).items():
        if meta.get("public"):
            continue
        markers.add(key)
        title = meta.get("title")
        if title:
            markers.add(title)
        markers.update(NONPUBLIC_ALIASES.get(key, set()))
    return markers


def iter_files(paths: list[Path]) -> list[Path]:
    files: list[Path] = []
    for path in paths:
        if not path.exists():
            raise FileNotFoundError(path)
        if path.is_file():
            files.append(path)
            continue
        files.extend(
            p for p in sorted(path.rglob("*"))
            if p.is_file() and p.suffix.lower() in PUBLIC_EXTS
        )
    return files


def line_hits(path: Path, markers: set[str]) -> list[str]:
    hits: list[str] = []
    text = path.read_text(encoding="utf-8", errors="ignore")
    lowered_markers = [(m, m.lower()) for m in sorted(markers)]
    for lineno, line in enumerate(text.splitlines(), 1):
        lowered_line = line.lower()
        for marker, lowered_marker in lowered_markers:
            if lowered_marker in lowered_line:
                hits.append(f"{path}:{lineno}: non-public marker '{marker}'")
    return hits


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "paths",
        nargs="*",
        type=Path,
        default=[ROOT / "docs/html"],
        help="Generated public files or directories to scan",
    )
    args = parser.parse_args()

    try:
        files = iter_files(args.paths)
    except FileNotFoundError as exc:
        print(f"FAIL  {exc.args[0]}: path not found")
        return 1

    if not files:
        print("FAIL  no public documentation files found")
        return 1

    markers = non_public_markers()
    failures: list[str] = []
    for path in files:
        failures.extend(line_hits(path, markers))

    for failure in failures:
        print(f"FAIL  {failure}")

    if failures:
        print(f"\n{len(failures)} public-doc marker hit(s)")
        return 1

    print(f"All public documentation checks passed ({len(files)} files scanned).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
