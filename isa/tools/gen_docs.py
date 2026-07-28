"""Generate the public EZH Architecture B static documentation site.

Usage:
    uv run python isa/tools/gen_docs.py
    uv run python isa/tools/gen_docs.py --check

The generated site is deterministic and offline-capable. It combines the
machine-readable ISA database under isa/ezh_b with reviewed Markdown chapters in
docs_src/. Rendered provenance is filtered to public sources only; private
source ids, private titles, and review-only notes remain in source metadata.
"""

from __future__ import annotations

import argparse
import filecmp
import html as html_lib
import json
import re
import shutil
import subprocess
import sys
import tempfile
import tomllib
from pathlib import Path
from typing import Any

import markdown
from jinja2 import Environment, FileSystemLoader, select_autoescape

sys.path.insert(0, str(Path(__file__).resolve().parent))

from expand_mnemonics import expand, expected_base  # noqa: E402
from validate import load, parse_range  # noqa: E402
from verify_encodings import encode, form_mask_match  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
DOCS_SRC = ROOT / "docs_src"
TEMPLATE_DIR = DOCS_SRC / "templates"
DEFAULT_OUT = ROOT / "docs" / "html"
VENDOR_DIR = DOCS_SRC / "vendor"
PLATFORM_DIR = ROOT / "isa" / "ezh_b" / "platform"
SENTINEL = ".ezh-docs-generated"

CHAPTER_IDS = ("architecture", "assembler", "cookbook")
PUBLIC_SCAN_EXTS = {".html", ".css", ".js", ".json", ".txt", ".md", ".svg"}
N_FIELD_COLORS = 6


class GenerationError(RuntimeError):
    """Raised when docs cannot be generated safely."""


def slugify(text: str) -> str:
    slug = re.sub(r"[^a-z0-9]+", "-", text.lower()).strip("-")
    return slug or "section"


def read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8")


def write_text(path: Path, text: str) -> None:
    text = "\n".join(line.rstrip() for line in text.splitlines()) + (
        "\n" if text.endswith("\n") else ""
    )
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8", newline="\n")


def html_id(text: str) -> str:
    return slugify(text.replace("_", "-"))


def markdown_text_to_html(text: str) -> str:
    converter = markdown.Markdown(
        extensions=["fenced_code", "tables", "attr_list"],
        output_format="html5",
    )
    return converter.convert(text)


def strip_markdown(text: str) -> str:
    text = re.sub(r"```.*?```", " ", text, flags=re.S)
    text = re.sub(r"\[\[([^\]]+)\]\]", r"\1", text)
    text = re.sub(r"\[([^\]]+)\]\([^)]+\)", r"\1", text)
    text = re.sub(r"[#*_`>{}\[\]|]", " ", text)
    text = re.sub(r"\s+", " ", text)
    return text.strip()


def strip_html(text: str) -> str:
    text = re.sub(r"<[^>]+>", " ", text)
    text = html_lib.unescape(text)
    text = re.sub(r"\s+", " ", text)
    return text.strip()


def first_sentence(text: str, max_len: int = 150) -> str:
    cleaned = re.sub(r"\s+", " ", text).strip()
    if not cleaned:
        return ""
    match = re.search(r"(?<=[.!?])\s+", cleaned)
    if match:
        cleaned = cleaned[: match.start()]
    if len(cleaned) > max_len:
        cleaned = cleaned[: max_len - 1].rstrip() + "..."
    return cleaned


def public_sources(arch: dict[str, Any]) -> dict[str, str]:
    out: dict[str, str] = {}
    for key, meta in arch.get("sources", {}).items():
        if meta.get("public"):
            out[key] = meta.get("title", key)
    return out


def public_provenance(
    entries: list[dict[str, Any]] | None, arch: dict[str, Any]
) -> list[dict[str, Any]]:
    public = public_sources(arch)
    rendered: list[dict[str, Any]] = []
    for entry in entries or []:
        src_ids = entry.get("sources")
        if src_ids is None and "source" in entry:
            src_ids = [entry["source"]]
        src_ids = list(src_ids or [])
        titles = [public[sid] for sid in src_ids if sid in public]
        if not titles:
            continue
        detail = str(entry.get("detail", "")).strip()
        if not detail:
            detail = "Public source evidence"
        rendered.append({"detail": detail, "sources": titles})
    return rendered


def parse_chapter(path: Path) -> dict[str, Any]:
    text = read_text(path)
    if not text.startswith("+++"):
        raise GenerationError(f"{path}: missing TOML front matter")
    parts = text.split("+++", 2)
    if len(parts) != 3:
        raise GenerationError(f"{path}: unterminated TOML front matter")
    try:
        meta = tomllib.loads(parts[1])
    except tomllib.TOMLDecodeError as exc:
        raise GenerationError(f"{path}: invalid TOML front matter: {exc}") from exc
    body = parts[2].lstrip()
    return {"path": path, "meta": meta, "body": body}


