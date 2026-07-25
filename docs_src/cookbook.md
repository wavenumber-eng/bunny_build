+++
type = "doc_chapter"
id = "cookbook"
title = "Cookbook: Patterns and Idioms"
section = 5
status = "draft"
created = "2026-07-25"

# Provenance is carried here, not in the body, so that non-public source ids can
# never reach rendered output. Patterns are drawn from a deduplicated corpus of
# 87 EZH programs across four codebases; see the sample-mining plan logs.

[[provenance]]
section = "how-to-read"
sources = ["bunny_build"]
detail = "Corpus inventory and dedup method recorded in plan logs corpus-inventory-and-catalog and corpus-counts-deduplicated"

[[provenance]]
section = "boot-preamble"
sources = ["an14650", "bunny_build"]
detail = "AN14650 §4.2.12 shows the ARM2EZH/mask/SP sequence; 68 of 87 deduplicated corpus programs use it verbatim"

[[provenance]]
section = "signal-and-park"
sources = ["bunny_build", "spec_b_06"]
detail = "Park block appears in seven distinct corpus sources (8x in the feature-demo file, 8x in a display-controller source, once in third-party production code) and is implemented as E__END in src/bunny_build__psuedo_instr.c. Spec E_INT_TRIGGER section for the common-interrupt-always-fires rule"

[[provenance]]
section = "multi-app"
sources = ["bunny_build"]
detail = "gibbon-d (teenage engineering) app/src/ezh_app.cpp: ezh_app_offset[] pool, sequential bunny_build() into shared ezh_ram, dispatch by offset in ezh__execute_command()"

[[provenance]]
section = "events"
sources = ["an14650", "bunny_build"]
detail = "AN14650 §4.2.8 vectored-hold dispatch and table discipline; corpus: EZH_ButtonBitslice (key scan), EZH_PendingTrap, the camera interface's bit-slice dispatch"

[[provenance]]
section = "timing"
sources = ["bunny_build", "an14650"]
detail = "EZH_PWMClock in the feature-demo source: heartbeat + tight loop + E_SYNCH_ALL_TO_BEAT(1) + E_MODIFY_GPO_BYTE. AN14650 §4.2.7 for heartbeat semantics"

[[provenance]]
section = "data-movement"
sources = ["an14650", "bunny_build"]
detail = "AN14650 §4.2.10 performance note (batched loads vs immediate consumption); the display-controller sources are the largest worked examples"

[[provenance]]
section = "subroutines"
sources = ["bunny_build", "an14650"]
detail = "EZH_FunctionCall in the feature-demo source; AN14650 §4.2.11 for the RA discipline"

[[provenance]]
section = "protocol"
sources = ["bunny_build"]
detail = "gibbon-d ezh_app__spi_wr / ezh_app__spi_rd: byte loops, GOSUB subroutines, polling"

[[provenance]]
section = "capture"
sources = ["bunny_build"]
detail = "avc (wavenumber) bv_camera__interface.c: OV5640 continuous capture, per-frame re-boot with a fresh buffer pointer, GPIO IRQ handlers"

[[provenance]]
section = "debug"
sources = ["an14650", "bunny_build"]
detail = "AN14650 §4.2.12 breakpoint pair; corpus EZH_SetRegisters / EZH_RegistersDump and the register-dump-to-buffer idiom"

[[provenance]]
section = "algorithmic"
sources = ["an14650", "spec_b_06", "bunny_build"]
detail = "EZH_ConditionFlag - the only program in the deduplicated corpus using SPO/SNE. AN14650 §4.2.5.2.1 reproduces its shift-accumulate sequence; spec §4.5 for the 16x16 multiply"

[[unverified]]
id = "corpus-representativeness"
status = "open"
section = "how-to-read"
claim = "Frequency counts describe the surviving sample corpus, not EZH practice generally"
basis = "87 deduplicated programs across four codebases, heavily weighted toward NXP demo material (70 of 87). Rare-idiom counts in particular are small enough that one unfound codebase would move them. They are reported because 'one program in the corpus does this' is useful information about documentation coverage, not because they measure what engineers write"
resolve_by = "not resolvable; stated so the numbers are not over-read"
+++

# Cookbook: Patterns and Idioms

The [architecture chapter](architecture.html) describes the machine and the
[assembler guide](assembler.html) describes how to write for it. This chapter is the
part you copy from.

## How to read this chapter {#how-to-read}

