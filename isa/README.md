# EZH Arch B — Machine-Readable ISA Description

This directory is the **single source of truth** for the EZH (SmartDMA) Architecture B
instruction set. Everything else is generated from or verified against it:

1. documentation (static HTML instruction reference)
2. encoding verification (three-way diff vs the original fsl header and the
   bunny_build encoders)
3. C encoder/assembler generation and validation (bunny_build)
4. simulator instruction decode (future: C core → WebAssembly)
5. debugger / disassembler tables (future)
6. HDL (Verilog decode/match logic for experiments and verification)

Format: TOML (see ADR isa-adr-0001). Layout:

```
isa/
  ezh_b/
    arch.toml            # registers, condition codes, bit-slice configs, sources
    fields.toml          # shared field definitions referenced by opcode files
    opcodes/<name>.toml  # one file per base opcode
  tools/
    validate.py          # schema check + demo C/Verilog emission
    extract_header.py    # numeric probe of bunny_build__instr.h -> JSON inventory
    verify_encodings.py  # name-free check of ALL header encoder fns vs the db
    extract_fsl.py       # numeric probe of the original fsl header (read in place)
    verify_fsl.py        # three-way check: fsl <-> db <-> bunny_build + report
    expand_mnemonics.py  # mnemonic patterns -> exact 1502-name reproduction
    gen_docs_spike.py    # doc-generator spike (superseded by build-static-html)
```

## Core model

An **instruction word is 32 bits**. The base opcode lives in bits `[4:0]`
(exception: `GOSUB` claims every encoding with `[1:0] == 0b11`; decoders must match
most-specific-first, i.e. sort by mask popcount descending).

Each opcode file declares one or more **forms** (distinct encodings sharing the
opcode, e.g. MOV register vs MOV immediate, selected by a fixed bit). A form is:

- `fixed` — decode-significant bits with hard values; mask/match are derived
  from them. Unclaimed bits are *reserved-zero*: canonical encoders emit 0,
  decoders treat them as don't-care (see isa-adr-0001).
- `operands` / `modifiers` — named references into `fields.toml`.
- `mnemonic` (or a `mnemonics` list) — patterns + positional binds reproducing
  the historical E_* names; see "Mnemonic patterns" below.

Opcode files may also declare `[[aliases]]`: a historical mnemonic that is a
form with baked operand/modifier values (e.g. `E_POP` = LDR word + writeback,
`src1 = SP`, `offset8s = -1`). `verify_encodings.py` checks alias words too.

A **field** maps *value bits* to *instruction bits* as a list of **slices**:

```toml
[fields.per_addr20_w]
desc = "Peripheral byte offset from 0x4000_0000 within the 1MB window, word aligned (PER_WRITE split encoding; 18 offset bits encoded)"
slices = [
  { instr = "31:24", value = "19:12" },
  { instr = "19:10", value = "11:2"  },
]
```

Contiguous fields have one slice. Split fields (real examples: `PER_WRITE` address,
`LOAD_SIMM` shift amount) have several. This slice model is what makes the data
directly usable for C (`(((v)>>12 & 0xff) << 24) | ...`), Verilog
(`assign addr[19:12] = instr[31:24];`), and bitfield diagrams alike.

## Modifier grammar

The ~1500 historical `E_*` mnemonics are ~25 base opcodes × a modifier matrix.
Mnemonics compose **in pipeline execution order** (e.g. `E_SUBN_LSLS` = subtract →
invert → shift left → set flags):

| token | meaning | typical encoding |
|-------|---------|------------------|
| `COND_` | conditional execution | `cond` field `[8:5]` ≠ `EU` |
| `S` suffix | set flags (ALU/MOV families) | bit 9 |
| `S` suffix | *signed* access (LDRB/LDR_REG load families) | bit 21 |
| `N` | invert result | bit 31 (MOV), bit 19 (ALU), bit 27 (register-shift) |
| `IMM` | immediate operand form | form-select fixed bit |
| `LSL/LSR/ASR/ROR` | barrel-shift fusion (pre/post by position) | family-dependent |
| `F/FEND/FBIT` | endian / bitwise flip | family-dependent |
| `R` prefix | shift amount from register | family-dependent |

Modifier bit positions are declared **per form** in the opcode files — do not assume
they are global.

## Mnemonic patterns (notation v2)

Each form carries one `mnemonic = { pattern, binds }` or a
`mnemonics = [ {...}, ... ]` list. Bracket groups bind positionally to
`binds`, left to right:

- `[X]` — optional token. Bound field 1 → token present; for `cond`, presence
  means the `COND_` variant that takes a cond argument (no base-word bits).
- `{A|B=n|...}` — alternation; the bound field takes the alternative's value
  (its index by default, `=n` explicit — needed where encoded values are
  sparse, e.g. `{BCLR=1|BTST=5|BSET=6|BTOG=7}`). An empty alternative
  contributes no text.
- `when = { field = value, ... }` — pins fields non-positionally. Used where
  token *order* depends on a field (rshift: `RLSL_ADD` vs `ADD_RLSL` on the
  order bit) and where a name implies several bits (`_POST` sets writeback
  AND post).

Names that share an encoding but differ by optional-argument presence
(`E_ADD` vs `E_ADD_LSL`, `E_LOAD_IMM` vs `E_LOAD_SIMM`) are separate pattern
entries. Aliases expand as `E_[COND_]<name>` automatically when their form is
conditional.

`expand_mnemonics.py` enforces the ADR contract mechanically: the expansion
of all patterns must reproduce the fsl header's 1502-name list *exactly*, and
every name's bound field values must predict its macro's base word
bit-for-bit — a pattern that spells the right name with the wrong binding
fails.

## Editing rules

- `sv_tb` is an **internal analysis source**: cite it only inside
  `[[provenance]]` blocks (which never render) and never name it in prose,
  restrictions, notes, syntax strings, or citation details - rendered text
  says "hardware analysis (advisory)" or states the fact without
  attribution.

- One base opcode per file; keep prose semantics (`semantics.prose`) in sync with
  cited sources and record `provenance` (source ids from `arch.toml`).
- Never copy text from NXP-confidential sources (the Arch B spec, the fsl header).
  AN14650 (public SmartDMA Cookbook) is citable.
- Run `uv run python isa/tools/validate.py` before committing — it rejects
  overlapping bits, out-of-range slices, width mismatches, opcode-value typos
  and duplicates, and prints the derived C/Verilog to eyeball.
- Run `uv run python isa/tools/verify_encodings.py` after any encoding change —
  it structurally matches every encoder function in `bunny_build__instr.h`
  (1492 of them) against exactly one form or alias of the db, with no reliance
  on mnemonic names, plus direct formula checks for the non-inline NOP, GOSUB,
  and GOTO. A db bit in the wrong place fails loudly, and the extractor
  reconciles matched functions against declared ones so nothing drops silently.
- Run `uv run python isa/tools/verify_fsl.py` for the full three-way check
  against the original fsl header (authority #1): constants, structure,
  header-vs-header diff, dead forms, phantom modifiers/operands, plus the
  adjudication report of known-defective macros.
- Run `uv run python isa/tools/expand_mnemonics.py` after touching any
  `mnemonic` data — it must report the exact 1502-name reproduction with all
  bases verified.