def chapter_paths() -> list[Path]:
    paths = [DOCS_SRC / f"{chapter_id}.md" for chapter_id in CHAPTER_IDS]
    missing = [p for p in paths if not p.exists()]
    if missing:
        joined = ", ".join(str(p) for p in missing)
        raise GenerationError(f"missing chapter source(s): {joined}")
    return paths


def resolve_instruction_links(body: str, mnemonic_to_opcode: dict[str, str]) -> str:
    def replace(match: re.Match[str]) -> str:
        name = match.group(1)
        opcode = mnemonic_to_opcode.get(name)
        if opcode is None:
            raise GenerationError(f"unresolved instruction link [[{name}]]")
        return f"[`{name}`](instructions.html#{opcode})"

    return re.sub(r"\[\[(E_[A-Z0-9_]+)\]\]", replace, body)


def clean_heading_title(raw: str) -> str:
    raw = re.sub(r"\s+\{#[a-z0-9-]+\}\s*$", "", raw)
    raw = re.sub(r"\[([^\]]+)\]\([^)]+\)", r"\1", raw)
    raw = raw.replace("`", "")
    raw = re.sub(r"[*_]", "", raw)
    return raw.strip()


def search_sections(chapter: dict[str, Any], href: str) -> list[dict[str, Any]]:
    body = chapter["body"]
    matches = list(re.finditer(r"^##\s+(.+?)\s*(?:\{#([a-z0-9-]+)\})?\s*$", body, re.M))
    docs: list[dict[str, Any]] = []
    chapter_id = chapter["meta"]["id"]
    chapter_title = chapter["meta"]["title"]
    for idx, match in enumerate(matches):
        start = match.end()
        end = matches[idx + 1].start() if idx + 1 < len(matches) else len(body)
        title = clean_heading_title(match.group(1))
        anchor = match.group(2) or slugify(title)
        section_body = strip_markdown(body[start:end])
        docs.append(
            {
                "id": f"section:{chapter_id}:{anchor}",
                "title": f"{chapter_title}: {title}",
                "url": f"{href}#{anchor}",
                "kind": "section",
                "summary": first_sentence(section_body),
                "body": section_body,
                "mnemonics": "",
                "tags": chapter_id,
            }
        )
    return docs


def describe(brief: str, selections: list[tuple[str, object]], fields: dict[str, Any]) -> str:
    clauses: list[str] = []
    for field_name, value in selections:
        field = fields.get(field_name)
        if field is None:
            continue
        if "value_briefs" in field:
            clause = field["value_briefs"].get(str(value), "")
        elif field_name == "cond" or value:
            clause = field.get("brief", "")
        else:
            clause = ""
        if clause:
            clauses.append(clause)
    return "; ".join([brief, *clauses]) if clauses else brief


def mnemonic_rows(op: dict[str, Any], form: dict[str, Any], fields: dict[str, Any]) -> list[dict[str, str]]:
    rows: list[dict[str, str]] = []
    specs = form.get("mnemonics") or ([form["mnemonic"]] if "mnemonic" in form else [])
    for spec in specs:
        brief = spec.get("brief") or form.get("brief", "")
        for name, values, selections in expand(
            spec["pattern"], spec.get("binds", []), spec.get("when", {})
        ):
            rows.append(
                {
                    "name": name,
                    "base_word": f"0x{expected_base(form, fields, values):08x}",
                    "notes": describe(brief, selections, fields),
                }
            )
    return sorted(rows, key=lambda row: row["name"])


def alias_rows_for_form(
    op: dict[str, Any], form: dict[str, Any], fields: dict[str, Any]
) -> list[dict[str, str]]:
    rows: list[dict[str, str]] = []
    for alias in op.get("aliases", []):
        if alias.get("form") != form.get("name"):
            continue
        _, match = form_mask_match(form)
        word = match
        for key, value in alias.get("preset", {}).items():
            word |= encode(fields[key], value)
        preset = ", ".join(
            f"{key}={value:#x}" if isinstance(value, int) and value >= 0 else f"{key}={value}"
            for key, value in alias.get("preset", {}).items()
        )
        note = alias.get("brief", "") or f"{alias['form']} form preset"
        if preset:
            note += f" ({alias['form']} form: {preset})"
        rows.append(
            {
                "name": f"E_{alias['name']}",
                "expands_to": f"0x{word:08x}",
                "notes": note,
            }
        )
        if "cond" in form.get("modifiers", []):
            rows.append(
                {
                    "name": f"E_COND_{alias['name']}",
                    "expands_to": f"0x{word:08x}",
                    "notes": note + "; conditional variant takes a cond argument",
                }
            )
    return sorted(rows, key=lambda row: row["name"])


def notes_list(notes: Any) -> list[str]:
    if notes is None:
        return []
    if isinstance(notes, list):
        return [str(note) for note in notes if str(note).strip()]
    text = str(notes).strip()
    return [text] if text else []


