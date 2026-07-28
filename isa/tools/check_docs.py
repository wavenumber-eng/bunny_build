"""Scan generated public documentation for non-public source markers.

This is the last gate before publishing generated HTML. The prose linter checks
chapter source files before rendering; this tool checks the artifact that would
actually ship. It is meant to run from gen_docs.py --check after docs/html/ has
been generated.

Usage:
    uv run python isa/tools/check_docs.py docs/html
"""

from __future__ import annotations

import argparse
import html
import json
import os
import sys
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
PUBLIC_EXTS = {".html", ".css", ".js", ".json", ".txt", ".md", ".svg"}

SOURCE_PATTERNS = (
    r"\bspec_[a-z]_\d+\b", r"\bsv_[a-z]+\b",
    r"\bez[h]andler\b", r"\bpre[-_ ]?rel\d",
    r"\b\w+\.(?:docx|sv)\b", r"\bfsl_\w+\.h\b",
)


def non_public_markers() -> set[str]:
    markers = {
        "provenance", "public evidence", "public output", "source boundary",
        "non-public", "confidential", "proprietary", "internal source",
        "internal deck", "internal material", "creator review", "creator confirmation",
        "original header author", "adjudication", "advisory", "spec-grounded",
        "nxp-monkey", "pending enrichment", "discovery notes", "extraction gaps",
        "generated from", "isa/ezh_b/", "docs_src/",
        "the specification", "checked model", "source ranking",
        "database models", "improvement opportunity",
        "both headers", "real camera code", "spec table wording",
    }
    catalog = os.environ.get("BUNNY_BUILD_PRIVATE_MARKERS")
    if catalog:
        data = json.loads(Path(catalog).read_text(encoding="utf-8"))
        entries = data.get("markers") if isinstance(data, dict) else None
        if not isinstance(entries, list) or not entries or not all(
            isinstance(entry, str) and entry.strip() for entry in entries
        ):
            raise ValueError("private marker catalog must contain a nonempty list of strings")
        markers.update(entries)
    return markers


def source_marker_hits(text: str, markers: set[str]) -> list[str]:
    decoded = html.unescape(text)
    variants = {text.lower()}
    for separator in ("", " "):
        visible = re.sub(r"<[^>]+>", separator, decoded)
        variants.add(" ".join(visible.lower().split()))
    hits = {marker for marker in markers
            if any(" ".join(marker.lower().split()) in variant for variant in variants)}
    for pattern in SOURCE_PATTERNS:
        for variant in variants:
            hits.update(re.findall(pattern, variant))
    return sorted(hits)


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
    matched = set()
    for lineno, line in enumerate(text.splitlines(), 1):
        for marker in source_marker_hits(line, markers):
            hits.append(f"{path}:{lineno}: non-public marker '{marker}'")
            matched.add(marker)
    for marker in set(source_marker_hits(text, markers)) - matched:
        hits.append(f"{path}:1: non-public marker '{marker}' across markup or lines")
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

    try:
        markers = non_public_markers()
    except (OSError, ValueError) as exc:
        print(f"FAIL  cannot load private marker catalog: {exc}")
        return 1
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
