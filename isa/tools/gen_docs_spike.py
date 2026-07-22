"""Doc-generator spike for ADR isa-adr-0002 (accepted).

Usage:  uv run python isa/tools/gen_docs_spike.py OUTDIR [--single FILE]

Proves the pipeline end-to-end with stdlib only: walks the ISA db and emits
one styled HTML page per base opcode plus an index, with bitfield diagrams as
inline SVG derived from the slice data and mnemonic lists from the verified
pattern expansion.  The real generator (build-static-html step) replaces the
f-string templating here with Jinja2 and adds the Markdown prose chapters and
the --check reproducibility mode; page structure and the SVG walk carry over.

Styling (direction from Eli, 2026-07-22): the supply-chain-monkey status page
(src/py/scm/server/templates/status.html in wavenumber-eng/supply-chain-monkey)
copied verbatim where applicable - amber phosphor-glow terminal, monospace,
flat collapsible panels - with the monkey ASCII art replaced by the bunny from
this repo's README.  Tweaks per direction: token-based CSS variables, a light
theme as a manual option (dark is the identity and the default), and a footer
font cycler for trying monospace options.

--single additionally writes everything as one self-contained page (used for
review previews).  Output is deterministic; nothing is written inside the
repo tree unless OUTDIR points there.
"""
from __future__ import annotations

import html
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from expand_mnemonics import expand, expected_base  # noqa: E402
from validate import load, parse_range  # noqa: E402
from verify_encodings import encode, form_mask_match  # noqa: E402

BUNNY_ART = r"""
     / \
    / _ \
   | / \ |
   ||   || _______
   ||   || |\     \
   ||   || ||\     \
   ||   || || \    |
   ||   || ||  \__/
   ||   || ||   ||
    \\_/ \_/ \_//
   /   _     _   \
  /               \
  |    O     O    |
  |   \  ___  /   |
 /     \ \_/ /     \
/  -----  |  --\    \
|     \__/|\__/ \   |
\       |_|_|       /
 \_____       _____/
       \     /
       |     |
"""

