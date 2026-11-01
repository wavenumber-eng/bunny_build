+++
type = "doc_chapter"
id = "cookbook"
title = "Cookbook: Patterns and Idioms"
section = 5
status = "draft"
created = "2026-07-25"
+++
# Cookbook: Patterns and Idioms

The [architecture chapter](architecture.html) describes the machine and the
[assembler guide](assembler.html) describes how to write for it. This chapter is the
part you copy shapes from. The small runnable examples stay in the repository; this
chapter explains reusable program structures.

## How to read this chapter {#how-to-read}

Use these snippets as building blocks for timing, capture, and protocol tasks.
Adapt the register allocation, pin assignments, and buffer layout to your application.
The runnable examples in the repository show how to assemble and launch complete programs.

## Choose the program shape {#program-shapes}

Decide this before choosing individual instructions. EZH programs commonly use
one of two shapes.

**Continuous engine.** Boot the program and let EZH own a timing- or event-driven job:
camera capture, key scan, display streaming, bit-banged protocol work. The program waits
on `HOLD`, heartbeat, FIFO state, GPIO, or a tight loop, then keeps moving data until the
Arm gives it a new frame, buffer, or command. The important property is that EZH is the
engine while the work is live; the Arm is not stepping every byte.

**Command / execute / stop.** The Arm prepares a parameter block, boots a bounded program,
the program does the operation, optionally signals the Arm, and parks. This is the
`E_INT_TRIGGER(0)` then `E_END` world. It is the right shape for one-shot transforms,
register chores, diagnostics, and small peripheral commands.

In a multi-app system, the Arm can select an independently assembled program by
offset and boot it. Each program retains its own entry point and parameter layout.

bunny_build's C builder gives you one more lever: if a repeated sequence has a single
intent, make it a pseudo-instruction. That is not a third execution shape; it is how you
name the boundary between pattern and boilerplate.

## The boot preamble {#boot-preamble}

Initialize the parameter-block pointer and stack before using either:

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

When a program finishes, signal the Arm and park without consuming bus bandwidth:

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
peripheral's interrupt instead, pass its mask. `E_INT_TRIGGER(0xFFFFFF)` selects
all hijack channels.

> Order matters. Park first and the interrupt never issues, because the core has stopped.

## Pseudo-instructions are pattern boundaries {#pseudo-instructions}

EZH pseudo-instructions are ordinary C builder helpers that emit more than one hardware
instruction. That matters because the builder runs in your program: when a repeated
sequence has one intent, you can give it one name instead of copying the sequence through
every app.

`E_END` is the canonical example. The hardware has [[E_HOLD]], `CFS`, `CFM`, and
branches; the pattern is "park forever without fetching". Packaging that as a helper is
right because all eight emitted instructions have one semantic job and strict ordering.
`E_LOAD_32IMM` is the other obvious case: a 32-bit constant load is not one hardware
instruction, but it is one programmer-facing operation.

Use this sparingly. A pseudo-instruction should hide boilerplate, not hide control flow.
Document scratch registers, stack requirements, and whether the helper emits labels or
branches. If those rules are surprising, the sequence may deserve to stay visible in the
program that uses it.

## Multi-app dispatch {#multi-app}

One EZH can run several programs selected at run time. Assemble every
program into one shared RAM pool and remember where each lands:

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

## Continuous engines re-boot with fresh parameters {#capture}

A continuous camera engine can restart for each frame: EZH owns the hot path
while a frame is live, then the Arm starts the next frame with fresh parameters.

EZH has no persistent descriptor chain. Each boot writes a new parameter-block pointer to
`EZHB_ARM2EZH`, and the program re-reads it from the top — so the natural way to run
repeated work is to re-boot with different parameters rather than to build a descriptor
list once and let hardware walk it.

A per-frame entry point takes the destination buffer and boots the frame program
with the updated parameters:

```c
void camera_prepare_frame(uint16_t *buffer)
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

For key scanning, drive several slices from GPIO through the INPUTMUX and let
the vectored hold do the debounce-free dispatch — the whole point being that there is no
interrupt entry cost to pay per key.

## Deterministic timing {#timing}

Two mechanisms, and they compose. `E_WAIT_FOR_BEAT` aligns one instruction to the
heartbeat; `E_SYNCH_ALL_TO_BEAT(1)` puts *every* instruction on the beat.

A clock generator needs three instructions inside a tight loop:

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

## Streaming DSP loops {#streaming-dsp}

A streaming DSP program is still a continuous engine, but the useful pattern is different
from a copy loop. The fast path must accept every input event, while the slow path spreads
decimated work across the interval before the next output sample.

For PDM-to-PCM conversion, each raw PDM bit waits on
the Boolean detector, folds the bit into a four-stage integrator, and then spends the
available slack on one or two pieces of slower work: comb differentiators, pre-envelope
filters, absolute value, fast/slow envelope trackers, and largest-difference tracking.
The comb/filter work happens once per output sample, but it is interleaved through the
oversampling window rather than placed in one burst at the end.

```
E_HOLD()                         ; next clock/data event
; update the integrator chain for this raw bit
; do one slice of decimated-side work while there is slack
E_HOLD()
; update the next raw bit
; do the next slice of decimated-side work
```

The loop itself is kept out of the hot path. Initialise the breakpoint register to the
loop end and the breakpoint vector to the loop start; when execution reaches the end
marker, breakpoint substitution sends EZH back to the first instruction of the loop:

```
E_PER_WRITE(R1, EZHBREAKADDR)    ; loop end marker
E_PER_WRITE(R0, EZHBREAKVECT)    ; loop restart address
```

The output buffer is another reusable trick. Point `SP` at an aligned ring, write with
post-increment, test the low address bits to notify the Arm at a half-buffer boundary,
then clear the wrap bit so the stack pointer circles:

```
E_STR_POST(SP, R4, 1)            ; store output sample and advance
E_AND_IMMS(GPI, SP, half_buffer_mask)
; if ZE, notify the Arm with SP so it can identify the filled half
E_BCLR_IMM(SP, SP, wrap_bit)
```

This is not a generic "put DSP on EZH" recipe. It works because the algorithm has a
strict input cadence, a small fixed state vector, and a slow side of the calculation that
can be scheduled in pieces. That combination is what to look for in decimators, simple
filters, and edge/envelope detectors.

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
the swap fuses into an instruction that was happening anyway. A display stream can use this sequence: load a batch, convert in flight, write to a
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

## Use branch shadows deliberately {#branch-shadow}

Scheduled branches are not just a faster way to jump. They give you two instruction
slots that execute while the branch target is being fetched. The rare but useful pattern
is to put mutually exclusive conditional work there:

```
E_COND_GOTO(UNS, "shadow_done")  ; scheduled: the next two instructions execute
E_COND_PUSH(EX, R0)              ; if the external flag is set
E_COND_PUSH(NEX, R1)             ; if the external flag is clear
E_PUSH(R2)                       ; not in the shadow; never reached by this branch
E_LABEL("shadow_done")
```

The scheduled branch is unconditional, but the two shadow instructions still keep their
own conditions. Exactly one push happens, and it costs no extra branch. That is the kind
of pattern scheduled branches are for: useful work in cycles that an ordinary branch
would throw away.

EZH can set up the condition it later tests: read-modify-write the control register with the `0xC0DE` key and change `EXF`, then
use `EX`/`NEX` in the branch shadow. That is legal, but it is shared state with the Arm.
Use it when the program and Arm code have an explicit ownership rule.

## Protocol emulation {#protocol}

An SPI PSRAM driver can run entirely on EZH. The same structure works for
bit-banged or FIFO-driven protocols:

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

Use memory dumps and the hardware breakpoint to inspect EZH execution.

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

Validate the operand order, signedness, and result width for your algorithm before
using this pattern for CRCs, filters, or fixed-point multiplication.
