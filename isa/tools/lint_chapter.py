"""Lint a prose documentation chapter in docs_src/.

Enforces the contract in docs/design/isa-doc-generator.html so that chapter
defects fail loudly instead of relying on ad-hoc checking:

  1. Front matter parses as TOML and carries the required keys.
  2. Every [[E_NAME]] cross-link resolves against the expanded mnemonic set.
  3. Every body section has a [[provenance]] entry, and no provenance or
     [[unverified]] entry names a section that does not exist.
  4. No intra-page anchor is broken.
  5. No non-public source id appears in body text (the "synthesize, don't copy"
     rule, enforced at the file level rather than by author discipline).
  6. Every [[unverified]] entry carries an explicit status from a known set, so
     a settled item can never render as an open hedge.
  7. Bare E_* tokens in the body that are neither real mnemonics nor declared
     exceptions fail the run - they are usually typos in a code example.
  8. Renderable provenance detail strings and [[unverified]] claim metadata do
     not name non-public source ids, source titles, or known private source
     filenames.

Usage:
    uv run python isa/tools/lint_chapter.py [docs_src/*.md ...]

Exits non-zero on any error.
"""

from __future__ import annotations

import re
import sys
import tomllib
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import expand_mnemonics as em  # noqa: E402
import pc_model  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
VALID_STATUS = {"open", "corroborated", "resolved"}
REQUIRED_META = ("type", "id", "title", "status")

# E_* tokens that legitimately appear in prose without being real mnemonics.
# Each needs a reason, so the list cannot quietly become a dumping ground.
ALLOWED_NON_MNEMONICS = {
    "E_GPO_BYTE_MODIFY": "cited as the name that does NOT exist (real one is E_MODIFY_GPO_BYTE)",
    "E_LOAD_32IMM": "bunny_build pseudo-instruction, documented in the assembler guide",
    "E_DCD": "assembler directive, not a hardware instruction",
    "E_DCD_VAL": "assembler directive, not a hardware instruction",
    "E_LABEL": "assembler directive, not a hardware instruction",
    "E__END": "bunny_build pseudo-instruction (park pattern)",
    "E_END": "bunny_build pseudo-instruction (public park helper spelling)",
}


def mnemonic_set() -> set[str]:
    """Expand every mnemonic pattern in the ISA database."""
    _arch, fields, opcodes = em.load()
    names: set[str] = set()
    for op in opcodes.values():
        for form in op.get("forms", []):
            specs = form.get("mnemonics") or (
                [form["mnemonic"]] if "mnemonic" in form else []
            )
            for spec in specs:
                for name, _values, _sel in em.expand(
                    spec["pattern"], spec.get("binds", []), spec.get("when", {})
                ):
                    names.add(name)
        for alias in op.get("aliases", []):
            form = next(f for f in op["forms"] if f["name"] == alias["form"])
            names.add(f"E_{alias['name']}")
            if "cond" in form.get("modifiers", []):
                names.add(f"E_COND_{alias['name']}")
    return names


def peripheral_symbols() -> set[str]:
    """Register-address symbols bunny_build actually defines.

    E_PER_READ/E_PER_WRITE take a peripheral address, and in practice that is a
    macro from include/ezh_arch.h. Published NXP listings spell several of them
    differently (EZH_BREAKADDR vs EZHBREAKADDR, EZH_ARM2EZH vs ARM2EZH), so a
    name copied out of a datasheet compiles nowhere. These are not E_* tokens,
    so the mnemonic check never sees them.
    """
    header = ROOT / "include/ezh_arch.h"
    if not header.exists():
        return set()
    text = header.read_text(encoding="utf-8", errors="ignore")
    return set(re.findall(r"^\s*#\s*define\s+([A-Za-z_]\w*)", text, re.M))


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


def non_public_markers() -> set[str]:
    arch = tomllib.loads((ROOT / "isa/ezh_b/arch.toml").read_text(encoding="utf-8"))
    markers: set[str] = set()
    for key, meta in arch.get("sources", {}).items():
        if meta.get("public"):
            continue
        markers.add(key)
        title = meta.get("title")
        if title:
            markers.add(title)
        markers.update(NONPUBLIC_ALIASES.get(key, set()))
    return markers


def marker_hits(text: str, markers: set[str]) -> list[str]:
    lowered = text.lower()
    return sorted(marker for marker in markers if marker.lower() in lowered)


#: Operands of these forms are register-address symbols, not numbers.
PER_CALL = re.compile(
    r"\bE_(?:COND_)?PER_(?:READ|WRITE)\s*\(\s*[^,]+,\s*([A-Za-z_]\w*)\s*\)"
)


