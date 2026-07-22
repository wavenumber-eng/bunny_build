+++
type = "adr"
id = "isa-adr-0001"
domain = "isa"
status = "accepted"
title = "TOML slice-based ISA description as single source of truth"
created = "2026-07-21"
+++

## Context

The EZH Arch B documentation effort (plan `ezh-instruction-set-docs`) needs a single
machine-readable description of the instruction set that can drive, in order of
realization: the doc generator, encoding verification against the original fsl
header and the bunny_build encoders, C encoder/assembler generation, a simulator
decoder (future C→WASM browser simulator), debugger/disassembler tables, and
Verilog decode/match logic. Today the encoding knowledge lives redundantly in the
hand-written fsl header (~1500 macros), bunny_build's inline functions, and prose in
NXP-confidential documents — none machine-consumable, none cross-checked.

Key structural facts driving the design:

- The ~1500 mnemonics are ~25 base 5-bit opcodes × a modifier matrix
  (COND / S / N / IMM / shift-fusion). The description must model the matrix, not
  the flat expansion.
- Real encodings contain **split fields** (PER_WRITE scatters a 20-bit address
  across two ranges; LOAD_SIMM splits a 5-bit shift amount). Any format that can
  only express contiguous bitfields is disqualified.
- GOSUB overlays every encoding with instruction bits [1:0] == 0b11, so decode is
  mask/match with most-specific-first precedence, not a simple opcode switch.

## Decision

TOML files under `isa/` in the bunny_build repo (bunny_build is the long-term home
for all EZH tooling):

- `isa/ezh_b/arch.toml` — registers, condition codes, bit-slice mux configs, and
  provenance source ids.
- `isa/ezh_b/fields.toml` — shared field definitions. A field is a list of
  **slices**, each mapping an instruction bit range to a value bit range
  (`{ instr = "31:24", value = "19:12" }`). Slices are the core abstraction: they
  express contiguous and split fields uniformly and translate mechanically to C
  shift/mask expressions, Verilog part-select assigns, and doc bitfield diagrams.
- `isa/ezh_b/opcodes/<name>.toml` — one file per base opcode: opcode value,
  semantics prose, restrictions, timing, provenance, and one or more **forms**.
  A form = `fixed` bits (decode mask/match derived from them) + `operands` +
  `modifiers` (both referencing shared fields). Modifier bit positions are declared
  per form — they are family-dependent, not global.
- `isa/tools/validate.py` — stdlib-only (tomllib) validator: slice width/range
  checks, double-claimed-bit detection, reference resolution, derived mask/match,
  demo emission of C encode macros and Verilog decode, and self-tests that encode
  known instructions through the slice model and compare against bunny_build's
  encoder formulas.

Semantics are prose-first (`semantics.prose` + `restrictions`). A structured
micro-op semantics language for the simulator is deliberately deferred; the schema
reserves room for it but does not block population on it.

### Decode mask vs canonical encoding

Bits in a form fall into three classes with distinct meanings:

- **fixed** — decode-significant: they participate in the derived mask/match, and a
  decoder rejects words that disagree. Encoders emit the declared value.
- **operand/modifier** — variable: excluded from the mask.
- **unclaimed** — *reserved-zero*: encoders emit 0 (the canonical encoding), but
  decoders treat them as don't-care. They are NOT part of the mask.

Consequently `fixed` must only cover bits the hardware is believed to actually
decode on. Declaring a full-word `fixed` (as the NOP worked example originally
did, before this section reduced it to opcode + sub-op selector) asserts that
hardware distinguishes a non-canonical NOP from a canonical one — a claim the fsl
header's emission formula alone cannot support. Where hardware decode
width is unverified, opcode files declare only the opcode bits (and any known form
selects) as fixed, and note the uncertainty in `provenance`/`notes` for
adjudication with the EZH creator. The disassembler renders words whose
reserved-zero bits are nonzero with a "(non-canonical)" annotation rather than
refusing to decode.

### Mnemonic patterns

