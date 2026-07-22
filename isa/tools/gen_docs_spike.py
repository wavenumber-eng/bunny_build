"""Doc-generator spike for ADR isa-adr-0002 (proposed).

Usage:  uv run python isa/tools/gen_docs_spike.py OUTDIR [--single FILE]

Proves the pipeline end-to-end with stdlib only: walks the ISA db and emits
one styled HTML page per base opcode plus an index, with bitfield diagrams as
inline SVG derived from the slice data and mnemonic lists from the verified
pattern expansion.  The real generator (build-static-html step) replaces the
f-string templating here with Jinja2 and adds the Markdown prose chapters and
the --check reproducibility mode; page structure and the SVG walk carry over.

--single additionally writes everything as one self-contained page (used for
review previews).  Output is deterministic; nothing is written inside the
repo tree unless OUTDIR points there.
"""
from __future__ import annotations

import html
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from expand_mnemonics import expand, expected_base  # noqa: E402
from validate import load, parse_range  # noqa: E402
from verify_encodings import form_mask_match  # noqa: E402

CSS = """
:root {
  --bg: #ffffff; --ink: #1c1e21; --muted: #5c6670; --accent: #26547c;
  --line: #c9cfd6; --surface: #eef2f7; --warn-bg: #fff6e5; --warn-edge: #e8a13d;
  --f0: #cfe3f5; --f1: #d9f0d4; --f2: #f5e3cf; --f3: #e8d4f0; --f4: #f0d4d8;
  --f5: #d4f0ec; --rsvd: #f3f3f3; --cell-ink: #1c1e21;
}
@media (prefers-color-scheme: dark) { :root {
  --bg: #14171a; --ink: #dfe3e8; --muted: #98a2ad; --accent: #7fb0d8;
  --line: #3a434c; --surface: #1e242b; --warn-bg: #2b2314; --warn-edge: #b98a2e;
  --f0: #24405c; --f1: #2b4a28; --f2: #55402a; --f3: #43305c; --f4: #542e35;
  --f5: #1e4a44; --rsvd: #20252b; --cell-ink: #dfe3e8;
} }
:root[data-theme="light"] {
  --bg: #ffffff; --ink: #1c1e21; --muted: #5c6670; --accent: #26547c;
  --line: #c9cfd6; --surface: #eef2f7; --warn-bg: #fff6e5; --warn-edge: #e8a13d;
  --f0: #cfe3f5; --f1: #d9f0d4; --f2: #f5e3cf; --f3: #e8d4f0; --f4: #f0d4d8;
  --f5: #d4f0ec; --rsvd: #f3f3f3; --cell-ink: #1c1e21;
}
:root[data-theme="dark"] {
  --bg: #14171a; --ink: #dfe3e8; --muted: #98a2ad; --accent: #7fb0d8;
  --line: #3a434c; --surface: #1e242b; --warn-bg: #2b2314; --warn-edge: #b98a2e;
  --f0: #24405c; --f1: #2b4a28; --f2: #55402a; --f3: #43305c; --f4: #542e35;
  --f5: #1e4a44; --rsvd: #20252b; --cell-ink: #dfe3e8;
}
body { font-family: system-ui, sans-serif; margin: 2rem auto; max-width: 60rem;
       line-height: 1.5; color: var(--ink); background: var(--bg); padding: 0 1rem; }
h1 { border-bottom: 2px solid var(--accent); padding-bottom: .3rem; }
h2 { color: var(--accent); margin-top: 2rem; }
code, td.enc { font-family: ui-monospace, Consolas, monospace; }
td.enc, .idx td { font-variant-numeric: tabular-nums; }
.tblwrap { overflow-x: auto; }
table { border-collapse: collapse; margin: .8rem 0; }
th, td { border: 1px solid var(--line); padding: .25rem .6rem; text-align: left; }
th { background: var(--surface); }
.restr { background: var(--warn-bg); border-left: 4px solid var(--warn-edge);
         padding: .5rem .8rem; }
.prov { color: var(--muted); font-size: .85rem; }
svg { display: block; margin: .8rem 0; max-width: 100%; }
svg rect { stroke: var(--line); }
svg text { fill: var(--cell-ink); }
svg text.bit { fill: var(--muted); }
.fx { fill: var(--bg); } .rz { fill: var(--rsvd); }
.f0 { fill: var(--f0); } .f1 { fill: var(--f1); } .f2 { fill: var(--f2); }
.f3 { fill: var(--f3); } .f4 { fill: var(--f4); } .f5 { fill: var(--f5); }
a { color: var(--accent); }
.idx td { padding: .15rem .6rem; }
"""