def lint(path: Path, names: set[str], nonpublic: set[str]) -> tuple[list[str], list[str]]:
    errors: list[str] = []
    warnings: list[str] = []
    text = path.read_text(encoding="utf-8")

    if not text.startswith("+++"):
        return [f"{path}: missing +++ TOML front matter"], []
    parts = text.split("+++", 2)
    if len(parts) < 3:
        return [f"{path}: unterminated +++ front matter"], []

    try:
        meta = tomllib.loads(parts[1])
    except tomllib.TOMLDecodeError as exc:
        return [f"{path}: front matter is not valid TOML: {exc}"], []
    body = parts[2]

    for key in REQUIRED_META:
        if key not in meta:
            errors.append(f"{path}: front matter missing required key '{key}'")

    # Top-level sections carry provenance; anchors may live at any heading
    # level, so link targets and provenance targets are collected separately.
    sections = re.findall(r"^##\s+(.*?)\s*\{#([a-z0-9-]+)\}\s*$", body, re.M)
    ids = {anchor for _title, anchor in sections}
    all_anchors = set(
        re.findall(r"^#{2,4}\s+.*?\{#([a-z0-9-]+)\}\s*$", body, re.M)
    )
    if not ids:
        errors.append(f"{path}: no '## Title {{#anchor}}' sections found")

    dupes = [a for _t, a in sections if [x for _y, x in sections].count(a) > 1]
    for anchor in sorted(set(dupes)):
        errors.append(f"{path}: duplicate section anchor '{anchor}'")

    # Provenance coverage.
    prov_sections = {p.get("section") for p in meta.get("provenance", [])}
    for anchor in sorted(ids - prov_sections):
        errors.append(f"{path}: section '{anchor}' has no [[provenance]] entry")
    for anchor in sorted(prov_sections - ids):
        errors.append(f"{path}: [[provenance]] names unknown section '{anchor}'")
    for entry in meta.get("provenance", []):
        detail = entry.get("detail", "")
        for marker in marker_hits(detail, nonpublic):
            errors.append(
                f"{path}: [[provenance]] section '{entry.get('section', '<unknown>')}' "
                f"detail names non-public source marker '{marker}'"
            )

    # Unverified entries.
    for entry in meta.get("unverified", []):
        ident = entry.get("id", "<no id>")
        if entry.get("section") not in ids:
            errors.append(
                f"{path}: [[unverified]] '{ident}' names unknown section "
                f"'{entry.get('section')}'"
            )
        status = entry.get("status")
        if status is None:
            errors.append(f"{path}: [[unverified]] '{ident}' has no status field")
        elif status not in VALID_STATUS:
            errors.append(
                f"{path}: [[unverified]] '{ident}' has status '{status}', "
                f"expected one of {sorted(VALID_STATUS)}"
            )
        for field in ("claim", "basis", "resolve_by"):
            if not entry.get(field):
                errors.append(f"{path}: [[unverified]] '{ident}' missing '{field}'")
                continue
            for marker in marker_hits(str(entry[field]), nonpublic):
                errors.append(
                    f"{path}: [[unverified]] '{ident}' field '{field}' "
                    f"names non-public source marker '{marker}'"
                )

    # Cross-links.
    linked = re.findall(r"\[\[([^\]]+)\]\]", body)
    for name in sorted(set(linked)):
        if name not in names:
            errors.append(f"{path}: unresolved cross-link [[{name}]]")

    # Intra-page anchors may target any heading level, not just top-level ones.
    for anchor in sorted(set(re.findall(r"\]\(#([a-z0-9-]+)\)", body))):
        if anchor not in all_anchors:
            errors.append(f"{path}: broken intra-page anchor '#{anchor}'")

    # Confidential source containment.
    for sid in marker_hits(body, nonpublic):
        errors.append(
            f"{path}: non-public source marker '{sid}' appears in body text "
            "(provenance belongs in front matter)"
        )

    # Bare E_* tokens outside link syntax.
    stripped = re.sub(r"\[\[[^\]]+\]\]", "", body)
    for token in sorted(set(re.findall(r"\bE_[A-Z0-9_]+", stripped))):
        if token in names or token in ALLOWED_NON_MNEMONICS:
            continue
        errors.append(f"{path}: bare token '{token}' is not a known mnemonic")

    # Register-address symbols passed to E_PER_READ / E_PER_WRITE.
    symbols = peripheral_symbols()
    if symbols:
        for sym in sorted(set(PER_CALL.findall(body))):
            if sym in symbols:
                continue
            near = [s for s in symbols if s.replace("_", "") == sym.replace("_", "")]
            hint = f"; did you mean '{near[0]}'?" if near else ""
            errors.append(
                f"{path}: E_PER_* operand '{sym}' is not defined in "
                f"include/ezh_arch.h{hint}"
            )

    return errors, warnings


#: PC-relative forms the resolver understands, mapped to their immediate units.
#: The immediate is captured as text because sources idiomatically spell byte
#: constants as a product ("2*4" meaning two instruction words).
PC_FORMS = (
    (re.compile(r"\bE_(?:COND_)?(?:ADD|SUB)_IMMS?\s*\(\s*[^,]+,\s*PC\s*,\s*([-\d\s*]+)\)"), "bytes"),
    (re.compile(r"\bE_(?:COND_)?LDR\s*\(\s*[^,]+,\s*PC\s*,\s*([-\d\s*]+)\)"), "words"),
)