def field_tip(name: str, field: dict[str, Any]) -> str:
    desc = field.get("desc", "").strip()
    kind = field.get("kind", "field")
    slices = []
    for item in field.get("slices", []):
        slices.append(f"instr[{item['instr']}] <= value[{item['value']}]")
    pieces = [f"{name} ({kind})"]
    if desc:
        pieces.append(desc)
    if slices:
        pieces.append("; ".join(slices))
    if field.get("signed"):
        pieces.append("signed two's-complement value")
    if field.get("constraint"):
        pieces.append(f"constraint: {field['constraint']}")
    return " - ".join(pieces)


def bitfield_svg(form: dict[str, Any], fields: dict[str, Any], op_key: str) -> str:
    owner: list[tuple[str, str]] = [("rsvd", "0")] * 32

    for fixed in form.get("fixed", []):
        msb, lsb = parse_range(fixed["bits"])
        for bit in range(lsb, msb + 1):
            owner[bit] = ("fixed", str((fixed["value"] >> (bit - lsb)) & 1))

    for group in ("operands", "modifiers"):
        for name in form.get(group, []):
            for slice_item in fields[name]["slices"]:
                msb, lsb = parse_range(slice_item["instr"])
                for bit in range(lsb, msb + 1):
                    owner[bit] = ("field", name)

    segments: list[tuple[int, int, str, str]] = []
    bit = 31
    while bit >= 0:
        kind, label = owner[bit]
        lo = bit
        if kind == "fixed":
            while lo > 0 and owner[lo - 1][0] == "fixed":
                lo -= 1
            label = "".join(owner[idx][1] for idx in range(bit, lo - 1, -1))
        else:
            while lo > 0 and owner[lo - 1] == (kind, label):
                lo -= 1
        segments.append((bit, lo, kind, label))
        bit = lo - 1

    width = 26
    height = 34
    tick = 12
    parts = [
        (
            f'<svg xmlns="http://www.w3.org/2000/svg" '
            f'viewBox="0 0 {32 * width} {height + tick + 14}" '
            f'font-family="Consolas, monospace" font-size="11">'
        )
    ]
    color_of: dict[str, str] = {}
    for hi, lo, kind, label in segments:
        x = (31 - hi) * width
        cell_width = (hi - lo + 1) * width
        if kind == "field":
            css_class = color_of.setdefault(label, f"f{len(color_of) % N_FIELD_COLORS}")
            text_class = ""
            tip = field_tip(label, fields[label])
        elif kind == "rsvd":
            css_class = "rz"
            text_class = "vrz"
            tip = "reserved-zero - canonical encoders emit 0; decoders treat these bits as don't-care"
        else:
            css_class = "fx"
            text_class = "vfx"
            if lo == 0:
                tip = f"opcode {op_key} fixed low bits"
            else:
                tip = "fixed bits - decode-significant form selector"

        parts.append(
            f'<rect x="{x}" y="{tick}" width="{cell_width}" height="{height}" '
            f'class="{css_class}" data-tip="{html_lib.escape(tip, quote=True)}"/>'
        )

        label_text = label if kind != "rsvd" else "0"
        char_width = 0.62
        mode = "h"
        font_size = 11
        for size in (11, 10, 9, 8):
            if len(label_text) * size * char_width <= cell_width - 4:
                font_size = size
                mode = "h"
                break
        else:
            for size in (9, 8, 7):
                if len(label_text) * size * char_width <= height - 4:
                    font_size = size
                    mode = "v"
                    break
            else:
                max_chars = max(2, int((height - 4) / (8 * char_width)) - 1)
                label_text = label_text[:max_chars] + "..."
                font_size = 8
                mode = "v"

        text_attr = f' class="{text_class}"' if text_class else ""
        caption = "opcode" if kind == "fixed" and lo == 0 else ""
        center_x = x + cell_width / 2
        escaped_label = html_lib.escape(label_text)
        if mode == "v":
            center_y = tick + height / 2
            parts.append(
                f'<text x="{center_x}" y="{center_y + font_size * 0.35}" '
                f'text-anchor="middle" transform="rotate(-90 {center_x} {center_y})" '
                f'font-size="{font_size}"{text_attr}>{escaped_label}</text>'
            )
        else:
            text_y = tick + 13 if caption else tick + height / 2 + 4
            parts.append(
                f'<text x="{center_x}" y="{text_y}" text-anchor="middle" '
                f'font-size="{font_size}"{text_attr}>{escaped_label}</text>'
            )
        if caption:
            parts.append(
                f'<text x="{center_x}" y="{tick + height - 6}" text-anchor="middle" '
                f'font-size="8" class="bit">{caption}</text>'
            )
        parts.append(f'<text x="{x + 2}" y="{tick - 2}" font-size="9" class="bit">{hi}</text>')
        if lo != hi:
            parts.append(
                f'<text x="{x + cell_width - 2}" y="{tick - 2}" font-size="9" '
                f'class="bit" text-anchor="end">{lo}</text>'
            )

    parts.append("</svg>")
    parts.append(
        "<div class='small-note'>fixed bits = decode mask/match; tinted cells = "
        "operand and modifier fields; dim 0 = reserved-zero canonical output</div>"
    )
    return "".join(parts)