# supply-chain-monkey status.html styling, copied verbatim where applicable;
# additions: light-theme token block, --font-mono variable, SVG cell classes.
CSS = """
* { margin: 0; padding: 0; box-sizing: border-box; }

:root {
    --bg-dark: #1a1a1a;
    --bg-panel: #242424;
    --bg-input: #2d2d2d;
    --border: #3d3d3d;
    --amber: #ffb000;
    --amber-dim: #cc8800;
    --amber-glow: rgba(255, 176, 0, 0.3);
    --text: #e0e0e0;
    --text-dim: #808080;
    --green: #00ff00;
    --red: #ff4444;
    --font-mono: 'Consolas', 'Monaco', 'Courier New', monospace;
    --f0: rgba(255, 176, 0, 0.18);
    --f1: rgba(0, 255, 0, 0.10);
    --f2: rgba(0, 200, 255, 0.12);
    --f3: rgba(255, 80, 255, 0.12);
    --f4: rgba(255, 96, 96, 0.14);
    --f5: rgba(150, 150, 255, 0.14);
    --rsvd: rgba(255, 255, 255, 0.03);
}
:root[data-theme="light"] {
    --bg-dark: #f4f1e8;
    --bg-panel: #ece9df;
    --bg-input: #e2ded2;
    --border: #c6c0af;
    --amber: #8a5800;
    --amber-dim: #a87d1a;
    --amber-glow: rgba(138, 88, 0, 0.25);
    --text: #2b2721;
    --text-dim: #7d766a;
    --green: #0a7a0a;
    --red: #c02020;
    --f0: rgba(138, 88, 0, 0.16);
    --f1: rgba(10, 122, 10, 0.12);
    --f2: rgba(0, 110, 140, 0.12);
    --f3: rgba(140, 40, 140, 0.10);
    --f4: rgba(180, 40, 40, 0.10);
    --f5: rgba(60, 60, 180, 0.10);
    --rsvd: rgba(0, 0, 0, 0.04);
}

body {
    font-family: var(--font-mono);
    font-size: 14px;
    background: var(--bg-dark);
    color: var(--text);
    min-height: 100vh;
    line-height: 1.4;
}

.container { max-width: 1100px; margin: 0 auto; padding: 20px; }

.panel { background: var(--bg-panel); border: 1px solid var(--border); margin-bottom: 10px; }

.panel-header {
    background: var(--bg-input);
    padding: 6px 10px;
    border-bottom: 1px solid var(--border);
    color: var(--amber);
    cursor: pointer;
    user-select: none;
    display: flex;
    justify-content: space-between;
    align-items: center;
}
.panel-header::after { content: '[-]'; color: var(--text-dim); }
.panel.collapsed .panel-header { border-bottom: none; }
.panel.collapsed .panel-header::after { content: '[+]'; }
.panel.collapsed .panel-content { display: none; }
.panel-content { padding: 12px; }

.bunny-container {
    padding: 10px;
    color: var(--amber);
    text-shadow: 0 0 10px var(--amber-glow);
    text-align: center;
}
.bunny-art {
    font-family: var(--font-mono);
    font-size: 8px;
    line-height: 1.1;
    display: inline-block;
    text-align: left;
    white-space: pre;
}
.title { color: var(--amber); font-size: 14px; margin-top: 6px; letter-spacing: 2px; }
.subtitle { color: var(--text-dim); font-size: 11px; margin-top: 2px; letter-spacing: 1px; }

.status-row {
    display: flex;
    justify-content: space-between;
    padding: 4px 0;
    border-bottom: 1px solid var(--border);
}
.status-row:last-child { border-bottom: none; }
.status-label { color: var(--text-dim); min-width: 120px; }
.status-value { color: var(--amber); text-align: right; }
.status-value.ok { color: var(--green); }
.status-value.error { color: var(--red); }

.footer { color: var(--text-dim); font-size: 11px; text-align: center; margin-top: 16px; }
.footer button {
    background: none; border: 1px solid var(--border); color: var(--text-dim);
    font-family: var(--font-mono); font-size: 11px; padding: 2px 8px;
    cursor: pointer; margin: 0 3px;
}
.footer button:hover { color: var(--amber); border-color: var(--amber); }

.results-table { width: 100%; border-collapse: collapse; font-size: 12px; }
.results-table th {
    background: var(--bg-input);
    color: var(--amber);
    padding: 4px 8px;
    text-align: left;
    border: 1px solid var(--border);
    font-weight: normal;
    white-space: nowrap;
}
.results-table td {
    padding: 4px 8px;
    border: 1px solid var(--border);
    vertical-align: top;
    font-variant-numeric: tabular-nums;
}
.results-table .enc { color: var(--text); }
.results-table .mn { color: var(--amber); }
.tblwrap { overflow-x: auto; }

.restr { color: var(--amber-dim); padding: 4px 0; }
.restr li { margin-left: 1.4em; }
.prov { color: var(--text-dim); font-size: 11px; }
.prose { padding: 4px 0; }

a { color: var(--amber); text-decoration: none; }
a:hover { color: var(--text); text-decoration: underline; }

svg { display: block; margin: 8px 0; max-width: 100%; }
.legend { margin: -2px 0 8px 0; }
.lg-fx { color: var(--green); }
#ezh-tip { position: fixed; display: none; z-index: 50; max-width: 28rem;
    background: var(--bg-input); border: 1px solid var(--amber);
    color: var(--text); font-family: var(--font-mono); font-size: 12px;
    line-height: 1.35; padding: 8px 10px; pointer-events: none;
    box-shadow: 0 0 12px var(--amber-glow); }
#ezh-tip b { color: var(--amber); }
#ezh-tip .dim { color: var(--text-dim); }
#ezh-tip table { border-collapse: collapse; margin: 5px 0 0 0; font-size: 11px; }
#ezh-tip th, #ezh-tip td { border: 1px solid var(--border); padding: 1px 6px; }
#ezh-tip th { background: var(--bg-panel); color: var(--amber); font-weight: normal; }
svg rect { stroke: var(--border); }
svg rect[data-tip] { cursor: help; }
svg rect[data-tip]:hover { stroke: var(--amber); stroke-width: 1.5; }
svg text { pointer-events: none; }
svg text { fill: var(--text); }
svg text.bit { fill: var(--text-dim); }
svg text.vfx { fill: var(--green); }
svg text.vrz { fill: var(--text-dim); }
.fx { fill: var(--bg-input); } .rz { fill: var(--rsvd); }
.f0 { fill: var(--f0); } .f1 { fill: var(--f1); } .f2 { fill: var(--f2); }
.f3 { fill: var(--f3); } .f4 { fill: var(--f4); } .f5 { fill: var(--f5); }
"""

