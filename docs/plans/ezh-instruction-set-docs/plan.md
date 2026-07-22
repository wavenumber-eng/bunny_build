+++
type = "plan"
id = "ezh-instruction-set-docs"
status = "active"
created = "2026-07-21"

[[steps]]
id = "inventory-sources"
title = "Inventory and triage all EZH source material"
status = "done"

[[steps]]
id = "isa-schema"
title = "Design the machine-readable ISA description format (ADR) — single source of truth for docs, codegen, simulator"
status = "done"
depends_on = ["inventory-sources"]

[[steps]]
id = "populate-isa-db"
title = "Populate the ISA database: base opcodes, bitfields, modifier grammar, semantics, restrictions, timing"
status = "done"
depends_on = ["isa-schema"]

[[steps]]
id = "verify-encodings"
title = "Mechanically verify: parse fsl header + bunny_build encoders, three-way diff against ISA db; camera blob as integration anchor"
status = "done"
depends_on = ["populate-isa-db"]

[[steps]]
id = "instruction-prose"
title = "Meticulous per-instruction prose pass: extract AN14650 §5 and Arch B spec descriptions (use, modes, intent) for every instruction; synthesize accurate semantics prose into the ISA db; Eli reviews, then re-inspects rendered HTML"
status = "done"
depends_on = ["populate-isa-db"]

[[steps]]
id = "architecture-overview"
title = "Write architecture overview from spec §4 + AN14650 §2-4: buses, pipeline, registers, flags, boolean detection, heartbeat, supervisor"
status = "active"
depends_on = ["inventory-sources"]

[[steps]]
id = "pattern-library"
title = "Document programming patterns: run-and-stop, multi-app dispatch, pseudo-instructions, continuous DMA/IRQ capture"
status = "pending"
depends_on = ["inventory-sources"]

[[steps]]
id = "choose-doc-toolchain"
title = "Decide doc generator consuming the ISA db; static HTML output (ADR)"
status = "done"
depends_on = ["isa-schema"]

[[steps]]
id = "build-static-html"
title = "Produce the generated static HTML doc set kept in bunny_build"
status = "pending"
depends_on = ["verify-encodings", "instruction-prose", "architecture-overview", "pattern-library", "choose-doc-toolchain"]

[[steps]]
id = "design-doc-intent-audit"
title = "Audit design docs, ADRs, and requirements against implementation"
status = "pending"
depends_on = ["build-static-html"]

[[steps]]
id = "test-runtime-impact-audit"
title = "Audit new test runtime impact"
status = "pending"
depends_on = ["build-static-html"]

[[steps]]
id = "external-review"
title = "Obtain independent external review (EZH creator review of instruction semantics)"
status = "pending"
depends_on = ["build-static-html", "design-doc-intent-audit", "test-runtime-impact-audit"]

[[exit_criteria]]
id = "signoff"
title = "Focused signoff passes"
status = "pending"

[[exit_criteria]]
id = "isa-db-authoritative"
title = "Machine-readable ISA db exists and mechanically round-trips against the original fsl header and bunny_build encoders"
status = "met"

[[exit_criteria]]
id = "instruction-set-complete"
title = "Every Arch B base opcode and modifier documented with operands, behavior, restrictions, and bit-level encoding"
status = "met"

[[exit_criteria]]
id = "static-html-published"
title = "Static HTML doc set generates reproducibly from the ISA db and lives in the bunny_build repo"
status = "pending"

[[exit_criteria]]
id = "design-doc-intent-audit"
title = "Design docs, ADRs, and requirements match implementation"
status = "pending"

[[exit_criteria]]
id = "test-runtime-impact-audit"
title = "New tests are listed and runtime impact is reviewed"
status = "pending"

[[exit_criteria]]
id = "external-review"
title = "Independent external review is complete"
status = "pending"
+++

# New EZH Arch B Documentation

## Goal

Produce a new, coherent documentation set for the NXP EZH (SmartDMA) Architecture B
IO coprocessor — with the blessing of the original EZH creator — synthesized from
public NXP documents and the original architecture document. The end deliverable is a
static HTML doc set that ships with bunny_build, **generated from a machine-readable
ISA description** that also serves future code generation, simulation, and debugging.

## The keystone: machine-readable ISA description (`isa-schema` + `populate-isa-db`)

Everything downstream hangs off a structured ISA database (format TBD in the ADR —
likely TOML or JSON, kept in bunny_build). It must capture, per base opcode:

- 5-bit opcode value and bit-level field layout (positions, widths, meanings)
- the modifier grammar: COND, S (set flags), N (invert), IMM, barrel-shifter fusion
  (LSL/LSR/ASR/ROR pre/post, F/FEND/FBIT flips, R register-shift variants) — the
  ~1500 mnemonics are ~25 base opcodes x this matrix, and the db models the matrix,
  not the flat expansion
- operand types and constraints (register classes, imm widths, shift ranges)
- semantics prose + restrictions (from spec §5 / AN14650 §5)
- timing (single cycle vs multi, from AN14650 instruction table)

Consumers, in order of realization: (1) doc generator, (2) encoding verification
harness, (3) assembler generation/validation for bunny_build, (4) simulator decoder,
(5) debugger/disassembler.

## Verification (`verify-encodings`)

Authority ranking, per the EZH creator:

1. **`fsl_ezh_armclang.h`** — hand-created by the EZH creator; best available reference.
2. **bunny_build encoders** — independently validated by the camera byte-for-byte test.
3. **`ezh_tb_package.sv`** — was an *experiment*; advisory only, never authoritative.

Because the header was hand-written, it can contain bugs (one already found:
`E_COND_VECTORED_HOLD_NRA` defined with a space before its parameter list — broken
object-like macro). The verification step mechanically parses both the header macros
and the bunny_build inline functions into encoding expressions, three-way diffs them
against the ISA db, and produces a discrepancy list for the creator to adjudicate.
The MCX camera blob byte-for-byte test remains the integration anchor. Hardware
spot-checks on MCXN947/LPC55S69 where feasible.

## Source material (inventoried 2026-07-21, see plan logs)

Primary: `C:\eli\ezh\doc_project\` — Arch B spec PreRel0.6 (+"cleaned" variant,
content-identical minus front matter), `fsl_ezh_armclang.h`, `ezh_tb_package.sv`,
two training decks, **AN14650 = public SmartDMA Cookbook Rev 1.0 (May 2025)** — the
citation-safe public source covering architecture, registers, and all 29 instruction
groups (§5). Old code samples: archive only, not a focus.

Pattern sources for `pattern-library`:

- bunny_build `test/` — simple GPIO/goto samples
- `ezh` repo flat-samples — run-one-command-and-stop style patterns
- gibbon-d `ezh_app.cpp` (D:\prj\teenage_engineering\...) — multi-app RAM pool with
  offset dispatch, shared idle epilogue (CFM+HOLD), ARM2EZH parameter block, and
  `E_LOAD_32IMM` C-macro pseudo-instruction built on bunny_build
- avc (D:\prj\wavenumber\avc) — OV5640 continuous camera capture, DMA w/ IRQ,
  NXP smartdma blob drivers coexisting with vendored bunny_build

## Downstream tracks (explicitly out of this plan; parked as their own plans)

- `ezh-browser-simulator` — C simulator core compiled to WebAssembly, browser UI,
  ideally with debugging (breakpoints, register/flag view, disassembly). Decoder
  driven by the ISA db.
- `ezh-programming-models` — beyond on-target assembly: pseudo-instruction libraries,
  macro layers, possibly a higher-level DSL. bunny_build as the substrate.

bunny_build is the eventual home for everything: ISA db, doc generator, generated
HTML, simulator, tooling.

## Tooling history (context for docs and verification)

There was never real EZH tooling. The original "assembler" was the creator hacking the Keil
Arm compiler's inline assembler with C macros — single pass, so labels/branches
relied on compiler behavior that **broke in newer Arm compiler versions** (branch to
label stopped linking; workarounds were manual PC-distance math or literal-pool
dereference). bunny_build exists precisely to fix this: a true two-pass assembler
with first-class label resolution. Additionally, directive macros in the fsl header
(`E_DCD`, `E_DCD_VAL`, `E_LABEL`) were wrappers around Keil assembler syntax for
emitting constants/addresses into the stream — trivial in bunny_build since assembly
happens in runtime code. The docs should explain this history so readers understand
why mnemonics exist that aren't hardware instructions, and why bunny_build's surface
differs slightly from the header's.

## Strategy notes

- **Synthesize, don't copy.** The spec and fsl header carry NXP confidential banners;
  they inform, are never copied. AN14650 is public and citable. Track provenance per
  section.
- Docs must serve all levels: low-level (bit encodings, for tool writers) through
  high-level help (how do I capture a camera frame).