def semantic_html(text: str) -> str:
    paragraphs = [p.strip() for p in str(text or "").split("\n\n") if p.strip()]
    if not paragraphs:
        return ""
    return "".join(f"<p>{html_lib.escape(p)}</p>" for p in paragraphs)


def build_mnemonic_map(opcodes: dict[str, Any], fields: dict[str, Any]) -> dict[str, str]:
    mapping: dict[str, str] = {}
    for opcode_key, op in opcodes.items():
        for form in op.get("forms", []):
            specs = form.get("mnemonics") or ([form["mnemonic"]] if "mnemonic" in form else [])
            for spec in specs:
                for name, _values, _selections in expand(
                    spec["pattern"], spec.get("binds", []), spec.get("when", {})
                ):
                    previous = mapping.setdefault(name, opcode_key)
                    if previous != opcode_key:
                        raise GenerationError(f"{name} maps to both {previous} and {opcode_key}")
        for alias in op.get("aliases", []):
            names = [f"E_{alias['name']}"]
            form = next(f for f in op["forms"] if f["name"] == alias["form"])
            if "cond" in form.get("modifiers", []):
                names.append(f"E_COND_{alias['name']}")
            for name in names:
                previous = mapping.setdefault(name, opcode_key)
                if previous != opcode_key:
                    raise GenerationError(f"{name} maps to both {previous} and {opcode_key}")
    return mapping


def build_opcode_models(
    arch: dict[str, Any], fields: dict[str, Any], opcodes: dict[str, Any]
) -> list[dict[str, Any]]:
    models: list[dict[str, Any]] = []
    ordered = sorted(opcodes.items(), key=lambda item: item[1]["opcode"]["value"])
    for opcode_key, op in ordered:
        mnemonic_names: list[str] = []
        form_models: list[dict[str, Any]] = []
        for form in op.get("forms", []):
            rows = mnemonic_rows(op, form, fields)
            aliases = alias_rows_for_form(op, form, fields)
            mnemonic_names.extend(row["name"] for row in rows)
            mnemonic_names.extend(row["name"] for row in aliases)
            mask, match = form_mask_match(form)
            notes = notes_list(form.get("notes"))
            notes.insert(0, f"decode mask 0x{mask:08x}, match 0x{match:08x}")
            form_models.append(
                {
                    "name": form["name"],
                    "anchor": f"{opcode_key}-{html_id(form['name'])}",
                    "syntax": form.get("syntax", ""),
                    "svg": bitfield_svg(form, fields, op["opcode"]["name"]),
                    "mnemonics": rows,
                    "aliases": aliases,
                    "notes": notes,
                }
            )

        prose = op.get("semantics", {}).get("prose", "")
        restrictions = notes_list(op.get("semantics", {}).get("restrictions"))
        if restrictions:
            prose = prose.rstrip() + "\n\nRestrictions: " + "; ".join(restrictions)
        mnemonic_count = len(mnemonic_names)
        summary = f"0x{op['opcode']['value']:02X} {op['opcode'].get('family', 'opcode')}"
        search_terms = " ".join(
            [
                opcode_key,
                op["opcode"]["name"],
                op["opcode"].get("family", ""),
                prose,
                " ".join(mnemonic_names),
                " ".join(form.get("syntax", "") for form in op.get("forms", [])),
            ]
        )
        models.append(
            {
                "name": op["opcode"]["name"],
                "anchor": opcode_key,
                "summary": summary,
                "semantic_html": semantic_html(prose),
                "forms": form_models,
                "form_count": len(form_models),
                "mnemonic_count": mnemonic_count,
                "has_public_sources": bool(public_provenance(op.get("provenance"), arch)),
                "has_notes": bool(restrictions),
                "public_provenance": public_provenance(op.get("provenance"), arch),
                "search_text": re.sub(r"\s+", " ", search_terms.lower()).strip(),
                "search_doc": {
                    "id": f"opcode:{opcode_key}",
                    "title": f"{op['opcode']['name']} instruction",
                    "url": f"instructions.html#{opcode_key}",
                    "kind": "instruction",
                    "summary": first_sentence(prose) or summary,
                    "body": strip_markdown(search_terms),
                    "mnemonics": " ".join(mnemonic_names),
                    "tags": op["opcode"].get("family", ""),
                },
            }
        )
    return models


def render_page(
    env: Environment,
    page_title: str,
    active: str,
    body: str,
    nav: list[dict[str, str]],
    style_css: str,
    app_js: str,
) -> str:
    return env.get_template("base.html.j2").render(
        title=page_title,
        active=active,
        body=body,
        nav=nav,
        style_css=style_css,
        app_js=app_js,
    )