# Theme toggle (light mode is an option; dark is the default identity), font
# cycler for trying monospace options, and SCM's collapsible panels.
SCRIPT = """
document.querySelectorAll('.panel-header').forEach(h => {
    h.addEventListener('click', () => h.parentElement.classList.toggle('collapsed'));
});
const FONTS = [
    ["consolas", "'Consolas', 'Monaco', 'Courier New', monospace"],
    ["cascadia", "'Cascadia Code', 'Cascadia Mono', Consolas, monospace"],
    ["jetbrains", "'JetBrains Mono', Consolas, monospace"],
    ["ibm plex", "'IBM Plex Mono', Consolas, monospace"],
    ["courier", "'Courier New', Courier, monospace"],
];
const root = document.documentElement;
function applyPrefs() {
    const t = localStorage.getItem('ezh_theme');
    if (t) root.setAttribute('data-theme', t);
    const f = parseInt(localStorage.getItem('ezh_font') || '0', 10);
    root.style.setProperty('--font-mono', FONTS[f % FONTS.length][1]);
    const tb = document.getElementById('theme-btn');
    const fb = document.getElementById('font-btn');
    if (tb) tb.textContent = 'theme: ' + (root.getAttribute('data-theme') || 'dark');
    if (fb) fb.textContent = 'font: ' + FONTS[f % FONTS.length][0];
}
const themeBtn = document.getElementById('theme-btn');
if (themeBtn) themeBtn.addEventListener('click', () => {
    const cur = root.getAttribute('data-theme') || 'dark';
    localStorage.setItem('ezh_theme', cur === 'dark' ? 'light' : 'dark');
    applyPrefs();
});
const fontBtn = document.getElementById('font-btn');
if (fontBtn) fontBtn.addEventListener('click', () => {
    const f = parseInt(localStorage.getItem('ezh_font') || '0', 10);
    localStorage.setItem('ezh_font', String((f + 1) % FONTS.length));
    applyPrefs();
});
applyPrefs();
// Hover tooltips: cells carry data-tip keys into the db-generated EZH_TIPS.
const tipEl = document.createElement('div');
tipEl.id = 'ezh-tip';
document.body.appendChild(tipEl);
document.addEventListener('mousemove', e => {
    const t = e.target.closest ? e.target.closest('[data-tip]') : null;
    if (t && window.EZH_TIPS && EZH_TIPS[t.dataset.tip]) {
        tipEl.innerHTML = EZH_TIPS[t.dataset.tip];
        tipEl.style.display = 'block';
        let x = e.clientX + 14, y = e.clientY + 14;
        const r = tipEl.getBoundingClientRect();
        if (x + r.width > innerWidth - 8) x = innerWidth - r.width - 8;
        if (y + r.height > innerHeight - 8) y = e.clientY - r.height - 10;
        tipEl.style.left = x + 'px'; tipEl.style.top = y + 'px';
    } else {
        tipEl.style.display = 'none';
    }
});
// Deep links: #opcode expands that section (search anchors land here too).
function openHash() {
    const el = location.hash && document.getElementById(location.hash.slice(1));
    if (el && el.classList.contains('collapsed')) el.classList.remove('collapsed');
    if (el) el.scrollIntoView();
}
window.addEventListener('hashchange', openHash);
openHash();
"""

N_FIELD_COLORS = 6


