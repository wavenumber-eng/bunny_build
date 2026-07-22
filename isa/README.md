# EZH Arch B — Machine-Readable ISA Description

This directory is the **single source of truth** for the EZH (SmartDMA) Architecture B
instruction set. Everything else is generated from or verified against it:

1. documentation (static HTML instruction reference)
2. encoding verification (three-way diff vs the bundled reference header and the
   bunny_build encoders)
3. C encoder/assembler generation and validation (bunny_build)
4. simulator instruction decode (future: C core → WebAssembly)
5. debugger / disassembler tables (future)
6. HDL (Verilog decode/match logic for experiments and verification)

Format: TOML. Layout:

```
isa/
  ezh_b/
    arch.toml            # registers, condition codes, bit-slice configs
    fields.toml          # shared field definitions referenced by opcode files
    opcodes/<name>.toml  # one file per base opcode
  tools/
    validate.py          # schema check + demo C/Verilog emission
    extract_header.py    # numeric probe of bunny_build__instr.h -> JSON inventory
    verify_encodings.py  # name-free check of ALL header encoder fns vs the db
```

## Core model

An **instruction word is 32 bits**. The base opcode lives in bits `[4:0]`
(exception: `GOSUB` claims every encoding with `[1:0] == 0b11`; decoders must match
most-specific-first, i.e. sort by mask popcount descending).

Each opcode file declares one or more **forms** (distinct encodings sharing the
opcode, e.g. MOV register vs MOV immediate, selected by a fixed bit). A form is:

- `fixed` — decode-significant bits with hard values; mask/match are derived
  from them. Unclaimed bits are *reserved-zero*: canonical encoders emit 0,
  decoders treat them as don't-care .
- `operands` / `modifiers` — named references into `fields.toml`.
- `mnemonic` — pattern + positional binds reproducing the historical E_* names.

Opcode files may also declare `[[aliases]]`: a historical mnemonic that is a
form with baked operand/modifier values (e.g. `E_POP` = LDR word + writeback,
`src1 = SP`, `offset8s = -1`). `verify_encodings.py` checks alias words too.

A **field** maps *value bits* to *instruction bits* as a list of **slices**:

```toml
[fields.per_addr20_w]
desc = "peripheral byte address, word aligned, 1MB window (split encoding)"
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

## Validation

Run the ISA checks:

```sh
uv run python isa/tools/validate.py
uv run python isa/tools/verify_encodings.py
uv run python isa/tools/expand_mnemonics.py
uv run python isa/tools/verify_fsl.py
```

The mnemonic and macro checks use the bundled reference header. Use `--header PATH`
to compare with another header. Attribution and authoring records are maintained
separately from this repository.