def render_chapters(
    env: Environment,
    arch: dict[str, Any],
    mnemonic_to_opcode: dict[str, str],
) -> tuple[list[dict[str, Any]], list[dict[str, Any]]]:
    rendered: list[dict[str, Any]] = []
    search_docs: list[dict[str, Any]] = []
    for path in chapter_paths():
        chapter = parse_chapter(path)
        meta = chapter["meta"]
        href = f"{meta['id']}.html"
        linked = resolve_instruction_links(chapter["body"], mnemonic_to_opcode)
        html_body = markdown_text_to_html(linked)
        model = {
            "id": meta["id"],
            "title": meta["title"],
            "href": href,
            "html": html_body,
            "public_provenance": public_provenance(meta.get("provenance"), arch),
        }
        rendered.append(model)

        plain = strip_markdown(chapter["body"])
        search_docs.append(
            {
                "id": f"chapter:{meta['id']}",
                "title": meta["title"],
                "url": href,
                "kind": "chapter",
                "summary": first_sentence(plain),
                "body": plain,
                "mnemonics": "",
                "tags": meta["id"],
            }
        )
        search_docs.extend(search_sections(chapter, href))
    return rendered, search_docs


def render_search_index(search_docs: list[dict[str, Any]]) -> str:
    payload = {
        "options": {
            "fields": ["title", "body", "mnemonics", "lookup", "tags"],
            "storeFields": ["title", "url", "kind", "summary"],
            "searchOptions": {
                "prefix": True,
                "fuzzy": 0.18,
                "boost": {"title": 3, "mnemonics": 4, "lookup": 5, "tags": 2},
            },
        },
        "aliases": {
            "smartdma": "ezh",
            "ezh": "smartdma",
            "arm": "host",
            "host": "arm",
            "end": "park",
            "park": "end",
        },
        "documents": search_docs,
    }
    return "window.EZH_SEARCH = " + json.dumps(payload, ensure_ascii=True, sort_keys=True) + ";\n"


def symbol_search_docs(arch: dict[str, Any], fields: dict[str, Any]) -> list[dict[str, Any]]:
    docs: list[dict[str, Any]] = []
    for name, meta in sorted(arch.get("registers", {}).items(), key=lambda item: item[1]["value"]):
        desc = meta.get("desc", "")
        docs.append(
            {
                "id": f"register:{name}",
                "title": f"{name} register",
                "url": "architecture.html#registers",
                "kind": "register",
                "summary": desc,
                "body": desc,
                "mnemonics": "",
                "lookup": name,
                "tags": "register architecture",
            }
        )
    for name, meta in sorted(arch.get("conditions", {}).items(), key=lambda item: item[1]["value"]):
        aliases = " ".join(meta.get("alias", []))
        desc = meta.get("desc", "")
        docs.append(
            {
                "id": f"condition:{name}",
                "title": f"{name} condition",
                "url": "architecture.html#flags",
                "kind": "condition",
                "summary": desc,
                "body": f"{desc} {aliases}".strip(),
                "mnemonics": "",
                "lookup": f"{name} {aliases}".strip(),
                "tags": "condition flags",
            }
        )
    for name, meta in sorted(fields.items()):
        desc = meta.get("desc", "")
        kind = meta.get("kind", "field")
        docs.append(
            {
                "id": f"field:{name}",
                "title": f"{name} field",
                "url": "instructions.html",
                "kind": "field",
                "summary": desc,
                "body": desc,
                "mnemonics": "",
                "lookup": name,
                "tags": f"field {kind}",
            }
        )
    return docs


def short_revision(revision: str | None) -> str:
    if not revision:
        return ""
    return revision[:12]


def format_irq(irq: dict[str, Any]) -> dict[str, str]:
    description = irq.get("description", "")
    label = f"{irq['name']} = {irq['number']}"
    return {"label": label, "description": description}


def format_base_address(base: dict[str, Any]) -> dict[str, str]:
    spaces = {
        "default_or_nonsecure": "default/non-secure",
        "secure_or_cmse": "secure/CMSE",
        "nonsecure_alias": "non-secure alias",
    }
    return {
        "label": f"{base['macro']} = {base['address']}",
        "space": spaces.get(base.get("space"), base.get("space", "")),
    }