def build_tips(arch: dict, fields: dict, opcodes: dict) -> dict[str, str]:
    """db-generated hover-tooltip HTML, keyed by the cells' data-tip values."""
    tips: dict[str, str] = {}
    e = html.escape

    reg_line = " · ".join(
        f"{e(n)}={r['value']:x}" for n, r in arch["registers"].items()
    )
    cond_rows = "".join(
        "<tr><td>{}</td><td>0x{:x}</td><td>{}</td></tr>".format(
            e("/".join([n, *c.get("alias", [])])), c["value"],
            e(c["desc"].split(":")[0].split(". ")[0]))
        for n, c in arch["conditions"].items()
    )
    cond_table = ("<table><tr><th>cond</th><th>val</th><th>meaning</th></tr>"
                  + cond_rows + "</table>")

    for name, f in fields.items():
        width = sum(
            int(s["instr"].split(":")[0]) - int(s["instr"].split(":")[1]) + 1
            for s in f["slices"]
        )
        bits = ", ".join(
            f"instr[{e(s['instr'])}] &larr; value[{e(s['value'])}]" for s in f["slices"]
        )
        body = (f"<b>{e(name)}</b> <span class='dim'>({e(f.get('kind', '?'))}, "
                f"{width} bit{'s' if width != 1 else ''})</span><br>{e(f['desc'])}"
                f"<br><span class='dim'>{bits}</span>")
        if f.get("kind") == "condition":
            body += cond_table
        elif f.get("kind") == "register":
            body += ("<br><span class='dim'>R0-R7 only (3-bit field)</span>"
                     if width == 3 else f"<br><span class='dim'>{reg_line}</span>")
        if f.get("signed"):
            body += "<br><span class='dim'>signed (two's complement)</span>"
        if f.get("constraint"):
            body += f"<br><span class='dim'>constraint: {e(f['constraint'])}</span>"
        tips[f"f:{name}"] = body

    for name, op in opcodes.items():
        o = op["opcode"]
        tips[f"op:{name}"] = (
            f"<b>opcode {e(o['name'])}</b> = 0b{o['value']:05b} "
            f"(0x{o['value']:02X}) <span class='dim'>&middot; "
            f"{e(o.get('family', '?'))} family</span><br>"
            "<span class='dim'>fixed low bits; part of this form's decode "
            "mask/match</span>")
    tips["fixed"] = ("<b>fixed bits</b><br><span class='dim'>decode-significant: "
                     "included in this form's mask/match (often a form-select)</span>")
    tips["rsvd"] = ("<b>reserved-zero</b><br><span class='dim'>canonical encoders "
                    "emit 0; decoders treat these bits as don't-care</span>")
    return tips


def bitfield_svg(form: dict, fields: dict, op_key: str = "") -> str:
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
        if kind == "fixed":  # merge fixed run, rebuild its binary value
            while lo > 0 and owner[lo - 1][0] == "fixed":
                lo -= 1
            label = "".join(owner[i][1] for i in range(b, lo - 1, -1))
        else:
            while lo > 0 and owner[lo - 1] == (kind, label):
                lo -= 1
        segs.append((b, lo, kind, label))
        b = lo - 1

    W, H, TICK = 26, 34, 12
    parts = [
        f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {32 * W} {H + TICK + 14}" '
        f'font-family="Consolas, monospace" font-size="11">'
    ]
    color_of: dict[str, str] = {}
    for hi, lo, kind, label in segs:
        x, w = (31 - hi) * W, (hi - lo + 1) * W
        if kind == "field":
            cls, tcls = color_of.setdefault(label, f"f{len(color_of) % N_FIELD_COLORS}"), ""
            tip = f"f:{label}"
        elif kind == "rsvd":
            cls, tcls, tip = "rz", "vrz", "rsvd"
        else:
            cls, tcls = "fx", "vfx"
            tip = f"op:{op_key}" if lo == 0 and op_key else "fixed"
        parts.append(
            f'<rect x="{x}" y="{TICK}" width="{w}" height="{H}" class="{cls}" '
            f'data-tip="{tip}"/>'
        )
        text = label if kind != "rsvd" else "0"
        # Fit: horizontal first, rotate vertical for narrow cells with long
        # names, ellipsize as a last resort (the tooltip has the full name).
        CW = 0.62  # monospace glyph width as a fraction of font size
        mode, size = "h", 11
        for s in (11, 10, 9, 8):
            if len(text) * s * CW <= w - 4:
                mode, size = "h", s
                break
        else:
            for s in (9, 8, 7):
                if len(text) * s * CW <= H - 4:
                    mode, size = "v", s
                    break
            else:
                maxc = max(2, int((H - 4) / (8 * CW)) - 1)
                text, mode, size = text[:maxc] + "…", "v", 8
        tattr = f' class="{tcls}"' if tcls else ""
        caption = "opcode" if kind == "fixed" and lo == 0 else ""
        cx = x + w / 2
        if mode == "v":
            cy = TICK + H / 2
            parts.append(
                f'<text x="{cx}" y="{cy + size * 0.35}" text-anchor="middle" '
                f'transform="rotate(-90 {cx} {cy})" '
                f'font-size="{size}"{tattr}>{html.escape(text)}</text>'
            )
        else:
            ty = TICK + 13 if caption else TICK + H / 2 + 4
            parts.append(
                f'<text x="{cx}" y="{ty}" text-anchor="middle" '
                f'font-size="{size}"{tattr}>{html.escape(text)}</text>'
            )
        if caption:
            parts.append(
                f'<text x="{x + w / 2}" y="{TICK + H - 6}" text-anchor="middle" '
                f'font-size="8" class="bit">{caption}</text>'
            )
        parts.append(f'<text x="{x + 2}" y="{TICK - 2}" font-size="9" class="bit">{hi}</text>')
        if lo != hi:
            parts.append(
                f'<text x="{x + w - 2}" y="{TICK - 2}" font-size="9" class="bit" '
                f'text-anchor="end">{lo}</text>'
            )
    parts.append("</svg>")
    parts.append(
        "<div class='prov legend'>"
        "<span class='lg-fx'>green</span> = fixed bits (decode mask/match) · "
        "tinted = operand/modifier fields · "
        "dim 0 = reserved (canonical 0, decode don't-care)</div>"
    )
    return "".join(parts)


