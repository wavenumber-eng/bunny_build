+++
type = "adr"
id = "isa-adr-0002"
domain = "isa"
status = "accepted"
title = "Custom static HTML doc generator driven by the ISA database"
created = "2026-07-22"
+++

## Context

The `build-static-html` step needs a documentation toolchain that consumes the
ISA database (`isa/`, ADR isa-adr-0001) and produces the shipped doc set. The
plan's exit criterion: a static HTML doc set that generates **reproducibly**
from the ISA db and lives in the bunny_build repo.

Facts driving the choice:

- The instruction reference is ~100% generated content: encodings,
  bitfield layouts, modifier matrices, mnemonic expansions, timing, and
  restrictions all come from the db, which is mechanically verified against
  the fsl header and the bunny_build encoders. Hand-maintained instruction
  pages are precisely the drift the isa-adr-0001 pipeline exists to kill.
- The prose steps (`architecture-overview`, `pattern-library`) produce
  narrative documents that must ship in the same site and cross-link into the
  generated reference.
- Provenance discipline: NXP-confidential sources inform but are never
  copied; rendered citations must come from public sources (AN14650). The db
  already records per-section provenance ids; the renderer must filter them
  structurally so non-public ids, titles, and audit notes never reach the
  shipped HTML.
- Ecosystem: Python 3.12 + uv, TOML, stdlib-lean tools, and a house style of
  mechanical verification (validate / verify_encodings / verify_fsl /
  expand_mnemonics are all CI-able checkers).
- The parked `ezh-browser-simulator` plan wants a C-to-WASM simulator page
  embedded in the docs eventually; the toolchain must not fight a plain
  HTML + JS + WASM page.
- Output must be self-contained (offline-usable, no CDN fonts/scripts) since
  it ships inside a vendorable repo.

## Decision

A **custom Python generator in the bunny_build repo** (`isa/tools/
gen_docs.py`), rendering the ISA db
plus Markdown prose to self-contained static HTML in `docs/html/`:

- **Templates: Jinja2.** The only real templating dependency; pure Python,
  uv-managed, universally understood.
- **Prose: Markdown files** (architecture overview, assembler guide, cookbook)
  rendered with `python-markdown` and wrapped in the same layout as generated pages.
  Prose pages may cross-link opcode pages by name (`[[E_MOV]]`-style link
  resolution against the db's expanded mnemonic set).
- **Bitfield diagrams: inline SVG generated from the slice data.** The slice
  model was designed for this (isa-adr-0001); the same walk that emits C
  shift/mask expressions and Verilog part-selects emits `<rect>`/`<text>`
  rows. No image assets, no diagram tool dependency.
- **Structure:** one generated instruction-reference page
  (`instructions.html`) with one expandable panel per base opcode (forms,
  encodings, modifier matrix, expanded mnemonic list, timing, restrictions,
  provenance), a home page, and the prose chapters. Deep links target opcode
  panels (for example `instructions.html#mov`). One shared hand-written CSS
  file is inlined at build time.
- **Reproducibility contract:** the generator is deterministic (stable
  ordering, no timestamps in output). `gen_docs.py --check` regenerates and
  diffs against the committed `docs/html/` tree — doc drift becomes a CI
  failure exactly like encoding drift. Generated output is committed only
  together with this check.
- **Provenance rendering:** rendered citations are built only from sources
  whose `public = true` in `arch.toml`. Non-public source ids may remain in
  structured metadata for creator review, but their ids, titles, and private
  audit notes are not renderable data. A public-output scan is part of the
  generator check path.

## Alternatives considered

- **MkDocs (+ Material).** Best-in-class nav/search for free, but the
  reference pages are fully generated — we would write the same db-walking
  generator and then feed its output through a second generator via plugin
  glue (`mkdocs-gen-files`, macros). Material's default assets pull fonts
  from CDNs unless configured otherwise, and the dependency tree is large
  for a repo whose only other Python dep is the dev standard. Adoptable
  later: the generator's data layer stays, templates would target Markdown
  instead of HTML.
- **Sphinx.** The natural home for Python API docs; for TOML-driven
  reference content it means writing a custom domain/extension — strictly
  more machinery than emitting HTML directly — and bunny_build's public API
  is C, not Python.
- **Doxygen.** Right tool for the C API surface of bunny_build someday;
  wrong shape for ISA reference pages driven by a TOML db.
- **Hand-written HTML/Markdown pages.** Violates single-source-of-truth;
  rejected on principle established in isa-adr-0001.

## Consequences

- Two pure-Python dependencies enter the dev group (`jinja2`, `markdown`);
  the search library is a vendored browser asset with its license committed.
- The doc generator becomes ISA-db consumer #1 (the ordering in isa-adr-0001),
  and its `--check` mode joins the verifier suite in CI.
- Search is implemented in `build-static-html`, after the pages and anchors
  are stable. It remains fully static: the generator emits deterministic
  `search_index.js` data, and the site loads vendored MiniSearch from the
  committed output tree. No CDN, backend, or `fetch()` requirement is allowed,
  so the docs still work from `file://`.
- The simulator page embeds later as one more static page plus a WASM asset —
  no toolchain interaction.
- The old spike (`isa/tools/gen_docs_spike.py`, stdlib-only) is retained only
  as an archived proof of the bitfield/rendering path.