def load_platform_model() -> dict[str, Any]:
    index_path = PLATFORM_DIR / "index.json"
    if not index_path.exists():
        raise GenerationError(f"missing platform index: {index_path.relative_to(ROOT)}")
    index = json.loads(read_text(index_path))

    parts: list[dict[str, Any]] = []
    core_rows: list[dict[str, Any]] = []
    families: dict[tuple[str, str], dict[str, Any]] = {}
    missing_base_core_views = 0

    for rel_path in index.get("part_files", []):
        part_path = PLATFORM_DIR / rel_path
        part = json.loads(read_text(part_path))
        part_cores: list[dict[str, Any]] = []
        anchor = f"part-{html_id(part['part'])}"
        family_key = (part["series"], part["family"])
        family = families.setdefault(
            family_key,
            {
                "series": part["series"],
                "family": part["family"],
                "parts": 0,
                "core_views": 0,
            },
        )
        family["parts"] += 1

        for core in part.get("cores", []):
            formatted_irqs = [format_irq(item) for item in core.get("irqs", [])]
            formatted_bases = [
                format_base_address(item) for item in core.get("base_addresses", [])
            ]
            if not formatted_bases:
                missing_base_core_views += 1
            core_model = {
                "core": core["core"],
                "features_header": core.get("features_header"),
                "common_header": core.get("common_header"),
                "presence": core.get("presence", {}),
                "irqs": formatted_irqs,
                "base_addresses": formatted_bases,
                "missing_irq": not formatted_irqs,
                "missing_base": not formatted_bases,
            }
            part_cores.append(core_model)
            core_rows.append(
                {
                    "part": part["part"],
                    "anchor": anchor,
                    "series": part["series"],
                    "family": part["family"],
                    **core_model,
                }
            )
            family["core_views"] += 1

        parts.append(
            {
                "part": part["part"],
                "anchor": anchor,
                "series": part["series"],
                "family": part["family"],
                "repo": part.get("repo"),
                "repo_revision": part.get("repo_revision"),
                "repo_revision_short": short_revision(part.get("repo_revision")),
                "repo_path": part.get("repo_path"),
                "track_branch": part.get("track_branch"),
                "status": part.get("status"),
                "cores": part_cores,
                "enrichment": part.get("enrichment", {}),
            }
        )

    series_rows = []
    unconfirmed_candidates: list[dict[str, Any]] = []
    for series, stats in sorted(index.get("series", {}).items()):
        series_rows.append(
            {
                "series": series,
                "feature_headers_scanned": stats.get("feature_headers_scanned", 0),
                "confirmed_parts": stats.get("confirmed_parts", 0),
                "confirmed_core_views": stats.get("confirmed_core_views", 0),
                "broad_ezh_files_scanned": stats.get("broad_ezh_files_scanned", 0),
                "broad_ezh_candidates": stats.get("broad_ezh_candidates", 0),
            }
        )
        for candidate in stats.get("unconfirmed_candidates", []):
            unconfirmed_candidates.append(
                {
                    "series": series,
                    "path": candidate["path"],
                    "reason": candidate.get("reason", ""),
                    "irqs": [format_irq(item) for item in candidate.get("irqs", [])],
                    "base_addresses": [
                        format_base_address(item)
                        for item in candidate.get("base_addresses", [])
                    ],
                }
            )

    summary = dict(index.get("summary", {}))
    summary["missing_base_core_views"] = missing_base_core_views
    return {
        "index": index,
        "summary": summary,
        "manifest_revision": index.get("manifest", {}).get("revision", ""),
        "manifest_revision_short": short_revision(index.get("manifest", {}).get("revision")),
        "series": series_rows,
        "families": sorted(families.values(), key=lambda item: (item["series"], item["family"])),
        "parts": parts,
        "core_rows": core_rows,
        "open_items": index.get("open_items", []),
        "notes": index.get("notes", []),
        "unconfirmed_candidates": unconfirmed_candidates,
    }


def platform_search_docs(platform: dict[str, Any]) -> list[dict[str, Any]]:
    docs = [
        {
            "id": "page:platform",
            "title": "Platform Guide",
            "url": "platform.html",
            "kind": "page",
            "summary": "SDK-discovered SmartDMA/EZH parts and known extraction gaps.",
            "body": (
                "platform smartdma ezh sdk discovery part core base address irq "
                "inputmux pin mux enrichment open gaps"
            ),
            "mnemonics": "",
            "tags": "platform smartdma ezh",
        }
    ]
    for part in platform["parts"]:
        terms: list[str] = [
            part["part"],
            part["series"],
            part["family"],
            part.get("repo_path") or "",
            part.get("track_branch") or "",
            "platform smartdma ezh",
        ]
        for core in part["cores"]:
            terms.append(core["core"])
            terms.append(core.get("features_header") or "")
            terms.append(core.get("common_header") or "")
            terms.append(core.get("presence", {}).get("probe", ""))
            for irq in core["irqs"]:
                terms.append(irq["label"])
                terms.append(irq["description"])
            for base in core["base_addresses"]:
                terms.append(base["label"])
                terms.append(base["space"])
        core_count = len(part["cores"])
        docs.append(
            {
                "id": f"platform:{part['part']}",
                "title": f"{part['part']} platform",
                "url": f"platform.html#{part['anchor']}",
                "kind": "platform",
                "summary": (
                    f"{part['series']} {part['family']}; "
                    f"{core_count} SDK-confirmed core view"
                    f"{'' if core_count == 1 else 's'}."
                ),
                "body": " ".join(item for item in terms if item),
                "mnemonics": "",
                "lookup": f"{part['part']} {part['family']} {part['series']}",
                "tags": "platform smartdma ezh",
            }
        )
    return docs


def prepare_out_dir(out_dir: Path) -> None:
    resolved = out_dir.resolve()
    protected = {
        ROOT.resolve(),
        (ROOT / "docs").resolve(),
        DOCS_SRC.resolve(),
        (ROOT / "isa").resolve(),
        (ROOT / "src").resolve(),
        (ROOT / "include").resolve(),
    }
    if resolved in protected or str(resolved) == resolved.anchor:
        raise GenerationError(f"refusing to clear unsafe output directory: {out_dir}")
    if out_dir.exists() and not out_dir.is_dir():
        raise GenerationError(f"refusing to overwrite non-directory output path: {out_dir}")
    known_generated_root = resolved == DEFAULT_OUT.resolve()
    sentinel = out_dir / SENTINEL
    if out_dir.exists() and any(out_dir.iterdir()) and not known_generated_root and not sentinel.is_file():
        raise GenerationError(
            f"refusing to clear existing non-generated directory: {out_dir} "
            f"(missing {SENTINEL})"
        )
    if out_dir.exists():
        for child in out_dir.iterdir():
            if child.is_dir():
                shutil.rmtree(child)
            else:
                child.unlink()
    else:
        out_dir.mkdir(parents=True)