def mnemonic_rows(op: dict, form: dict, fields: dict) -> list[tuple[str, int]]:
    rows: list[tuple[str, int]] = []
    specs = form.get("mnemonics") or ([form["mnemonic"]] if "mnemonic" in form else [])
    for spec in specs:
        for name, values in expand(spec["pattern"], spec.get("binds", []), spec.get("when", {})):
            rows.append((name, expected_base(form, fields, values)))
    return sorted(rows)


def alias_rows(op: dict, fields: dict) -> list[tuple[str, int, str]]:
    """Alias mnemonics: form match word + baked presets (same math the
    1502/1502 expansion check uses)."""
    rows: list[tuple[str, int, str]] = []
    for alias in op.get("aliases", []):
        form = next(f for f in op["forms"] if f["name"] == alias["form"])
        _, match = form_mask_match(form)
        word = match
        for key, val in alias.get("preset", {}).items():
            word |= encode(fields[key], val)
        preset = ", ".join(f"{k}={v:#x}" if isinstance(v, int) and v >= 0 else f"{k}={v}"
                           for k, v in alias.get("preset", {}).items())
        note = f"{alias['form']} form with {preset}"
        rows.append((f"E_{alias['name']}", word, note))
        if "cond" in form.get("modifiers", []):
            rows.append((f"E_COND_{alias['name']}", word, note + " (+ cond argument)"))
    return sorted(rows)


def panel(header: str, content: str, collapsed: bool = False, anchor: str = "") -> str:
    cls = "panel collapsed" if collapsed else "panel"
    aid = f' id="{anchor}"' if anchor else ""
    return (
        f'<div class="{cls}"{aid}><div class="panel-header">{html.escape(header)}</div>'
        f'<div class="panel-content">{content}</div></div>'
    )


def bunny_header(subtitle: str) -> str:
    return (
        '<div class="panel"><div class="bunny-container">'
        f'<pre class="bunny-art">{html.escape(BUNNY_ART)}</pre>'
        '<div class="title">BUNNY_BUILD // EZH ARCHITECTURE B</div>'
        f'<div class="subtitle">{html.escape(subtitle)}</div>'
        "</div></div>"
    )