Historical `E_*` mnemonic names are not mechanically derivable from field names
(MOV + N spells `MVN`, while LOAD_IMM + N spells `LOAD_IMMN`), yet the doc
generator and the three-way `verify-encodings` diff both need the exact ~1500-name
set. Each form therefore carries a machine-expandable `syntax` pattern in a small
formal notation:

- `[X]` — optional token (present iff the modifier it maps to is 1)
- `{A|B}` — alternation selected by a modifier value (e.g. `{MOV|MVN}` bound to
  the `n` field: 0 → MOV, 1 → MVN)
- literal text otherwise; tokens compose in pipeline execution order

Every bracket group binds positionally to a named field of the form:

```toml
mnemonic = { pattern = "E_[COND_]{MOV|MVN}[S]", binds = ["cond", "n", "s"] }
```

`binds[i]` names the field controlling the i-th bracket group (left to right).
For `[X]` the token is present iff the bound field is nonzero (for `cond`,
nonzero means not-EU). For `{A|B}` the bound field's value indexes the
alternative. A group may bind an operand when the historical names split on an
operand value (e.g. `{IMM|SIMM}` on the shift amount: zero → first alternative).
The validator checks group count == len(binds) and that every bind resolves.
Expansion of all patterns across all forms must reproduce the historical
mnemonic list exactly — any mismatch is a `verify-encodings` failure to
adjudicate, not a silent rename.

**Amendment 2026-07-21 (notation v2, validated against the full name list).**
Populating the patterns against the fsl header's 1502 names showed the
original notation could not express three real name grammars; the notation is
extended, additively, as follows (spec in `isa/README.md`, enforced by
`isa/tools/expand_mnemonics.py`):

- Alternatives may carry explicit values (`{BCLR=1|BTST=5|BSET=6|BTOG=7}`);
  the default remains the alternative's index. Needed where encoded selector
  values are sparse or reordered relative to the spelling.
- A form may declare a `mnemonics` list of patterns instead of a single
  `mnemonic`; each entry may pin fields non-positionally with
  `when = { field = value }`. This expresses token *reordering* driven by a
  field (register-shift `RLSL_ADD` vs `ADD_RLSL` on the order bit) and names
  that imply several bits at once (`_POST` sets writeback and post).
- Names differing only by optional-argument presence over one encoding
  (`E_ADD` vs `E_ADD_LSL`) are separate pattern entries; the operand-binding
  sentence above is superseded (the `{IMM|SIMM}` example is now two entries).
- Aliases expand as `E_[COND_]<name>` when their form is conditional.

The reproduction requirement is strengthened: expansion must match the fsl
name list exactly AND each expanded name's bound field values must predict
that macro's base encoding word bit-for-bit (`expand_mnemonics.py` checks
both; 1502/1502 verified).

## Alternatives considered

- **JSON/YAML**: JSON has no comments (provenance notes matter); YAML brings
  indentation fragility and an extra parser dependency. TOML matches the wn-dev-std
  ecosystem, diffs well, and Python 3.12 parses it from the stdlib.
- **Custom DSL**: maximum expressiveness, but a parser to maintain and a barrier for
  contributors; unjustified when TOML + slices covers the real encodings found.
- **Keep C as the source of truth** (generate docs by parsing bunny_build headers):
  inverts the dependency — the assembler should eventually be *checked against* (and
  partly generated from) the ISA description, and hand-written C can't carry
  semantics, restrictions, timing, or provenance.

## Consequences

- Verification becomes mechanical: parse fsl header macros and bunny_build functions
  into encoding expressions, three-way diff against the db (`verify-encodings` step).
- Population effort is ~25 opcode files plus shared fields — bounded and reviewable;
  worked examples (mov, per_write, nop) validate the model against the hardest known
  cases (multi-form select bit, split fields, full-word fixed encoding).
- The doc generator, simulator, and any Verilog experiments consume one artifact;
  drift between docs, tools, and hardware description becomes a validator failure
  instead of a silent divergence.
- Discrepancies found during population (e.g. the broken E_COND_VECTORED_HOLD_NRA
  macro in the fsl header) get recorded in the db and adjudicated by the EZH creator.