def copy_vendor(out_dir: Path) -> None:
    source = VENDOR_DIR / "minisearch" / "minisearch-7.2.0.js"
    if not source.exists():
        raise GenerationError(
            "missing vendored MiniSearch asset; expected "
            f"{source.relative_to(ROOT)}"
        )
    shutil.copytree(VENDOR_DIR, out_dir / "vendor")


def generate_site(out_dir: Path) -> dict[str, int]:
    arch, fields, opcodes = load()
    mnemonic_to_opcode = build_mnemonic_map(opcodes, fields)
    opcode_models = build_opcode_models(arch, fields, opcodes)
    platform = load_platform_model()

    env = Environment(
        loader=FileSystemLoader(TEMPLATE_DIR),
        autoescape=select_autoescape(["html", "j2"]),
        keep_trailing_newline=True,
    )
    style_css = read_text(DOCS_SRC / "style.css")
    app_js = read_text(TEMPLATE_DIR / "app.js")

    nav = [
        {"id": "home", "title": "Home", "href": "index.html"},
        {"id": "architecture", "title": "Architecture", "href": "architecture.html"},
        {"id": "instructions", "title": "Instructions", "href": "instructions.html"},
        {"id": "assembler", "title": "Assembler", "href": "assembler.html"},
        {"id": "cookbook", "title": "Cookbook", "href": "cookbook.html"},
        {"id": "platform", "title": "Platform", "href": "platform.html"},
        {"id": "simulator", "title": "Simulator", "href": "simulator.html"},
    ]

    chapters, chapter_search_docs = render_chapters(env, arch, mnemonic_to_opcode)

    prepare_out_dir(out_dir)
    write_text(out_dir / SENTINEL, "Generated by isa/tools/gen_docs.py; safe to replace.\n")
    copy_vendor(out_dir)

    search_docs: list[dict[str, Any]] = []
    search_docs.extend(chapter_search_docs)
    search_docs.extend(op["search_doc"] for op in opcode_models)
    search_docs.extend(symbol_search_docs(arch, fields))
    search_docs.extend(platform_search_docs(platform))
    search_docs.append(
        {
            "id": "page:instructions",
            "title": "Instruction Reference",
            "url": "instructions.html",
            "kind": "page",
            "summary": "Generated opcode, form, bitfield, and mnemonic reference.",
            "body": "instruction reference opcode form bitfield mnemonic encoding base word",
            "mnemonics": "",
            "tags": "instructions",
        }
    )
    search_docs.append(
        {
            "id": "page:simulator",
            "title": "Instruction Simulator",
            "url": "simulator.html",
            "kind": "page",
            "summary": "Opcode simulator placeholder.",
            "body": "simulator instruction encoding decode execute",
            "mnemonics": "",
            "tags": "simulator",
        }
    )

    home_body = env.get_template("home.html.j2").render(
        summary=(
            "A public static reference for EZH, the instruction-set surface of "
            "NXP SmartDMA. Encodings come from the checked ISA database; prose "
            "chapters explain the architecture, assembler, and recurring patterns."
        ),
        opcode_count=len(opcodes),
        mnemonic_count=len(mnemonic_to_opcode),
        chapter_count=len(chapters),
        tiles=[
            {
                "title": "Architecture",
                "href": "architecture.html",
                "description": "Execution model, register file, flags, buses, branches, and supervisor behavior.",
            },
            {
                "title": "Instruction Reference",
                "href": "instructions.html",
                "description": "Expandable opcode panels with generated bitfields, forms, and mnemonic expansions.",
            },
            {
                "title": "Assembler",
                "href": "assembler.html",
                "description": "bunny_build as a two-pass C assembler with labels, directives, and pseudo-instructions.",
            },
            {
                "title": "Cookbook",
                "href": "cookbook.html",
                "description": "Corpus-backed patterns for continuous engines, command/execute/stop programs, and pseudo-instruction idioms.",
            },
            {
                "title": "Platform",
                "href": "platform.html",
                "description": "SDK-discovered SmartDMA/EZH parts, per-core IRQ/base facts, and explicit extraction gaps.",
            },
            {
                "title": "Simulator",
                "href": "simulator.html",
                "description": "Interactive instruction experiments. This page is reserved for the simulator step.",
            },
        ],
    )
    write_text(
        out_dir / "index.html",
        render_page(env, "Home", "home", home_body, nav, style_css, app_js),
    )

    chapter_by_id = {chapter["id"]: chapter for chapter in chapters}
    for chapter in chapters:
        body = env.get_template("prose.html.j2").render(chapter=chapter)
        write_text(
            out_dir / chapter["href"],
            render_page(env, chapter["title"], chapter["id"], body, nav, style_css, app_js),
        )

    instructions_body = env.get_template("instructions.html.j2").render(opcodes=opcode_models)
    write_text(
        out_dir / "instructions.html",
        render_page(env, "Instruction Reference", "instructions", instructions_body, nav, style_css, app_js),
    )

    platform_body = env.get_template("platform.html.j2").render(platform=platform)
    write_text(
        out_dir / "platform.html",
        render_page(env, "Platform Guide", "platform", platform_body, nav, style_css, app_js),
    )

    placeholder_body = env.get_template("placeholder.html.j2").render(
        heading="Instruction Simulator",
        message=(
            "The simulator page is reserved for the later execution-model step. "
            "The current static build provides the checked prose chapters, opcode "
            "reference, and offline search assets."
        ),
    )
    write_text(
        out_dir / "simulator.html",
        render_page(env, "Instruction Simulator", "simulator", placeholder_body, nav, style_css, app_js),
    )

    write_text(out_dir / "search_index.js", render_search_index(search_docs))

    return {
        "opcodes": len(opcodes),
        "mnemonics": len(mnemonic_to_opcode),
        "chapters": len(chapter_by_id),
        "search_docs": len(search_docs),
    }


