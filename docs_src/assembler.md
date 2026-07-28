+++
type = "doc_chapter"
id = "assembler"
title = "The bunny_build Assembler"
section = 4
status = "draft"
created = "2026-07-25"

# Provenance is carried here, not in the body, so that non-public source ids can
# never reach rendered output. See docs/design/isa-doc-generator.html.
# This chapter's primary source is bunny_build's own source, which is public.

[[provenance]]
section = "thesis"
sources = ["bunny_build"]
detail = "include/bunny_build.h, src/bunny_build.c: the library surface and the ezh_program(void) contract"

[[provenance]]
section = "history"
sources = ["an14650", "spec_b_06"]
detail = "AN14650 §4.1.1-4.1.3 (IDE support, scatter file, macros as pseudo-instructions). Tooling history recorded in the ezh-instruction-set-docs plan body"

[[provenance]]
section = "two-pass"
sources = ["bunny_build"]
detail = "src/bunny_build.c bunny_build__relocate() and bunny_build__add_instruction(): pass_num 0 counts and records, pass_num 1 emits; idx reset between passes"

[[provenance]]
section = "labels"
sources = ["bunny_build"]
detail = "src/bunny_build.c bunny_build__add_label()/bunny_build__label_get_address(); src/bunny_build__psuedo_instr.c E_LABEL(); src/bunny_build__instr.c label-taking branch forms"

[[provenance]]
section = "relocation"
sources = ["bunny_build"]
detail = "src/bunny_build.c: bunny_build() passes the array address as the base; bunny_build__relocate() takes an independent base"

[[provenance]]
section = "directives"
sources = ["bunny_build", "an14650"]
detail = "src/bunny_build__psuedo_instr.c E_LABEL/E_DCD/E_DCD_VAL; AN14650 §4.2.15.2 shows the historical E_DCD label-table idiom"

[[provenance]]
section = "pseudo"
sources = ["bunny_build", "an14650"]
detail = "src/bunny_build__psuedo_instr.c E_LOAD_32IMM and E_END/E__END; AN14650 §4.2.4 for why a 32-bit load must be synthesized from 11-bit immediates"

[[provenance]]
section = "park"
sources = ["bunny_build"]
detail = "src/bunny_build__psuedo_instr.c E_END()/E__END(); CFM value 0xDB6DB600 decoded against the bit-slice event encoding in isa/ezh_b/arch.toml [bit_slice_cfg]"

[[provenance]]
section = "gotchas"
sources = ["bunny_build"]
detail = "src/bunny_build__instr.c (undefined-label fallback, 0x1FFFFF branch mask); src/bunny_build__psuedo_instr.c (E_LOAD_32IMM stack use, E_END/E__END park helper spellings)"

[[provenance]]
section = "worked-example"
sources = ["bunny_build"]
detail = "test/lpc55s69__ezh_hello_gpio/source/ezh_app.c, reproduced from this repository"

[[unverified]]
id = "goto-window-2mb"
status = "resolved"
section = "gotchas"
claim = "E_GOTO to a label reaches only the low 2 MB of the architecture's 8 MB branch window - the encoding is correct within that range, the range is purely the mask"
basis = "Challenged in review as possibly a 4x offset defect, on the grounds that bunny_build shifts a BYTE address by 9 while the ISA field is a WORD immediate at [31:11]. Settled by round-tripping bunny_build's encoder against goto.toml's decode model: a word-aligned byte address shifted left 9 places bits [20:2] - the word index - exactly in the immediate field, and imm << 2 recovers the byte address. Exact for every address below 2 MB, aliasing above. Verified across all 524288 word addresses in [0, 2MB): widening the mask to 0x7FFFFF changes zero encodings, so it is a safe enhancement rather than a bug fix. Form bit 9 never collides with the shifted address because word-aligned addresses have bits [1:0] clear"
resolve_by = "closed by construction; the assembler change (0x7FFFFF at the four label-taking branch forms) remains an open enhancement"
+++

# The bunny_build Assembler