N_FIELD_COLORS = 6


def bitfield_svg(form: dict, fields: dict) -> str:
    """One 32-bit row; contiguous same-owner runs merged into labeled cells."""
    owner: list[tuple[str, str]] = [("rsvd", "0")] * 32  # bit -> (kind, label)
    for fx in form.get("fixed", []):
        msb, lsb = parse_range(fx["bits"])
        for b in range(lsb, msb + 1):
            owner[b] = ("fixed", str((fx["value"] >> (b - lsb)) & 1))
    for kind in ("operands", "modifiers"):
        for name in form.get(kind, []):
            for s in fields[name]["slices"]:
                imsb, ilsb = parse_range(s["instr"])
                for b in range(ilsb, imsb + 1):
                    owner[b] = ("field", name)

    segs = []  # (hi, lo, kind, label)
    b = 31
    while b >= 0:
        kind, label = owner[b]
        lo = b
        while lo > 0 and owner[lo - 1] == (kind, label) and not (kind == "fixed"):
            lo -= 1
        if kind == "fixed":  # merge fixed run, rebuild its binary value
            lo = b
            while lo > 0 and owner[lo - 1][0] == "fixed":
                lo -= 1
            label = "".join(owner[i][1] for i in range(b, lo - 1, -1))
        segs.append((b, lo, kind, label))
        b = lo - 1

    W, H, TICK = 26, 34, 12
    parts = [
        f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {32 * W} {H + TICK + 14}" '
        f'font-family="ui-monospace, Consolas, monospace" font-size="11">'
    ]
    color_of: dict[str, str] = {}
    for hi, lo, kind, label in segs:
        x, w = (31 - hi) * W, (hi - lo + 1) * W
        if kind == "field":
            cls = color_of.setdefault(label, f"f{len(color_of) % N_FIELD_COLORS}")
        else:
            cls = "rz" if kind == "rsvd" else "fx"
        parts.append(f'<rect x="{x}" y="{TICK}" width="{w}" height="{H}" class="{cls}"/>')
        text = label if kind != "rsvd" else "0"
        size = 11 if len(text) * 7 <= w else max(7, int(w / len(text) * 1.6))
        parts.append(
            f'<text x="{x + w / 2}" y="{TICK + H / 2 + 4}" text-anchor="middle" '
            f'font-size="{size}">{html.escape(text)}</text>'
        )
        parts.append(f'<text x="{x + 2}" y="{TICK - 2}" font-size="9" class="bit">{hi}</text>')
        if lo != hi:
            parts.append(
                f'<text x="{x + w - 2}" y="{TICK - 2}" font-size="9" class="bit" '
                f'text-anchor="end">{lo}</text>'
            )
    parts.append("</svg>")
    return "".join(parts)


def mnemonic_rows(op: dict, form: dict, fields: dict) -> list[tuple[str, int]]:
    rows: list[tuple[str, int]] = []
    specs = form.get("mnemonics") or ([form["mnemonic"]] if "mnemonic" in form else [])
    for spec in specs:
        for name, values in expand(spec["pattern"], spec.get("binds", []), spec.get("when", {})):
            rows.append((name, expected_base(form, fields, values)))
    return sorted(rows)