def code_blocks(body: str) -> list[str]:
    """Return the contents of every fenced code block.

    Scanned line by line rather than by pairing fences with a regex. A regex
    that pairs bare ``` fences silently mis-pairs as soon as the document also
    uses a tagged fence (```c), shifting every subsequent block and skipping
    content without any error - which is how PC-relative lines in two chapters
    went unresolved while the run still reported success.
    """
    blocks: list[str] = []
    current: list[str] | None = None
    for line in body.splitlines():
        if line.startswith("```"):
            if current is None:
                current = []          # opening fence, tagged or not
            else:
                blocks.append("\n".join(current))
                current = None
            continue
        if current is not None:
            current.append(line)
    return blocks


def fence_errors(path: Path, body: str) -> list[str]:
    count = sum(1 for line in body.splitlines() if line.startswith("```"))
    if count % 2:
        return [f"{path}: unterminated fenced code block"]
    return []


_IMM_EXPR = re.compile(r"^-?\d+(?:\s*\*\s*\d+)*$")


def parse_imm(text: str) -> int | None:
    """Evaluate an immediate written as an integer or a product of integers."""
    text = text.strip()
    if not _IMM_EXPR.match(text):
        return None
    value = 1
    negative = text.startswith("-")
    for factor in text.lstrip("-").split("*"):
        value *= int(factor.strip())
    return -value if negative else value


def pc_report(path: Path, body: str) -> list[str]:
    """Resolve PC-relative operands in fenced code blocks to instruction deltas.

    Informational, not pass/fail: the linter cannot know what a prose comment
    intended. What it can do is show the resolved target for every PC-relative
    line, so a claim like "lands two instructions past the body" is checkable at
    a glance instead of by hand.
    """
    lines: list[str] = []
    for bi, block in enumerate(code_blocks(body), 1):
        instrs = [
            ln for ln in block.splitlines() if ln.strip().startswith("E_")
        ]
        for idx, ln in enumerate(instrs):
            for pattern, unit in PC_FORMS:
                m = pattern.search(ln)
                if not m:
                    continue
                imm = parse_imm(m.group(1))
                if imm is None:
                    lines.append(
                        f"    block {bi} line {idx + 1}: unparsed immediate "
                        f"'{m.group(1).strip()}' in {ln.strip()[:40]}"
                    )
                    continue
                addr = idx * pc_model.WORD
                target = (
                    pc_model.alu_imm_target(addr, imm)
                    if unit == "bytes"
                    else pc_model.ldr_word_target(addr, imm)
                )
                delta = pc_model.instr_delta(addr, target)
                tgt_idx = int(target // pc_model.WORD)
                where = (
                    instrs[tgt_idx].strip()
                    if 0 <= tgt_idx < len(instrs)
                    else "outside this excerpt"
                )
                lines.append(
                    f"    block {bi} line {idx + 1}: {ln.strip()[:46]:46s} "
                    f"-> {delta:+g} instr ({where[:40]})"
                )
    return lines


def main() -> int:
    args = [a for a in sys.argv[1:] if not a.startswith("-")]
    # The PC resolution report is on by default: it is the only thing that makes
    # an off-by-one-word claim visible, and leaving it opt-in meant a wrong
    # claim survived a review that the tool could already refute.
    show_pc = "--quiet" not in sys.argv[1:]
    paths = [Path(a) for a in args] if args else sorted((ROOT / "docs_src").glob("*.md"))
    if not paths:
        print("no chapters found in docs_src/")
        return 1

    missing = [p for p in paths if not p.exists()]
    for path in missing:
        print(f"FAIL  {path}: file not found")
    if missing:
        return 1

    names = mnemonic_set()
    nonpublic = non_public_markers()

    total_err = 0

    # The PC model underpins every PC-relative claim in every chapter; if it
    # stops reproducing the sources' worked examples, that is a hard failure.
    pc_failures = pc_model.selftest()
    for f in pc_failures:
        print(f"FAIL  pc_model: {f}")
    total_err += len(pc_failures)

    for path in paths:
        errors, warnings = lint(path, names, nonpublic)
        errors.extend(fence_errors(path, path.read_text(encoding="utf-8")))
        total_err += len(errors)
        for w in warnings:
            print(f"WARN  {w}")
        for e in errors:
            print(f"FAIL  {e}")
        if not errors:
            print(f"ok    {path} ({len(names)} mnemonics known)")
        if show_pc:
            report = pc_report(path, path.read_text(encoding="utf-8"))
            if report:
                print(f"  PC-relative resolutions in {path.name}:")
                print("\n".join(report))

    print()
    if total_err:
        print(f"{total_err} error(s)")
        return 1
    print("All chapter checks passed.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