def render_opcode(name: str, op: dict, fields: dict, arch: dict) -> str:
    o = op["opcode"]
    out = []
    sem = op.get("semantics", {})
    body = ""
    if sem.get("prose"):
        body += f"<div class='prose'>{html.escape(sem['prose'].strip())}</div>"
    t = op.get("timing", {})
    if t:
        note = f" — {html.escape(t['notes'])}" if t.get("notes") else ""
        body += (
            "<div class='status-row'><span class='status-label'>timing</span>"
            f"<span class='status-value'>{html.escape(str(t.get('cycles', '?')))}"
            f" cycle(s)</span></div><div class='prov'>{note[3:] if note else ''}</div>"
        )
    if sem.get("restrictions"):
        items = "".join(f"<li>{html.escape(r)}</li>" for r in sem["restrictions"])
        body += f"<div class='restr'>restrictions:<ul>{items}</ul></div>"
    out.append(panel(f"{o['name']} — OPCODE 0x{o['value']:02X}", body))

    for form in op.get("forms", []):
        mask, match = form_mask_match(form)
        fbody = (
            f"<div class='prose'><code>{html.escape(form.get('syntax', ''))}</code></div>"
            f"<div class='prov'>decode mask 0x{mask:08x} · match 0x{match:08x}</div>"
        )
        fbody += bitfield_svg(form, fields, op_key=name)
        if form.get("notes"):
            fbody += f"<div class='prov'>{html.escape(form['notes'])}</div>"
        out.append(panel(f"FORM: {form['name'].upper()}", fbody))

        rows = mnemonic_rows(op, form, fields)
        if rows:
            tr = "".join(
                f"<tr><td class='mn'>{html.escape(n)}</td>"
                f"<td class='enc'>0x{b:08x}</td></tr>"
                for n, b in rows
            )
            table = (
                "<div class='tblwrap'><table class='results-table'>"
                f"<tr><th>mnemonic</th><th>base word</th></tr>{tr}</table></div>"
            )
            out.append(panel(f"MNEMONICS: {form['name'].upper()} ({len(rows)})", table,
                             collapsed=True))

    arows = alias_rows(op, fields)
    if arows:
        tr = "".join(
            f"<tr><td class='mn'>{html.escape(n)}</td><td class='enc'>0x{b:08x}</td>"
            f"<td class='prov'>{html.escape(note)}</td></tr>"
            for n, b, note in arows
        )
        table = (
            "<div class='tblwrap'><table class='results-table'>"
            f"<tr><th>alias</th><th>base word</th><th>expansion</th></tr>{tr}</table></div>"
        )
        out.append(panel(f"ALIASES ({len(arows)})", table))

    pub = {s for s, meta in arch["sources"].items() if meta.get("public")}
    cites = [p for p in op.get("provenance", []) if p["source"] in pub]
    if cites:
        items = "".join(
            "<div class='status-row'>"
            f"<span class='status-label'>{html.escape(arch['sources'][p['source']]['title'])}"
            f"</span><span class='prov'>{html.escape(p['detail'])}</span></div>"
            for p in cites
        )
        out.append(panel("PUBLIC SOURCES", items))
    return "\n".join(out)


FOOTER = (
    '<div class="footer">generated from the machine-readable ISA database · '
    'bunny_build · <button id="theme-btn">theme: dark</button>'
    '<button id="font-btn">font: consolas</button></div>'
)


def page(title: str, body: str, tips_json: str = "{}") -> str:
    return (
        "<!DOCTYPE html>\n<html>\n<head>\n"
        '<meta charset="UTF-8">\n'
        '<meta name="viewport" content="width=device-width, initial-scale=1.0">\n'
        f"<title>{html.escape(title)}</title>\n<style>{CSS}</style>\n</head>\n<body>"
        f'<div class="container">{body}{FOOTER}</div>'
        f"<script>window.EZH_TIPS = {tips_json};</script>"
        f"<script>{SCRIPT}</script></body>\n</html>\n"
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
    tips_json = json.dumps(build_tips(arch, fields, opcodes), sort_keys=True)

    # Single expandable reference: every opcode is a collapsed panel on the
    # index itself (per direction: expandable details, not links to pages).
    sections = []
    total_mnem = 0
    for name, op in ordered:
        n_mnem = sum(len(mnemonic_rows(op, f, fields)) for f in op.get("forms", []))
        n_mnem += len(alias_rows(op, fields))
        total_mnem += n_mnem
        header = (f"{op['opcode']['name']} — 0x{op['opcode']['value']:02X} · "
                  f"{n_mnem} mnemonics")
        sections.append(panel(header, render_opcode(name, op, fields, arch),
                              collapsed=True, anchor=name))
    index_body = (
        bunny_header("instruction set reference")
        + "<div class='prose'>Click an instruction to expand its reference. "
        "All encodings, mnemonic expansions, and timing are generated from "
        "the machine-readable ISA database.</div>"
        + "\n".join(sections)
    )
    (outdir / "index.html").write_text(
        page("EZH instruction set", index_body, tips_json), encoding="utf-8")
    print(f"expandable index ({len(ordered)} opcode sections) -> {outdir}")
    print(f"{total_mnem} mnemonics rendered (expand_mnemonics.py guarantees 1502 vs fsl)")

    if single:
        single.write_text(
            page("EZH instruction set (preview)", index_body, tips_json),
            encoding="utf-8",
        )
        print(f"single-page preview -> {single}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