def render_opcode(name: str, op: dict, fields: dict, arch: dict, standalone: bool) -> str:
    o = op["opcode"]
    out = []
    if standalone:
        out.append(f"<h1>{html.escape(o['name'])} — opcode 0x{o['value']:02x}</h1>")
    else:
        out.append(f"<h2 id='{name}'>{html.escape(o['name'])} — opcode 0x{o['value']:02x}</h2>")
    sem = op.get("semantics", {})
    if sem.get("prose"):
        out.append(f"<p>{html.escape(sem['prose'].strip())}</p>")
    if sem.get("restrictions"):
        items = "".join(f"<li>{html.escape(r)}</li>" for r in sem["restrictions"])
        out.append(f"<div class='restr'><strong>Restrictions</strong><ul>{items}</ul></div>")
    t = op.get("timing", {})
    if t:
        cyc = html.escape(str(t.get("cycles", "?")))
        note = f" — {html.escape(t['notes'])}" if t.get("notes") else ""
        out.append(f"<p><strong>Timing:</strong> {cyc} cycle(s){note}</p>")
    for form in op.get("forms", []):
        mask, match = form_mask_match(form)
        out.append(f"<h3>form <code>{html.escape(form['name'])}</code></h3>")
        out.append(f"<p><code>{html.escape(form.get('syntax', ''))}</code><br>"
                   f"<span class='prov'>decode mask 0x{mask:08x}, match 0x{match:08x}</span></p>")
        out.append(bitfield_svg(form, fields))
        if form.get("notes"):
            out.append(f"<p class='prov'>{html.escape(form['notes'])}</p>")
        rows = mnemonic_rows(op, form, fields)
        if rows:
            tr = "".join(
                f"<tr><td><code>{html.escape(n)}</code></td>"
                f"<td class='enc'>0x{b:08x}</td></tr>"
                for n, b in rows
            )
            out.append(
                "<details><summary>"
                f"{len(rows)} mnemonic(s), canonical base words</summary>"
                "<div class='tblwrap'><table><tr><th>mnemonic</th><th>base word</th>"
                f"</tr>{tr}</table></div></details>"
            )
    pub = {s for s, meta in arch["sources"].items() if meta.get("public")}
    cites = [p for p in op.get("provenance", []) if p["source"] in pub]
    if cites:
        items = "".join(
            f"<li>{html.escape(arch['sources'][p['source']]['title'])}: "
            f"{html.escape(p['detail'])}</li>"
            for p in cites
        )
        out.append(f"<p class='prov'>Public sources:</p><ul class='prov'>{items}</ul>")
    return "\n".join(out)


def page(title: str, body: str) -> str:
    return (
        "<!doctype html><html><head><meta charset='utf-8'>"
        f"<title>{html.escape(title)}</title><style>{CSS}</style></head>"
        f"<body>{body}</body></html>"
    )


def main() -> int:
    args = sys.argv[1:]
    if not args:
        print(__doc__)
        return 2
    outdir = Path(args[0])
    single = Path(args[args.index("--single") + 1]) if "--single" in args else None
    outdir.mkdir(parents=True, exist_ok=True)

    arch, fields, opcodes = load()
    ordered = sorted(opcodes.items(), key=lambda kv: kv[1]["opcode"]["value"])

    idx_rows = []
    for name, op in ordered:
        body = render_opcode(name, op, fields, arch, standalone=True)
        (outdir / f"{name}.html").write_text(
            page(f"EZH {op['opcode']['name']}", body + "<p><a href='index.html'>index</a></p>"),
            encoding="utf-8",
        )
        n_mnem = sum(len(mnemonic_rows(op, f, fields)) for f in op.get("forms", []))
        idx_rows.append(
            f"<tr><td><a href='{name}.html'><code>{html.escape(op['opcode']['name'])}"
            f"</code></a></td><td class='enc'>0x{op['opcode']['value']:02x}</td>"
            f"<td>{n_mnem}</td></tr>"
        )
    index_body = (
        "<h1>EZH Architecture B — instruction set</h1>"
        "<p>Generated from the machine-readable ISA database "
        "(spike preview, ADR isa-adr-0002 proposed).</p>"
        "<table class='idx'><tr><th>opcode</th><th>value</th><th>mnemonics</th></tr>"
        + "".join(idx_rows)
        + "</table>"
    )
    (outdir / "index.html").write_text(page("EZH instruction set", index_body), encoding="utf-8")
    print(f"{len(ordered)} opcode pages + index -> {outdir}")

    if single:
        parts = [index_body.replace(".html'", "'").replace("<a href='", "<a href='#")]
        for name, op in ordered:
            parts.append(render_opcode(name, op, fields, arch, standalone=False))
        single.write_text(page("EZH instruction set (single-page preview)",
                               "\n".join(parts)), encoding="utf-8")
        print(f"single-page preview -> {single}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