Every pattern here comes from working code — a deduplicated corpus of 87 EZH programs
across four codebases: NXP's sample material, bunny_build's own tests, teenage
engineering's gibbon-d, and wavenumber's avc. Where a pattern is rare in that corpus, this
chapter says so, because that is useful information: it usually means the feature is
under-documented rather than useless.

One number worth carrying: **the algorithmic flags are used by exactly one program in the
entire corpus, and register-sourced shifts by exactly one** — both in the same NXP feature
demonstration. Those are real architecture features with a single worked example anywhere.
If you need them, the example below may be all there is.

## The boot preamble {#boot-preamble}

Almost every EZH program starts the same way, and 68 of the 87 corpus programs use this
sequence essentially verbatim:

```
E_NOP                        ; the boot word is discarded
E_PER_READ(R6, ARM2EZH)      ; parameter block pointer
E_LSR(R6, R6, 2)             ; strip the interrupt-mode bits [1:0]
E_LSL(R6, R6, 2)
E_LDR(SP, R6, 0)             ; member 0: the stack
E_LDR(R7, R6, 1)             ; member 1: whatever you passed next
```

Three things are happening. The leading [[E_NOP]] covers the
[discarded boot word](architecture.html#system-context). The `LSR`/`LSL` pair masks off
`EZHB_ARM2EZH[1:0]`, which the hardware uses for interrupt mode — pass a 4-byte-aligned
pointer and those bits are yours to strip. And `SP` is loaded *first*, because
`E_LOAD_32IMM` and anything using [[E_PUSH]] needs a working stack.

Load the rest of your parameters by word offset from `R6`. The struct on the Arm side is
just a `uint32_t` array as far as EZH is concerned.

## Signal and park {#signal-and-park}

A program that has finished should stop without burning bus bandwidth. The corpus's
standard terminator — present in seven distinct sources including third-party production
code — is: raise an interrupt, then park forever.

```
E_INT_TRIGGER(0)             ; tell the Arm we are done
E_LABEL("END_LOOP")
    E_LOAD_IMM (CFS, 0)
    E_LOAD_SIMM(R0, 0xDB, 24)
    E_LOAD_SIMM(R1, 0x6D, 16)
    E_LOAD_SIMM(R2, 0xB6,  8)
    E_XOR(R0,  R0, R1)
    E_XOR(CFM, R0, R2)       ; CFM = 0xDB6DB600: every slice "always 0"
    E_HOLD()
    E_GOTO("END_LOOP")
```

The [assembler guide](assembler.html#park) decodes the `CFM` constant. The short version:
all eight bit-slices are forced to constant zero, so the Boolean combiner can never assert
and the [[E_HOLD]] never releases. The core stops fetching entirely.

`E_INT_TRIGGER(0)` fires the common interrupt while selecting no hijack channels — see
[the interrupt mechanisms](architecture.html#arm-ezh). If you want to hijack a specific
peripheral's interrupt instead, pass its mask; avc's camera path uses `E_INT_TRIGGER(0xFFFFFF)`
to fire everything.

> Order matters. Park first and the interrupt never issues, because the core has stopped.

## Multi-app dispatch {#multi-app}

One EZH, several programs, chosen at run time. gibbon-d does this by assembling every
program into one shared RAM pool and remembering where each landed:

```c
uint32_t ezh_ram[EZH_RAM_WORDS];
uint32_t ezh_app_offset[EZH_APP_QTY];
uint32_t last_idx = 0;

ezh_app_offset[SPI_WRITE_APP] = last_idx;
last_idx += bunny_build(&ezh_ram[ezh_app_offset[SPI_WRITE_APP]],
                        sizeof(ezh_ram), ezh_app__spi_wr);

ezh_app_offset[SPI_READ_APP] = last_idx;
last_idx += bunny_build(&ezh_ram[ezh_app_offset[SPI_READ_APP]],
                        sizeof(ezh_ram) - (last_idx * 4), ezh_app__spi_rd);
```

`bunny_build()` returns the word count, so accumulating it gives the next free slot.
Dispatch is then a lookup and a boot:

```c
void ezh__execute_command(uint8_t cmd, EZHPWM_Para *params)
{
    if (cmd < EZH_APP_QTY) {
        selected_program = &ezh_ram[ezh_app_offset[cmd]];
        EZH_init_and_boot(selected_program, params);
    }
}
```

This is the shape to reach for whenever EZH has more than one job. Note what it is *not*:
there is no resident dispatcher program branching on a command word. Each app is
independently assembled and independently booted, and the Arm chooses by pointing
`EZHB_BOOT` somewhere different.

**Watch the remaining-space argument.** The first call above passes the whole pool size;
the second correctly passes what is left. Getting that wrong turns a pool overflow into a
silent overwrite of the previous app.

## Parameters are set up fresh on every run {#capture}

EZH has no persistent descriptor chain. Each boot writes a new parameter-block pointer to
`EZHB_ARM2EZH`, and the program re-reads it from the top — so the natural way to run
repeated work is to re-boot with different parameters rather than to build a descriptor
list once and let hardware walk it.

avc's camera path is the clearest example: a per-frame entry point takes the destination
buffer, and the frame program is booted afresh each time.

```c
void avc_camera__prepare_frame(uint16_t *buffer)
{
    /* buffer goes into the parameter block; EZH re-reads it on boot */
}
```

That is a genuine difference from a classic DMA controller, and it cuts both ways. You give
up hardware-walked scatter-gather; you gain a program that can decide anything at run time
about what it is capturing, where it is putting it, and what it does to the data on the
way. For variable-shape work — a format conversion, a protocol, a frame whose layout
depends on a register you just read — that trade is usually worth it.

## Waiting for events {#events}

Plain [[E_HOLD]] blocks until a configured bit-slice fires:

```
E_LOAD_IMM(CFS, 0)           ; slice 0 watches input 0
E_LOAD_IMM(CFM, 0x101)       ; slice 0 = rising edge, OR-enabled
E_HOLD()
```

[[E_VECTORED_HOLD]] blocks until *any* enabled term fires and dispatches through a table.
Populate every entry, even the ones you do not expect — dispatch is positional, and an
unexpected trigger on an unused slice will still branch to its slot:

```
E_VECTORED_HOLD(PC)
E_NOP                        ; flushed
E_NOP                        ; flushed
; --- table, one entry per slice ---
E_NOP                        ; slice 0 unused
E_GOTO("vsync")              ; slice 1
E_GOTO("hsync")              ; slice 2
E_NOP                        ; ...
```

A handler for a *sticky* slice must clear the latch, and any write to `CFM` does it —
conventionally `E_BSET_IMM(CFM, CFM, <slice>)`.

For key scanning, the corpus drives several slices from GPIO through the INPUTMUX and lets
the vectored hold do the debounce-free dispatch — the whole point being that there is no
interrupt entry cost to pay per key.

## Deterministic timing {#timing}

Two mechanisms, and they compose. `E_WAIT_FOR_BEAT` aligns one instruction to the
heartbeat; `E_SYNCH_ALL_TO_BEAT(1)` puts *every* instruction on the beat.

The corpus's clock generator is three instructions inside a tight loop:

```
E_HEART_RYTHM_IMM(9)         ; a beat every 10 core cycles
E_LOAD_IMM(R1, 1000)         ; 1001 iterations
E_ADD_IMM(R0, PC, 8)
E_TIGHT_LOOP(R0, R1)
E_SYNCH_ALL_TO_BEAT(1)       ; one-shot: enter snap-to-grid mode
E_MODIFY_GPO_BYTE(0xFF, 0, 0xFF)   ; toggle the low byte, every beat
```

The instruction after [[E_TIGHT_LOOP]] runs once — that is where the mode switch goes —
and the loop body is the single byte-modify, executing on a beat boundary every time. The
result is a jitter-free square wave on eight pins at once, with the core doing nothing
else and no interrupt anywhere. `E_SYNCH_ALL_TO_BEAT` takes a 1-bit operand, so pass `0`
to leave the mode again.

This is the pattern for anything that must not jitter: bit-banged protocols, sampling,
waveform generation.

## Moving and converting data {#data-movement}

The DFETCH unit holds one posted transaction, so the shape of a copy loop matters. Batch
the loads, then consume them:

```
E_LDR_POST(R2, R0, 1)        ; four loads issue back to back
E_LDR_POST(R3, R0, 1)
E_LDR_POST(R4, R0, 1)
E_LDR_POST(R5, R0, 1)
E_FEND_LSR(R2, R2, 0)        ; by now R2 has arrived
E_PER_WRITE(R2, 0x32200)
E_FEND_LSR(R3, R3, 0)
E_PER_WRITE(R3, 0x32204)
```

Consuming each value immediately after its load stalls on every one. Both versions are
correct; the batched one is meaningfully faster, and the difference is entirely in the
scheduling. See [data access acceleration](architecture.html#dfetch).

Conversion rides along for free. `FEND` byte-swaps and `FBIT` bit-reverses *before* the
ALU, so feeding a big-endian peripheral from little-endian memory costs nothing extra —
the swap fuses into an instruction that was happening anyway. The display-controller
sources are built almost entirely from this: load a batch, convert in flight, write to a
FIFO.

## Subroutines {#subroutines}

[[E_GOSUB]] saves the return address in `RA`, and `RA` is a single register — so nesting
requires saving it yourself:

```
E_GOSUB("func_1")
...
E_LABEL("func_1")
    E_PUSH(RA)               ; preserve before the nested call clobbers it
    E_GOSUB("func_2")
    E_POP(RA)
    E_GOTO_REG(RA)           ; return
E_LABEL("func_2")
    E_GOTO_REG(RA)           ; leaf: no save needed
```

A leaf function needs no discipline at all. One level of nesting needs exactly the
push/pop pair above. This is the whole of EZH's calling convention — there is no frame, no
argument area, no callee-saved set. Registers are shared and you agree with yourself about
who owns what.

> Do not close a plain loop with [[E_GOSUB]]. It overwrites `RA` every iteration; use
> [[E_GOTO]] unless you actually want the return address.

## Protocol emulation {#protocol}

gibbon-d drives an SPI PSRAM entirely from EZH, and the structure generalises to any
bit-banged or FIFO-driven protocol:

```
E_LABEL("WRITE_BYTES_LOOP")
    ...
E_LABEL("NEXT_BYTE_OUT")
    E_GOSUB("SPI_WR_BYTE")   ; one byte out, as a subroutine
    ...
E_LABEL("SPI_WR_BYTE")
    ...                      ; FIFO write, wait, return
```

Two things make this work well. The byte-level operation is a subroutine, so the outer
loop reads as the transaction and the inner one as the wire format. And the command
structure — opcode plus address plus payload — comes in through the parameter block, so
the same assembled program serves every command the device understands. EZH ends up
performing small memory operations on behalf of the Arm through what is effectively a
command queue.

## Debug recipes {#debug}

EZH has no debugger, so the corpus uses two techniques.

**Dump registers to memory the Arm can read.** Point a register at a known buffer and
store everything:

```
E_STR(R6, R0, 0)
E_STR(R6, R1, 1)
E_STR(R6, R2, 2)
...
```

Then read the buffer from Arm code. Crude and completely effective.

**Use the hardware breakpoint as a callout.** Set `EZHB_BREAK_ADDR` to an [[E_NOP]] you
inserted for the purpose and `EZHB_BREAK_VECT` to a dump routine; the routine returns by
reading the break address back and adding 4:

```
E_PUSH(R4)                   ; handler at EZHB_BREAK_VECT
E_PUSH(R5)
E_PER_READ(R0, EZHBREAKADDR)
E_ADD_IMM(R0, R0, 4)
E_GOTO_REG(R0)               ; resume after the break site
```

Point `EZHB_BREAK_ADDR` at a real instruction and you have silently deleted it — the
substitution replaces, it does not precede. See
[breakpoint support](architecture.html#breakpoint).

## Shift-and-accumulate {#algorithmic}

The algorithmic conditions exist for algorithms where a shift happens every iteration and
an ALU operation happens only on some of them. Binary multiplication is the archetype, and
the entire 16×16 core is one instruction in a tight loop:

```
E_LOAD_IMM(R3, 15)                     ; 16 iterations
E_ADD_IMM(R4, PC, 2*4)
E_TIGHT_LOOP(R4, R3)
E_COND_LSLS(SPO, R0, R0, 16)           ; one-shot: position the multiplicand
E_COND_LSL_ADDS(SPO, R0, R1, R0, 1)    ; the whole multiply
```

`SPO` cancels the fused ALU stage when the algorithmic-positive flag is set — the shift
always happens, the add happens conditionally. [The flags section](architecture.html#flags)
covers the semantics, including which operand survives cancellation and the fact that an
`N` inversion is *not* cancelled.

This is the rarest pattern in the corpus: one program uses it, and that program is a
feature demonstration rather than an application. If you are doing CRC, a filter, or
fixed-point multiply on EZH, you are close to the edge of what has been tried — the
architecture supports it well, but there is very little prior art to copy.