The [architecture chapter](architecture.html) describes the machine and the
[instruction reference](instructions.html) describes its opcodes. This chapter is about
how you actually write a program for it.

## Assembly is a function call {#thesis}

bunny_build is not a command-line tool that consumes a `.s` file. It is a **C library**,
and an EZH program is a **C function that emits instructions when you call it**:

```c
void ezh_app(void)
{
    E_NOP;
    E_BSET_IMM(GPO, GPO, 3);
    E_GOSUB("toggle");
}
```

That function is not the program — running it *produces* the program. You hand it to the
builder along with somewhere to put the result:

```c
uint32_t ezh_prog[256];
uint32_t words = bunny_build(ezh_prog, 256, ezh_app);
```

`bunny_build()` calls `ezh_app` twice (see [two passes](#two-pass)) and leaves the encoded
instruction words in `ezh_prog`. Point `EZHB_BOOT` at that array, set the ignition bit, and
EZH runs it.

Three consequences follow, and they are the whole reason the library is shaped this way:

**You get C where the assembler's directives would be.** Loops that unroll instruction
sequences, `#define`d pin numbers, `if` around optional blocks, tables generated with a
`for` — all of it is ordinary C running at assembly time. There is no macro language to
learn because the macro language is C.

**Assembly can happen on the target, at run time.** The program can be rebuilt while the
system is live — different parameters, a different pin, a different sample rate — without
a toolchain anywhere in sight. That is the *on-target assembly* model, and it is something
a conventional assembler cannot do at all.

**There is no separate build step to keep in sync.** The EZH program is compiled by the
same compiler, from the same tree, as the Arm code that boots it.

## Why this exists {#history}

There was never real EZH tooling. The original "assembler" was a Keil Arm inline-assembler
macro layer: each `E_*` macro emitted a literal word into the instruction stream.

That worked, with one structural problem: **it was single-pass**. A macro emitting a branch
had to know the target address at the point it expanded, and it did not, so branch-to-label
leaned on compiler behaviour to resolve the reference later. That behaviour **broke in
newer Arm compiler versions** — branch to label stopped linking. The workarounds were
manual PC-distance arithmetic or literal-pool dereferences, both of which have to be
recomputed by hand every time an instruction is inserted anywhere above them.

bunny_build exists to fix precisely that. A second pass gives it first-class label
resolution, which is the one thing the macro-based approach could not have. The directive
macros in the old header (`E_DCD`, `E_DCD_VAL`, `E_LABEL`) were wrappers around Keil
assembler syntax for emitting constants into the stream; in bunny_build they are ordinary
C functions, because emitting a constant is trivial when assembly is just code running.

This history explains two things you will otherwise find puzzling: why some `E_*` names are
not hardware instructions at all, and why bunny_build's surface differs slightly from the
published header's.

## Two passes {#two-pass}

`bunny_build__relocate()` calls your program function **twice**:

```
pass 0   bunny_build__pass_num = 0    count instructions, record label addresses
                                      -> nothing is written to the output array
pass 1   bunny_build__pass_num = 1    emit encoded words, resolve label references
```

`bunny_build__idx` — the instruction index — is reset to zero between the passes. Pass 0
walks the program to learn where everything lands; pass 1 walks it again and, now knowing
every label's address, encodes for real.

That yields one invariant, and it is the only rule you must not break:

> **Every instruction function must emit in *both* passes.**

`bunny_build__add_instruction()` increments `idx` unconditionally and only stores a word
when `pass_num == 1`. The label-taking branches make the same accommodation explicitly: in
pass 0 they emit a placeholder zero purely so the index keeps advancing.

```c
else
{
    //make sure to always add something in pass 0 so address get resolved in pass 1
    bunny_build__add_instruction(0);
}
```

If you write your own helper that emits conditionally — say, one that skips an instruction
in pass 0 — every label after it resolves one word too low, and the failure appears as a
branch landing one instruction off. Emit unconditionally, always.

Note also that the passes must be **deterministic**. Your program function runs twice, and
it must emit the same instruction sequence both times. Branching on something that changes
between the calls (a volatile read, a counter you forgot to reset) desynchronises the
passes in exactly the same way.

## Labels {#labels}

`E_LABEL("name")` records the current position:

```c
bunny_build__labels[n].address = bunny_build__base_address + (bunny_build__idx * 4);
```

It does this **in pass 0 only** — the table is built on the first walk and read on the
second. Branches take the label as a string and resolve it during pass 1:

```c
E_LABEL("toggle");
    E_BSET_IMM(GPO, GPO, 3);
    E_WAIT_FOR_BEAT();
    E_BCLR_IMM(GPO, GPO, 3);
    E_GOSUB("toggle");
```

The label-taking forms are [[E_GOTO]], [[E_GOSUB]], `E_GOTOL`, `E_COND_GOTO` and
`E_COND_GOTOL`. The register-target forms ([[E_GOTO_REG]], [[E_GOTO_REGL]] and their
conditional variants) take a register instead and need no resolution.

Two limits worth knowing. The label table is a fixed array sized by
`BUNNY_BUILD_MAX_LABELS`, and adding a duplicate name is rejected rather than overwriting —
`bunny_build__add_label` returns `bunny_build_label__exists` and the original address
stands. Both conditions print a diagnostic.

## Relocation: assembling for somewhere else {#relocation}

There are two entry points, and the difference is where the program will *live* versus
where you are assembling it:

```c
/* Assembling on the target, into the memory EZH will execute from. */
uint32_t bunny_build(uint32_t *array, uint32_t len, void (*prog)(void));

/* Assembling anywhere, for a program that will live at some other address. */
uint32_t bunny_build__relocate(uint32_t *array, uint32_t len,
                               uint32_t base_address, void (*prog)(void));
```

`bunny_build()` is the on-target case and simply passes the array's own address as the
base. `bunny_build__relocate()` takes the base separately, which is what lets you assemble
on a PC — where the buffer is somewhere irrelevant — for a program that will be loaded to a
known address on the device. Labels resolve to `base_address + idx * 4`, so the base is
what makes the resulting words correct for their eventual home.

This is also what makes the byte-for-byte camera test possible: assemble on a host, compare
against a known-good blob.

## Directives {#directives}

Three functions exist that are not hardware instructions.

**`E_LABEL(const char *name)`** — records a position. Emits nothing.

**`E_DCD_VAL(uint32_t val)`** — emits a literal word into the instruction stream. This is
how you place a constant, a configuration value, or a jump table entry inline. It is a real
word in the program image, so control flow must not run into it.

**`E_DCD(uint32_t loc)`** — **deprecated, and deliberately loud.** In the Keil-era header
this placed the *address of a symbol* into the stream, which is how label tables were built
before label resolution existed. bunny_build keeps the name only to catch ported code: it
emits a zero and prints an error on pass 1.

```c
void E_DCD(uint32_t loc) { bunny_build__add_instruction(0); if (bunny_build__pass_num) { ... "E_DCD NOT YET IMPLEMENTED" ... } }
```

If you are porting a program built on the `E_DCD`-table idiom — build a table of label
addresses, load one with an index, branch through it — you do not need the table. Use a
label and a conditional branch, or keep the table and fill it with `E_DCD_VAL` of addresses
you resolve yourself. The [architecture chapter](architecture.html#two-ahead) covers the
computed-branch mechanics.

## Pseudo-instructions {#pseudo}

These look like instructions and expand to several.

### `E_LOAD_32IMM(rx, imm)` — load a full 32-bit constant

[[E_LOAD_IMM]] carries an 11-bit signed immediate, so a 32-bit constant has to be built.
The pseudo-instruction does it in the obvious way — four shifted loads OR'd together —
using `R5` as scratch and preserving it:

```c
E_PUSH(R5);
E_LOAD_SIMM(rx, (uint8_t)(imm >> 24), 24);
E_LOAD_SIMM(R5, (uint8_t)(imm >> 16), 16);
E_OR(rx, rx, R5);
E_LOAD_SIMM(R5, (uint8_t)(imm >> 8),  8);
E_OR(rx, rx, R5);
E_LOAD_IMM (R5, (uint8_t)(imm));
E_OR(rx, rx, R5);
E_POP(R5);
```

Nine instructions, and two things to keep in mind. It **uses the stack**, so `SP` must
already be valid — this is one of the reasons the boot preamble loads `SP` first. And the
destination must be `R0`–`R7`; passing anything above `R7` prints an error, because the
sequence would clobber the scratch register or the destination's own semantics.

If you need a constant in `CFS` or `CFM`, build it in a general-purpose register and move
it, or do what [the park pattern](#park) does and construct it with explicit loads.

## The park pattern {#park}

An EZH program that has finished should stop *cleanly*. Falling off the end runs whatever
words follow; spinning on a branch keeps the core fetching, which costs AHB bandwidth that
the Arm and other masters would rather have.

The park pseudo-instruction parks the core on a [[E_HOLD]] that can never be released:

```c
E_LABEL("END_LOOP");
    E_LOAD_IMM (CFS, 0);
    E_LOAD_SIMM(R0, 0xDB, 24);
    E_LOAD_SIMM(R1, 0x6D, 16);
    E_LOAD_SIMM(R2, 0xB6,  8);
    E_XOR(R0,  R0, R1);
    E_XOR(CFM, R0, R2);
    E_HOLD();
    E_GOTO("END_LOOP");
```

The trick is the `CFM` value. Those three shifted loads and two XORs build:

```
R0  = 0xDB000000
R1  = 0x006D0000        R0 ^ R1 = 0xDB6D0000
R2  = 0x0000B600      CFM      = 0xDB6DB600
```

`0xDB6DB600` looks arbitrary until you split it the way the Boolean detector does.
`CFM[7:0]` is `0x00`, so **every OR-enable is cleared**. `CFM[31:8]` is `0xDB6DB6`, which in
binary is `110` repeated eight times — and `110` is `6`, the bit-slice event setting
`BS_0`, *always 0*.

So all eight slices are forced to constant zero, and no slice is routed to the logical
combiner by an OR-enable. Whichever way you read the chain's termination — the
[architecture chapter](architecture.html#boolean-detection) notes that slice 7's result
reaches the combiner regardless — the combiner sees zero either way, because every slice
*value* is zero. The combiner output can never go high, the `BS` flag can never assert, and
the [[E_HOLD]] therefore never releases. The core stops fetching and waits forever, using no
bus bandwidth. The trailing [[E_GOTO]] back to the label is a belt-and-braces: if the hold
*does* somehow release, execution loops back and re-parks rather than running on into
whatever follows.

The repeated-`110` construction is why the constants are `0xDB`, `0x6D`, `0xB6` — three
bytes of a repeating three-bit pattern, which is exactly what you can assemble from shifted
11-bit immediates without touching the stack.

> **This idiom predates bunny_build.** The eight-instruction sequence appears
> character-for-character across NXP's own sample corpus — eight times in the feature-demo
> file alone, eight more in the display-controller sources, and once in third-party
> production code. It is the corpus's *standard program terminator*, not one program's
> trick. bunny_build did not invent the park; it packaged an established idiom as a
> pseudo-instruction so it stops being eight lines you copy between programs.

Call it as `E_END()` from the public header. `E__END()` is also declared and kept as the
historical spelling used in older notes and examples; both spellings emit the same park
sequence.

> **Signalling the Arm is a separate step.** The park does not raise an interrupt. If the
> Arm needs to know the program finished, issue [[E_INT_TRIGGER]] before parking —
> `E_INT_TRIGGER(0)` is the idiomatic "done" signal, since the common interrupt output
> fires regardless of the channel mask (see
> [architecture](architecture.html#arm-ezh)). The sample corpus does exactly this, in that
> order: programs carrying the park block issue `E_INT_TRIGGER(0)` on the instruction
> immediately before entering it. Across the deduplicated corpus `E_INT_TRIGGER(0)` occurs
> roughly sixty times — including thirty-five in a single display-controller source — which
> is worth knowing given that AN14650 §4.2.14 describes a zero argument as out of spec.

## Gotchas {#gotchas}

**An undefined label does not stop the build.** The branch prints an error and emits a zero
word — which decodes as a valid [[E_MOV]], not a trap. Your program will assemble, run, and
misbehave. Read the build output; bunny_build is chatty by design and the error is there.

**Branch-to-label reaches 2 MB, not 8 MB.** The architecture's immediate branch covers an
8 MB window. bunny_build masks the resolved address with `0x1FFFFF` before shifting it into
place, which limits label branches to the low 2 MB.

The encoding is *correct* within that range, which is worth stating precisely because the
shift makes it look wrong at a glance. bunny_build shifts a **byte** address left by 9,
while the instruction field is a **word** immediate at bits `[31:11]`. Those agree: a
word-aligned byte address shifted by 9 places its bits `[20:2]` — the word index — exactly
in the immediate field, and the hardware's `imm << 2` recovers the byte address. Round-trip
is exact for every address below 2 MB, and aliases above it.

Widening it is a one-constant change (`0x7FFFFF` in place of `0x1FFFFF`, at the four
label-taking branch forms) and is **byte-for-byte identical** for every program that
already fits in 2 MB — so it is a safe enhancement, not a bug fix. Recorded in the ISA
database as an improvement opportunity.

**`E_LOAD_32IMM` needs a working stack.** It pushes and pops `R5`. Load `SP` from the
parameter block before using it.

**`E_LOAD_32IMM` warns about a bad destination and then emits anyway.** The guard prints an
error for a destination above `R7` but does not return, so the nine-instruction sequence is
still generated — with a destination whose semantics the sequence does not respect. Same
shape as the undefined-label case: a diagnostic you have to read, not a stop.

**Your program function runs twice.** Anything with a side effect outside the instruction
stream happens twice, and anything that varies between the two calls corrupts label
resolution. Keep the function pure.

## A complete program {#worked-example}

From this repository's LPC55S69 test, unmodified — a GPIO square wave that counts cycles
and notifies the Arm:

```c
void ezh_app(void)
{
    E_NOP;
    E_NOP;
    E_PER_READ(R6, ARM2EZH);   // parameter block pointer
    E_LSR(R6, R6, 2);          // strip the mode bits [1:0]
    E_LSL(R6, R6, 2);
    E_LDR(SP, R6, 0);          // para.coprocessor_stack
    E_LDR(R7, R6, 1);          // para.p_buffer

    E_BSET_IMM(GPO, GPO, EZH_OP_1);   // drive it high
    E_BSET_IMM(GPD, GPD, EZH_OP_1);   // and make it an output

    E_HEART_RYTHM_IMM(37493);         // ~250 us beat at 150 MHz

E_LABEL("toggle");
    E_BSET_IMM(GPO, GPO, EZH_OP_1);
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_BCLR_IMM(GPO, GPO, EZH_OP_1);

    E_ADD_IMM(R0, R0, 1);             // count this cycle
    E_PER_WRITE(R0, EZH2ARM);         // and interrupt the Arm
    E_STR(R7, R0, 0);                 // publish it to the buffer

    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_GOSUB("toggle");
}
```

Everything this chapter covers is visible in it. The two leading [[E_NOP]]s cover the
discarded boot word. The `ARM2EZH` preamble recovers the parameter block, masking off the
mode bits the register carries in `[1:0]`, and loads `SP` before anything needs a stack.
`E_LABEL` plus [[E_GOSUB]] gives a loop with no hand-computed offsets — insert an
instruction anywhere above and the branch still lands correctly, which is the entire point
of the second pass. `EZH_OP_1` is a plain `#define`, resolved by the C compiler long before
any of this reaches EZH.

One detail worth noticing: the loop is closed with [[E_GOSUB]] rather than [[E_GOTO]].
[[E_GOSUB]] overwrites `RA` every time round, which is harmless here because nothing returns
through it — but it is a habit worth breaking in code that does use `RA`. [[E_GOTO]] is the
right instruction for a loop that never returns.