def run_command(args: list[str]) -> int:
    print("+ " + " ".join(args))
    completed = subprocess.run(args, cwd=ROOT)
    return completed.returncode


def preflight(full: bool) -> int:
    checks: list[list[str]] = []
    if full:
        checks.extend(
            [
                [sys.executable, "isa/tools/validate.py"],
                [sys.executable, "isa/tools/expand_mnemonics.py"],
                [sys.executable, "isa/tools/verify_encodings.py"],
                [sys.executable, "isa/tools/verify_fsl.py"],
            ]
        )
    checks.append(
        [
            sys.executable,
            "isa/tools/lint_chapter.py",
            *(str(path.relative_to(ROOT)) for path in chapter_paths()),
            "--quiet",
        ]
    )
    for check in checks:
        rc = run_command(check)
        if rc:
            return rc
    return 0


def scan_public(out_dir: Path) -> int:
    return run_command([sys.executable, "isa/tools/check_public_docs.py", str(out_dir)])


def file_map(root: Path, suffixes: set[str] | None = None) -> dict[Path, Path]:
    files: dict[Path, Path] = {}
    for path in sorted(root.rglob("*")):
        if path.is_file() and (suffixes is None or path.suffix.lower() in suffixes):
            files[path.relative_to(root)] = path
    return files


def compare_trees(expected: Path, actual: Path) -> list[str]:
    failures: list[str] = []
    if not actual.exists():
        return [f"{actual}: generated docs directory is missing"]
    expected_files = file_map(expected)
    actual_files = file_map(actual)
    for rel in sorted(expected_files.keys() - actual_files.keys()):
        failures.append(f"missing generated file: {rel}")
    for rel in sorted(actual_files.keys() - expected_files.keys()):
        failures.append(f"unexpected generated file: {rel}")
    for rel in sorted(expected_files.keys() & actual_files.keys()):
        if not filecmp.cmp(expected_files[rel], actual_files[rel], shallow=False):
            failures.append(f"stale generated file: {rel}")
    return failures


def check_mode(out_dir: Path) -> int:
    rc = preflight(full=True)
    if rc:
        return rc
    with tempfile.TemporaryDirectory(prefix="ezh-docs-") as temp:
        temp_out = Path(temp) / "html"
        stats = generate_site(temp_out)
        rc = scan_public(temp_out)
        if rc:
            return rc
        diffs = compare_trees(temp_out, out_dir)
        for failure in diffs:
            print(f"FAIL  {failure}")
        if diffs:
            print(f"\n{len(diffs)} generated-doc drift issue(s)")
            return 1
        print(
            "Generated docs are current: "
            f"{stats['opcodes']} opcodes, {stats['mnemonics']} mnemonics, "
            f"{stats['chapters']} chapters, {stats['search_docs']} search docs."
        )
    return 0


def generate_mode(out_dir: Path) -> int:
    rc = preflight(full=False)
    if rc:
        return rc
    stats = generate_site(out_dir)
    rc = scan_public(out_dir)
    if rc:
        return rc
    print(
        f"Generated {out_dir}: {stats['opcodes']} opcodes, "
        f"{stats['mnemonics']} mnemonics, {stats['chapters']} chapters, "
        f"{stats['search_docs']} search docs."
    )
    return 0


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--out", type=Path, default=DEFAULT_OUT, help="output directory")
    parser.add_argument(
        "--check",
        action="store_true",
        help="rebuild in a temporary directory and compare with --out",
    )
    args = parser.parse_args(argv)

    try:
        if args.check:
            return check_mode(args.out)
        return generate_mode(args.out)
    except GenerationError as exc:
        print(f"FAIL  {exc}")
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
