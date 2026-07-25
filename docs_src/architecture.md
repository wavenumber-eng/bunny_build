+++
type = "doc_chapter"
id = "architecture"
title = "EZH Architecture B — Architecture Overview"
section = 2
status = "draft"
created = "2026-07-25"

# Provenance is carried here, not in the body, so that non-public source ids can
# never reach rendered output. The generator renders citations only for sources
# flagged public = true in isa/ezh_b/arch.toml (an14650, bunny_build); non-public
# ids (spec_b_06, fsl_header, sv_tb) inform the prose and are recorded for the
# creator review pass only. See docs/design/isa-doc-generator.html, "Provenance
# rendering", and the plan rule "synthesize, don't copy".

[[provenance]]
section = "what-ezh-is"
sources = ["an14650", "spec_b_06"]
detail = "AN14650 §1, §1.2, §1.3; Arch B spec §3"

[[provenance]]
section = "system-context"
sources = ["an14650", "sv_tb"]
detail = "AN14650 §2.1, §3.1, §4.1.6, §4.1.7, §4.1.8. sv_tb ADVISORY: the model constructs its PC manager at boot_addr + 4, so the word at boot_addr is never executed - corroborates the deck's first-instruction-discarded claim"

[[provenance]]
section = "dual-bus"
sources = ["an14650", "spec_b_06"]
detail = "AN14650 §4.2.1; Arch B spec §4.1"

[[provenance]]
section = "pipeline"
sources = ["an14650", "spec_b_06"]
detail = "AN14650 §4.2.15, §4.2.10; Arch B spec §4.2"

[[provenance]]
section = "two-ahead"
sources = ["an14650", "spec_b_06", "bunny_build", "sv_tb"]
detail = "AN14650 §4.2.15.1 note, §4.2.10, §4.2.8; Arch B spec §4.2, §4.7, §4.13; PC offsets re-derived from the worked examples. sv_tb ADVISORY: ezh_pc_manager seeds the fetch queue boot+0/+4/+8, ticks by +4, executes pc[$-2] and returns pc[$] on a PC read (PC = exec+8); scheduled branch reassigns pc[$] with no cancel bits while an ordinary branch sets cancel on pc[$-1]/pc[$-2]; GOTO with the L bit writes RA as PC-4 ordinary, PC+4 scheduled"

[[provenance]]
section = "dfetch"
sources = ["an14650", "spec_b_06"]
detail = "AN14650 §4.2.10 performance note; Arch B spec §4.3"

[[provenance]]
section = "registers"
sources = ["an14650", "bunny_build"]
detail = "AN14650 §3.2; register encodings from isa/ezh_b/arch.toml"

[[provenance]]
section = "flags"
sources = ["an14650", "spec_b_06"]
detail = "AN14650 §4.2.5, §4.2.5.1, §4.2.5.2; Arch B spec §4.5"

[[provenance]]
section = "alu-shifter"
sources = ["an14650", "spec_b_06"]
detail = "AN14650 §4.2.2, §4.2.3, §4.2.4; Arch B spec §4.8"

[[provenance]]
section = "boolean-detection"
sources = ["an14650", "spec_b_06"]
detail = "AN14650 §3.2, §4.2.8; Arch B spec §4.6, §4.7"

[[provenance]]
section = "pending-trap"
sources = ["an14650"]
detail = "AN14650 §3.1 (EZHB_PENDTRAP), §4.2.9"

[[provenance]]
section = "gpio"
sources = ["an14650", "spec_b_06"]
detail = "AN14650 §3.2, §4.2.6, §4.1.7; Arch B spec §4.10"

[[provenance]]
section = "heartbeat"
sources = ["an14650", "spec_b_06"]
detail = "AN14650 §4.2.7; Arch B spec §4.11"

[[provenance]]
section = "supervisor"
sources = ["an14650", "spec_b_06"]
detail = "AN14650 §4.2.10; Arch B spec §4.12"

[[provenance]]
section = "stack-ra"
sources = ["an14650", "spec_b_06", "sv_tb"]
detail = "AN14650 §4.2.11; Arch B spec §4.9 (incl. the 'return with offset' headline feature). sv_tb ADVISORY: e_goto writes RA only when instruction bit 10 is set, as PC-4 for an ordinary branch and PC+4 for a scheduled one - i.e. the return address skips the two delay slots"

[[provenance]]
section = "breakpoint"
sources = ["an14650", "spec_b_06", "sv_tb"]
detail = "AN14650 §4.2.12; Arch B spec §4.13. sv_tb ADVISORY: ezh_pc_manager.tick() evaluates the tight-loop address swap BEFORE the breakpoint substitution, with an explicit comment that a tight-loop swap means the breakpoint need not trigger"

[[provenance]]
section = "emergency"
sources = ["an14650", "spec_b_06", "nxp_chipdata"]
detail = "AN14650 §3.1 (EZHB_EMER_SEL), §4.1.4, §4.2.13; Arch B spec §4.14 (core-level: describes the emergency INPUT, no wrapper registers). nxp_chipdata MCXN947 SMARTDMA0 EMER_SEL: EN[8], RQ[9] - settles the AN's internal contradiction"

[[provenance]]
section = "arm-ezh"
sources = ["an14650", "spec_b_06", "nxp_chipdata"]
detail = "AN14650 §3.1, §4.1.4, §4.1.5, §4.1.9, §4.2.5.2.3, §4.2.14; Arch B spec §4.5. nxp_chipdata MCXN947 SMARTDMA0 register block supplies the official field names (BOOTADR.ADDR[31:2]; CTRL START/EXF/ERRDIS/BUFEN/SYNCEN/WKEY; EMER_SEL EN/RQ; ARM2EZH IE/GP; PENDTRAP STATUS/POL/EN) and the SMARTDMAARCHB_INMUX[n] naming"

[[provenance]]
section = "open-questions"
sources = []
detail = "Derived section: indexes the [[unverified]] entries below, carries no claims of its own"

# Claims that are NOT grounded in a public source. Per the plan's RM-grounding
# rule these ship hedged in the body until a public Reference Manual, a bench
# result (hardware-adjudication), or creator review confirms them.
[[unverified]]
id = "txev-sev"
status = "open"
section = "arm-ezh"
claim = "EZH can observe the Arm TxEV event signal raised by __SEV(), giving an Arm-to-EZH wakeup path"
basis = "internal deck only"
resolve_by = "creator review or per-chip RM"

[[unverified]]
id = "ezh-runs-while-arm-halted"
status = "open"
section = "arm-ezh"
claim = "Once started, EZH keeps executing while the Arm core is halted at a debug breakpoint"
basis = "internal deck only"
resolve_by = "bench (hardware-adjudication)"

[[unverified]]
id = "boot-first-instruction"
status = "corroborated"
section = "system-context"
claim = "The first instruction of an EZH program is discarded for alignment, so programs conventionally open with E_NOP"
basis = "internal deck, plus hardware analysis: the behavioral model seeds its fetch queue at boot_addr + 4, so the word at boot_addr is never executed. Two independent sources now agree; still not in any public source"
resolve_by = "bench (hardware-adjudication)"

[[unverified]]
id = "vector-latency"
status = "open"
section = "boolean-detection"
claim = "Minimum trigger-to-handler latency for a vectored hold"
basis = "spec states a 4-cycle minimum for the accelerated case; AN14650 states roughly six cycles from trigger to hold release - the two count different intervals"
resolve_by = "bench (hardware-adjudication)"

[[unverified]]
id = "emergency-enable-polarity"
status = "resolved"
section = "emergency"
claim = "Polarity of EZHB_EMER_SEL bit 8 (software-emergency enable)"
basis = "AN14650's register table and its own EZH_SetEmergencyMode listing disagreed. Resolved via nxp_chipdata (MCXN947): the field is named EN, with RQ at bit 9 - so the register table is right and the code listing is inverted. Residual uncertainty is small: the vendor data carries no enumerated values for this field, so active-high is inferred from NXP's naming convention, which is self-evidencing in the same register block (negative-sense bits are named negatively - ERRDIS - while EN/START/RQ/BUFEN/SYNCEN are positive)"
resolve_by = "bench confirmation only; no longer blocking"

[[unverified]]
id = "heartbeat-period-off-by-one"
status = "open"
section = "heartbeat"
claim = "Whether the heartbeat period is `reload` or `reload + 1` core cycles"
basis = "The documented reload-0 behaviour (a beat every cycle) implies period = reload + 1, which puts the published 7500-at-150-MHz example at 19,997 Hz rather than the 20,000 Hz it is quoted as. Either the examples round, or the period is `reload` with 0 special-cased. No source states a formula; the chapter gives the 1 + count rule for tight loops and nothing equivalent here"
resolve_by = "bench (measure a beat directly); 0.013% error, so it matters only for long-running bit-banged protocols where it accumulates"

[[unverified]]
id = "rshift-ge-32"
status = "corroborated"
section = "alu-shifter"
claim = "Barrel-shifter results and carry for register-sourced shift amounts of 32 and above"
basis = "Spec section 4.8 and AN14650 Table 6 agree row for row, and hardware analysis models the same mod-32 rotate and shift-out carry rules. No source conflict - simply never confirmed on silicon, and the spec calls the >= 32 region out as a defined-behaviour table rather than derived behaviour"
resolve_by = "bench (hardware-adjudication, rshift >= 32 item)"

[[unverified]]
id = "int-trigger-zero"
status = "resolved"
section = "arm-ezh"
claim = "Behaviour of E_INT_TRIGGER(0)"
basis = "AN14650 4.2.14 claims the parameter must be greater than 0. Contradicted by the spec's E_INT_TRIGGER section, which states the opcode triggers the common interrupt output AS WELL AS any of the 24 channels, that the immediate only chooses the channels ('common interrupt always triggered'), and lists Restrictions: None. AN14650 5.21 agrees with the spec, as does the training deck and the whole sample corpus. So E_INT_TRIGGER(0) fires the common interrupt and no hijack channels - exactly the end-of-program signal. AN 4.2.14 is advice for the hijack case, not a constraint"
resolve_by = "closed on the 2026-07-25 authority ranking (spec over AN); bench confirmation optional. Unblocks the assembler guide's park-pattern section"

[[unverified]]
id = "pc-read-offset"
status = "corroborated"
section = "two-ahead"
claim = "A PC source read yields the current instruction address + 8 bytes (two 32-bit instruction words)"
basis = "AN14650 states the PC is two instructions ahead and every worked example is consistent with +8 bytes, but no source states the constant outright. Corroborated by hardware analysis: the behavioral model keeps a fetch queue stepping by 4, executes at pc[$-2], and returns pc[$] for a PC register read - i.e. executing address + 8"
resolve_by = "bench (hardware-adjudication, PC-read item) - now corroborated by an executable model, so confirmation rather than investigation"
+++

# Architecture Overview

EZH — "EZ Handler", shipped on more recent parts under the name **SmartDMA** — is a
32-bit coprocessor that sits beside the Arm core and takes over the work Arm cores are
bad at: reacting to an I/O edge in zero cycles, running the same tight loop a million
times, streaming data through a format conversion on its way to a peripheral.

> **EZH and SmartDMA are the same thing.** *SmartDMA* is the name NXP uses in official
> documentation, and it is the name in the silicon: the peripheral appears as `SMARTDMA0`,
> its trigger mux as `SMARTDMAARCHB_INMUX[n]`, its interrupt as `SMARTDMA_IRQn`, its pin
> function as `SMARTDMA_PIO`. *EZH* ("EZ Handler") is the original architecture name, and
> it is the one that survives in the things a programmer actually touches — the `E_*`
> instruction mnemonics, the `fsl_ezh_*` headers, the `EZHB_*` control registers.
>
> This documentation uses **EZH** when discussing the architecture and instruction set,
> and **SmartDMA** when discussing a specific part, because that is what a Reference
> Manual, an SDK header, or a config tool will call it. If you arrived here searching for
> one name, everything about the other applies.

This chapter describes what the machine *is*. The [instruction reference](instructions.html)
describes what each opcode *does*, down to the bit; the [assembler guide](assembler.html)
describes how you write programs for it with bunny_build. Everything here is grounded in
the public SmartDMA Cookbook (AN14650) and the original Architecture B specification;
where the two disagree, or where nothing public settles a question, this chapter says so
in place rather than guessing.

## What EZH is {#what-ezh-is}

EZH is not a general-purpose CPU and is not trying to be one. It is a *cooperation* core:
the Arm keeps the application, and EZH takes the tedious, repetitive, latency-critical
edges of it. Its design targets are:

- **State machine control** — hardware-assisted dispatch on I/O events.
- **Boolean detection** — combinational monitoring of up to eight event sources with no
  interrupt entry cost at all.
- **DMA emulation, and better** — plain DMA moves bytes; EZH can *transform* them in
  flight (the canonical example is RGB565 → RGB888 on the way to a display interface).
- **Protocol emulation over I/O** — USART, I²C, SPI, ISO7816, PWM, I3C.
- **Shift-based algorithms** — CRC, SHA, multiplication, decimation filters.
- **Streaming and general I/O handling** — register-mapped GPIO, single-cycle.
- **Interrupt load reduction** — EZH services the interrupt first and only escalates to
  the Arm when the Arm is actually needed.

The structural advantages over a small Arm core (the comparison AN14650 draws is against
a Cortex-M0+) come from four decisions:

| | EZH | Cortex-M0+ |
|---|---|---|
| Architecture | Modified Harvard, dual AHB (instruction + data) | Von Neumann, single system bus |
| Event latency | Bit-slice detection, no cycle penalty | ISR entry ~15 cycles at zero wait states |
| I/O access | Register-mapped (`GPO`/`GPI`/`GPD`) with dedicated opcodes | Memory-mapped over AHB, one extra cycle per access |
| Loops | Zero-overhead hardware loop | Decrement-compare-branch, one cycle penalty |

Add to that a 32-bit instruction word — far more room than 16-bit Thumb — which is what
buys conditional execution on nearly every opcode, fused pre/post barrel shifts, and
inversion, all in a single cycle.

## EZH in the system {#system-context}

EZH is an AHB **controller** (bus master), not a peripheral slave, on two independent
ports. Its control registers, in contrast, are slaves on the APB, at a per-part base
address:

| Part | EZH control register base |
|---|---|
| LPC5410x | `0x4004_C000` |
| LPC54114 / LPC51U68 | `0x4001_D000` |
| LPC55(S)6x / LPC55(S)2x / LPC55(S)3x | `0x4001_D000` |
| i.MX RT500 | `0x4002_7000` |
| MCXNx4x / MCXN23x | `0x4003_3000` |

> **That table is the published list, not the current one.** It reproduces AN14650's, which
> predates a good part of the portfolio — the MCXA line alone adds parts across the 1xx
> through 5xx series, and presence is not uniform even within a series (MCXA173/174/176
> carry the block; MCXA156 does not). On TrustZone parts each entry is also really a pair:
> MCXN947's is `0x5003_3000` secure, `0x4003_3000` non-secure. The
> [platform guide](platform.html) carries the derived, complete list.

The [platform guide](platform.html) carries the full per-part picture — pin mux options,
IRQ numbers, INPUTMUX trigger maps. Four pieces of system plumbing must be right before
any EZH program runs:

**Clock and reset.** Both live in the system control module. The EZH clock must be
enabled before you touch an EZH control register, let alone start the core.

**Pin mux.** EZH drives up to 32 I/O pins directly, when those pins select the EZH
alternate function: FUNC 4 on LPC5410x/LPC5411x/LPC51U68, FUNC 15 on
LPC55(S)3x/LPC55(S)6x/i.MX RT500, FUNC 7 on MCXNx4x.

**Trigger mux.** The eight Boolean bit-slice inputs are wired through the system
INPUTMUX (`EZH_INPUTMUX[0..7]`), exactly like DMA triggers. Anything the INPUTMUX can
reach — GPIO pins, peripheral interrupt lines, timer match events — can drive a bit-slice.

**Bus priority.** EZH shares the AHB matrix with the Arm core. At equal priority, EZH
memory accesses can be starved; raising the EZH instruction and data ports in the
`AHBMATPRIO` register of SYSCON/SYSCTL is the standard fix and is what the reference
boot sequence does.

Starting the core is then: write the (4-byte aligned) program address to `EZHB_BOOT`,
write the parameter-block pointer to `EZHB_ARM2EZH`, and set the ignition bit in
`EZHB_CTRL`. The full register block is in [Arm ↔ EZH interaction](#arm-ezh).

### The word at the boot address is not executed

**Begin every EZH program with an [[E_NOP]].** The instruction word sitting at
`EZHB_BOOT` is discarded — execution effectively begins one word later. This applies at
*boot* only; code reached by a branch, a vector dispatch, or a breakpoint substitution
loses nothing.

The evidence is consistent across four independent directions:

- Training material states it directly, attributing it to alignment.
- Hardware analysis agrees: the behavioural model seeds its fetch queue at
  `boot_addr + 4`, so the word at `boot_addr` is never fetched for execution.
- **111 of 114** EZH programs in the historical sample corpus open with [[E_NOP]] —
  either literally or through a prologue macro that begins with one.
- The exceptions prove the rule rather than breaking it. The two programs that skip the
  leading [[E_NOP]] are not boot entries: one is a breakpoint *vector* target (reached by
  address substitution) and one is dispatched to. AN14650 shows both halves of this pair
  in a single example — its boot-entry routine opens with [[E_NOP]], its breakpoint
  handler opens straight into [[E_PUSH]].
- One sample settles it outright: it places a **data constant** in the boot word (a
  buffer pointer, via a `DCD` directive) and branches from the second word. Executing
  that word would run a RAM address as an instruction. The program works.

That last idiom is worth knowing: the discarded word is free real estate. Most code
spends it on an [[E_NOP]]; the boot word can equally hold a constant the program is going
to want anyway.

> Still formally on the bench list — no public source states it, and none of the above is
> silicon. But the convention is safe regardless: an opening [[E_NOP]] costs nothing if
> the word turns out to be executed after all.

## Dual-bus architecture {#dual-bus}

EZH has two independent AHB controller interfaces:

- **Inst-AHB** — fetches opcodes. Nothing else.
- **Data-AHB** — everything else: literals, memory, peripherals, anywhere on the chip.

The interesting decision is that *data literals come over the data bus*, where an Arm core
would fetch them over the instruction bus from a literal pool. Three things fall out of
that, and all three shape how you write EZH code:

1. **The program counter mechanism stays trivial.** Because the instruction bus only ever
   fetches instructions, sequentially, it is *always* exactly two instructions ahead of
   the decode/execute stage. No literal pool perturbs it, so the relationship never has to
   be recomputed.
2. **The pipeline does not have to be flushed on a branch.** Since the correlation between
   fetch and decode is fixed and known, the hardware knows exactly how many extra opcodes
   it fetched, which makes it *safe to let them execute* instead of discarding them. This
   is what the [scheduled branch](#pipeline) is, and it is a direct consequence of putting
   literals on the data bus.
3. **Data accesses can be scheduled independently.** Every read and write goes through one
   unit (DFETCH), which can queue work whose address, offset, or data has not arrived yet
   — so the core keeps executing while memory traffic drains. See
   [data access acceleration](#dfetch).

## Instruction pipeline and branching {#pipeline}

Instruction fetch is an AHB read, so it carries the two-cycle address/data latency AHB
imposes. Decode and execute happen together in a single cycle, starting from the clock
edge that registers the read data. In steady-state linear execution that pipelining is
invisible: one instruction retires per cycle.

It becomes visible at branches, and EZH offers three branch mechanisms with three
different costs.

### Ordinary branch — 3 cycles

When a branch executes, the instruction bus has already fetched the next two instructions.
An ordinary branch discards them and refills from the new address:

```
I-AHB address    A0    A1    A2    Ax    Ax+1  Ax+2
I-AHB data             D0    D1    D2    Dx    Dx+1
Executing                    E0    ---   ---   Ex
                             ^branch  two flushed cycles
```

One cycle for the branch itself plus two dead cycles while the pipeline refills: **three
cycles**, and the two already-fetched instructions (`D1`, `D2`) are thrown away.

### Scheduled branch — 1 cycle

A scheduled branch reclaims those two cycles by *not* flushing. The two instructions
already in flight execute normally while the pipeline refills from the branch target:

```
I-AHB address    A0    A1    A2    Ax    Ax+1  Ax+2
I-AHB data             D0    D1    D2    Dx    Dx+1
Executing                    E0    E1    E2    Ex
                             ^branch  both execute
```

The branch costs **one cycle**. The price is that the two instructions after the branch
still run — that is not a hazard to be worked around, it is the feature. They are the
*branch delay slots*, and idiomatic EZH code fills them with useful work.

There are three ways to request one:

- **[[E_GOTO]] under the `UNS` condition** — unconditionally scheduled.
- **[[E_GOTO]] under the `NZS` condition** — scheduled if the `NZ` flag is set.
- **Any flag-setting ALU operation whose destination is `PC`.** Writing `PC` branches;
  writing `PC` *with* the `S` (set-flags) modifier makes it scheduled. The `S` bit is
  reinterpreted here — no flags are set, because the destination is `PC`.

```
E_COND_GOTO(UNS, target)   ; scheduled: the next two instructions execute
E_PUSH(R0)                 ; executed
E_PUSH(R1)                 ; executed
E_PUSH(R2)                 ; NOT executed - beyond the two-instruction shadow

E_GOTO(target2)            ; ordinary: the next two are flushed
E_PUSH(R3)                 ; NOT executed
```

The `UNS` and `NZS` condition codes are the same encodings as the `SPO` and `SNE`
[algorithmic flags](#flags) — the meaning depends on the opcode they qualify.

### Tight loop — 0 cycles

The third mechanism removes the branch entirely. [[E_TIGHT_LOOP]] hands the loop bounds
and iteration count to the [execution supervisor](#supervisor), which rewrites the fetch
address in hardware:

```
I-AHB address    A0    A1    A2    A0    A1    A2
I-AHB data             D0    D1    D2    D0    D1
Executing                    E0    E1    E2    E0
                                               ^no gap
```

**Zero cycles.** The loop repeats seamlessly with no branch instruction and no bubble.

## Living with a pipeline that runs two ahead {#two-ahead}

The two-instruction lookahead is not an implementation detail you can ignore — it is
visible in the programmer's model in at least eight places. Collected here, because
every one of them is a place where otherwise-correct code goes wrong.

**1. Reading `PC` gives you the current instruction's address + 8 bytes.** Instructions
are 32 bits, so +8 bytes is exactly the two instruction words the pipeline is ahead by.
`PC` is an ordinary readable source register and what you read is the fetch position, so
all PC-relative address math carries that two-word bias:

These two are *alternatives* at the same address, not a sequence — each shows what a
different immediate yields from the same starting point:

```
E_ADD_IMM(R4, PC, -4)   ; R4 = address of the NEXT instruction
E_ADD_IMM(R4, PC, 0)    ; R4 = address of the one after that
```

> **Mind the units — they are not the same across instructions.** The ALU immediate
> forms (`imm12s`: `E_ADD_IMM`, `E_SUB_IMM`, …) take a **raw byte** offset, so one
> instruction is `4`. The load/store offset (`offset8s`: [[E_LDR]], [[E_STR]] and
> relatives) is **scaled by access size**, so for a word access one instruction is `1`.
> The two idioms below step the same distance:
>
> ```
> E_ADD_IMM(R4, PC, -4)   ; -4 BYTES  = back one instruction
> E_LDR(PC, R4, 1)        ;  1 WORD   = forward one instruction
> ```
>
> This is why label tables are indexed `0, 1, 2, …` with [[E_LDR]] but set up with a
> byte-denominated `E_ADD_IMM(Rn, PC, -4)`. Older listings make the distinction visible
> by spelling the byte constant as a product — `E_ADD_IMM(R4, PC, 2*4)` means two
> instructions.

This is exactly why the standard label-table idiom opens with `E_ADD_IMM(Rn, PC, -4)`
immediately followed by the table: `-4` bytes lands on the first table entry. Every worked
example in the public and internal sources is consistent with a `+8`-byte read, and
AN14650 states plainly that the PC is two instructions ahead — but no source states the
constant outright, so it is on the bench list for confirmation.

**2. Writing `PC` branches; writing it with `S` branches *scheduled*.** The set-flags bit
is reinterpreted rather than setting flags. This makes computed branches cheap:
`E_ADD_IMMS(PC, PC, 8)` schedules a branch four instructions ahead of the current one
(`PC` already reads +8 bytes, and the immediate adds 8 more, so +16 bytes = four words).

**3. An ordinary branch throws away two fetched instructions; a scheduled branch runs
them.** Covered above — this *is* the mechanism.

**4. A vectored hold flushes two instructions unless you accelerate it.**
[[E_VECTORED_HOLD]] discards the two instructions after it, which is pure latency in an
event handler. [[E_ACC_VECTORED_HOLD]] takes a mask of which vectors should keep them, so
for the accelerated events those two instructions execute while the branch to the handler
is still in flight. See [Boolean detection](#boolean-detection).

**5. Large vector table entries are four instructions because of this.** A scheduled
branch plus its two unflushed instructions is three; the fourth slot is what lets an entry
hold a full single-cycle branch to the rest of a longer handler.

**6. The instruction after [[E_TIGHT_LOOP]] executes exactly once.** The loop body starts
*two* instructions after the [[E_TIGHT_LOOP]], because of the lookahead. That one-shot
slot is genuinely useful — it is where loop-invariant setup goes:

```
E_LOAD_IMM(R0, 15)          ; 15 -> 16 total iterations
E_ADD_IMM(R1, PC, 8)        ; R1 = first instruction PAST the loop body
E_TIGHT_LOOP(R1, R0)        ; arm the supervisor
E_BSET_IMM(GPD, GPD, 0)     ; runs ONCE, on loop entry
E_BTOG_IMM(GPO, GPO, 0)     ; loop body: runs 16 times
```

Note both pipeline effects in one snippet. The end-address register is computed with
`E_ADD_IMM(R1, PC, 8)`: `PC` reads +8 bytes from that instruction and the immediate adds
8 more, so `R1` lands **four instructions further on** — which, counting from the
`E_ADD_IMM`, is the instruction immediately after the one-instruction body. That is what
the supervisor wants: the first address *past* the loop. And the instruction between
[[E_TIGHT_LOOP]] and the body is the one-shot.

**7. The captured return address depends on whether the branch was scheduled.** When a
branch saves `RA`, the saved value is *not* simply "the next instruction". For an ordinary
branch `RA` is the following instruction; for a **scheduled** branch `RA` is four bytes
further on — past the two delay-slot instructions. It has to be: returning to the
instruction immediately after a scheduled branch would re-execute the two instructions
that already ran in the shadow. See [Stack and return address](#stack-ra).

**8. Breakpoints inside a branch shadow are not reconstructable.** If you set a breakpoint
on one of the two instructions following a scheduled branch, the breakpoint fires
correctly, but returning to it re-enters the shadow with the pending branch already lost.
See [Breakpoint support](#breakpoint).

## Data access acceleration {#dfetch}

EZH treats its register file as a cache in front of the data bus. The DFETCH unit holds
one posted transaction, so a load or store does not stall the core: execution continues
past it while the access drains.

DFETCH will queue **incomplete** requests. A read whose address or offset is itself still
in flight queues successfully; a write whose data has not yet landed in the source register
queues successfully. Returning read data is forwarded straight into the queue at the same
time as it is written back to the register, so a dependent queued access does not have to
wait for the register write to become visible. DFETCH also carries its own adder, so
address-plus-offset is computed without occupying the main ALU.

Execution stalls in exactly two cases:

1. An instruction **reads** a register whose data has not come back yet.
2. An instruction **writes** a register that is the destination of an outstanding read.

The second rule exists for determinism, not correctness of the read: without it, a late
read return could overwrite a value written by a later instruction. Blocking makes
ordering predictable rather than timing-dependent.

The practical consequence is that load-use distance matters a great deal. Batch the loads,
then consume them:

```
; drains without stalling
E_LDR_POST(R2, R0, 1)
E_LDR_POST(R3, R0, 1)
E_LDR_POST(R4, R0, 1)
E_LDR_POST(R5, R0, 1)
E_FEND_LSR(R2, R2, 0)
E_PER_WRITE(R2, 0x32200)
E_FEND_LSR(R3, R3, 0)
E_PER_WRITE(R3, 0x32204)
...

; stalls on every load: R2 is consumed immediately
E_LDR_POST(R2, R0, 1)
E_FEND_LSR(R2, R2, 0)
E_PER_WRITE(R2, 0x32200)
E_LDR_POST(R3, R0, 1)
...
```

Both sequences are correct. The first one is meaningfully faster, and the difference is
entirely in the scheduling.

## Register file {#registers}

Sixteen 32-bit registers, addressed by a 4-bit field. There is no separate "special
register" access path — `PC`, `SP`, `GPO` and the rest are operands to ordinary
instructions, which is where a lot of EZH's density comes from.

| Reg | Enc | Access | Purpose |
|---|---|---|---|
| `R0`–`R7` | `0x0`–`0x7` | RW | General purpose |
| `GPO` | `0x8` | RW | GPIO output: bit *n* drives EZH pin *n* (1 = high) |
| `GPD` | `0x9` | RW | GPIO direction: bit *n*, 1 = output, 0 = input |
| `CFS` | `0xa` | RW | Boolean detector **source** config: 8×3-bit slice input selects, plus live slice-input status |
| `CFM` | `0xb` | RW | Boolean detector **event** config: 8×3-bit slice event selects, plus 8 OR-enable bits |
| `SP` | `0xc` | RW | Stack pointer |
| `PC` | `0xd` | RW | Program counter — reads two instructions ahead, writes branch |
| `GPI` | `0xe` | RO | GPIO input: bit *n* reflects EZH pin *n*. Also the **discard destination** |
| `RA` | `0xf` | RW | Return address |

Three notes that matter in practice:

**`GPI` is the bit bucket.** EZH has no compare or test instruction, because it does not
need one: any flag-setting operation with `GPI` as its destination computes, sets flags,
and discards the result. `E_BTST_IMMS(GPI, GPI, 3)` is a bit test; a subtract with `S` into
`GPI` is a compare. This is the CMP/TST idiom, and it is why the instruction set looks like
it is missing something it is not.

**Unused I/O registers are free scratch.** If no pin is muxed to EZH, `GPO` and `GPD` hold
no meaning and are usable as two extra general-purpose registers. Likewise `CFM`, `CFS` and
`GPI` when the Boolean detector is unused. On a register-starved machine this is not a
curiosity — it is a routine technique.

**`SP` must be initialised even if you never push.** This is stated flatly by the sources
and is worth respecting; the reference boot sequence loads it from the Arm-supplied
parameter block as its first real act.

## Flags and conditional execution {#flags}

Almost every EZH instruction can be made conditional. The condition field selects one of
sixteen codes, drawn from three quite different pools.

### ALU flags

| Flag | Arm equivalent | Meaning |
|---|---|---|
| `EU` | (none) | Execute unconditionally |
| `ZE` | `EQ` | Result zero |
| `NZ` | `NE` | Result non-zero |
| `PO` | `PL`/`GE` | Positive (result ≥ 0) |
| `NE` | `MI` | Negative (result < 0) |
| `AZ` | `GT` | Above zero (result > 0) |
| `ZB` | `LE` | Zero or below (result ≤ 0) |
| `CA` | `CS` | Carry set |
| `NC` | `CC` | Carry not set |
| `CZ` | (none) | Carry set **and** zero |

```
E_ADDS(R1, R2, R3)        ; R1 = R2 + R3, set flags
E_COND_LDR(ZE, R1, R2)    ; if zero, load from [R2]
E_COND_LDR(NZ, R1, R3)    ; if non-zero, load from [R3]
E_COND_GOTO(AZ, start)    ; if above zero, branch back
```

Three rules govern when flags move:

- **Flags only update on an `S`-suffixed instruction.** Everything else leaves them alone,
  which means flag state survives across branches, holds, and data accesses. You can set
  flags, do a load, and branch on the flags afterwards.
- **Carry moves only for operations that can carry.** `ADD`, `SUB`, `ADC`, `SBC` and the
  shift/rotate stages affect it. A logical operation with `S` — `E_ORS`, `E_ANDS` — updates
  zero and negative but leaves carry untouched.
- **A set of instructions cannot set flags at all**, regardless: every data-bus read or
  write ([[E_LDR]], [[E_STR]], [[E_PER_READ]], [[E_PER_WRITE]] and their relatives), plus
  [[E_NOP]], [[E_INT_TRIGGER]], [[E_GOTO]], [[E_GOSUB]], [[E_MODIFY_GPO_BYTE]],
  [[E_TIGHT_LOOP]], [[E_HOLD]], [[E_VECTORED_HOLD]], [[E_HEART_RYTHM]],
  [[E_SYNCH_ALL_TO_BEAT]] and [[E_WAIT_FOR_BEAT]].

And the special case worth repeating: **when the destination is `PC`, `S` does not set
flags — it requests a scheduled branch.**

```
E_ORS(R2, R1, R3)          ; OR, store in R2, set flags
E_COND_ORS(PO, PC, R1, R3) ; if PO: OR, then SCHEDULED branch to the result
E_COND_OR(PO, PC, R1, R3)  ; if PO: OR, then ORDINARY branch to the result
```

### Algorithmic flags: `SPO` and `SNE`

`SPO` and `SNE` are shadow copies of `PO` and `NE` with one crucial difference: they only
latch from instructions that were themselves *conditioned* on `SPO` or `SNE`. An ordinary
`S` instruction updates `PO`/`NE` and leaves the algorithmic pair alone. That is what lets
you interleave unrelated flag-setting work into a shift-based algorithm and resume the
algorithm afterwards with its own state intact.

Their effect, when used as a condition on a fused shift + ALU instruction, is:

> **The shift always executes. The ALU stage is cancelled when the flag is set.**

So `SPO` means "when the algorithmic-positive flag is set, do the shift *only*"; `SNE` is
the same with the negative sense. This is the "shift-only-when-positive / -negative"
naming, and it is easy to read backwards — AN14650's own summary bullet states it the
other way round, but AN14650's own worked example, the specification, and the encodings in
the ISA database all agree with the rule above:

```
E_LOAD_IMM(R1, 1)
E_LOAD_IMMS(R0, 1)                   ; R0 = 1  (PO=1, SPO=0)
E_COND_LSL_ORS(SPO, R0, R0, R1, 1)   ; SPO==0 -> shift AND OR -> R0 = 3
                                     ; result positive -> SPO latches 1
E_LOAD_IMMS(R0, 1)                   ; R0 = 1  (PO=1, SPO unchanged - not conditioned on SPO)
E_COND_LSL_ORS(SPO, R0, R0, R1, 31)  ; SPO==1 -> shift ONLY  -> R0 = 0x8000_0000
                                     ; result negative -> SPO latches 0
```

The point of all this is shift-based algorithms, where a shift happens every iteration and
an accumulate happens only on some of them. Binary multiplication is the archetype — the
entire 16×16 multiply core is one instruction inside a tight loop:

```
E_LOAD_IMM(R3, 15)                     ; 16 iterations
E_ADD_IMM(R4, PC, 2*4)                 ; end of loop body
E_TIGHT_LOOP(R4, R3)
E_COND_LSLS(SPO, R0, R0, 16)           ; one-shot: position the multiplicand
E_COND_LSL_ADDS(SPO, R0, R1, R0, 1)    ; the whole multiply, x16
```

Two restrictions:

- `SPO`/`SNE` **do not cancel the `N` inversion** if the instruction carries one. In
  `E_COND_ADDN_LSL(SPO, R1, R2, R3, 24)` with `SPO` set, the add is cancelled but the
  inversion is not — the result is `R2` inverted and shifted left by 24. Note which
  operand survives: with the ALU stage cancelled, the value that flows on is the *first*
  source, `R2`, not the addend. (This worked example is the architecture
  specification's own; the ISA database records the cancellation rule but not the
  surviving-operand detail, so treat the latter as spec-grounded rather than
  mechanically verified.)
- They are **not general-purpose conditions.** The architecture names the illegal cases
  rather than the legal ones: using them on [[E_HOLD]], [[E_VECTORED_HOLD]], [[E_MOV]],
  [[E_LOAD_IMM]] or any data-bus access is undefined. They belong to the shift + ALU
  datapath, and the plain arithmetic and logical mnemonics are part of that family —
  `E_COND_ADDS(SPO, ...)` is legal, being a shift-by-zero encoding of the same form. The
  rule to carry is "not on holds, moves, immediate loads, or memory", not "only on
  instructions with a shift in the name".

### Branch-control conditions: `UNS` and `NZS`

`UNS` and `NZS` share encodings with `SPO` and `SNE`. On [[E_GOTO]] they mean "schedule
this branch" — unconditionally, or when `NZ` is set. They are not flags and qualify
nothing else. See [scheduled branch](#pipeline).

### Boolean and external conditions

Four conditions read state from outside the ALU:

- **`BS` / `NBS`** — the Boolean detector's logical combiner output is / is not asserted.
- **`EX` / `NEX`** — the external flag is / is not set. The external flag is
  `EZHB_CTRL` bit 1, writable by either the Arm or EZH itself; EZH has no instruction to
  set or clear it directly, only to observe it. It is the general-purpose "the Arm is
  telling me something" input.

Testing `BS` on an ordinary conditional instruction is a *sampled* test, and it comes with
a hazard. If `CFS` or `CFM` are being loaded from the data bus, nothing stalls the
conditional evaluation — the decision is made when the instruction reaches decode,
possibly with a stale detector configuration. [[E_HOLD]] and [[E_VECTORED_HOLD]] do not
have this problem: they hold `BS` artificially low until any outstanding `CFS`/`CFM` reads
have landed.

There is a second, sharper trap. Conditioning a hold on `BS`:

```
E_COND_VECTORED_HOLD(BS, PC)
```

looks like "take a vector only if one is already pending" — but the flag is sampled at
decode and the hold evaluates at least a cycle later. If the input goes away in between,
the hold has already committed and waits for a vector that is no longer there. Don't do
this unless the detector inputs are known to be stable.

## ALU, barrel shifter, and flip {#alu-shifter}

The ALU does signed 32-bit add and subtract (with and without carry), and `AND`, `OR`,
`XOR`. [[E_ANDOR]] does an AND and an OR against two different registers in one cycle,
which is a single-instruction read-modify-write for "clear these bits, set those".

What makes the instruction set dense is that an ALU operation is only one stage of the
datapath. A single instruction can chain, in one cycle:

```
flip -> pre-shift -> ALU -> post-shift -> invert -> set flags
```

Mnemonics are written **in pipeline order**, which is how you read a name like
`E_SUBN_LSLS`: subtract, invert, shift left, set flags.

### Barrel shifter

`LSL`, `LSR`, `ASR`, `ROR`, by an immediate of 0–31, fused into the same cycle as the ALU
op — either before it (pre-shift, the [[E_LSL]]/[[E_LSR]]/[[E_ASR]]/[[E_ROR]] families) or
after it (post-shift, the `_LSL` suffix on the arithmetic families).

The shift amount can also come from the **bottom byte of a register** (the [[E_RLSL]]
family), which allows amounts beyond 31. Those cases are defined:

| Op | Amount | Result | Carry |
|---|---|---|---|
| `LSL` | 32 | 0 | bit 0 |
| `LSR` | 32 | 0 | 0 |
| `ASR` | 32 | sign bit | sign bit |
| `ROR` | 32 | unchanged | bit 31 |
| `LSL` | ≥ 33 | 0 | 0 |
| `LSR` | ≥ 33 | 0 | 0 |
| `ASR` | ≥ 33 | sign bit | sign bit |
| `ROR` | ≥ 33 | rotate by amount mod 32 | bit (amount mod 32) |

> These ≥ 32 cases are on the bench-verification list. They are specified consistently by
> both the public and internal sources, but have not been confirmed on silicon.

One more shifter quirk, from the condition table: with a register-sourced `LSL` by 1 under
`SPO`/`SNE`, the carry is shifted into the LSB automatically — which is exactly what you
want when tail-chaining a shift across two registers.

### Flip and invert

Before the ALU, an operand can be byte-swapped (`FEND`, endianness flip) or bit-reversed
(`FBIT`). After the ALU, the result can be inverted (`N`).

| Input | `FEND` | `FBIT` | `N` (invert) |
|---|---|---|---|
| `0x01234567` | `0x67452301` | `0xE6A2C480` | `0xFEDCBA98` |
| `0x89ABCDEF` | `0xEFCDAB89` | `0xF7B3D591` | `0x76543210` |

`FEND` is why EZH is good at feeding big-endian peripherals from little-endian memory
without a conversion pass — the swap is free, fused into an instruction that was happening
anyway. `FBIT` serves bit-reversal-heavy algorithms (CRC, FFT addressing).

Flip and invert also compose with immediate loads, which matters because
[[E_LOAD_IMM]] only carries an 11-bit signed immediate. Building a full 32-bit constant
is a load-shift-OR sequence (or a load-invert), typically three or four instructions:

```
E_LOAD_SIMM(R0, 0xFA, 24)   ; R0 = 0xFA000000
E_LOAD_SIMM(R1, 0xC6, 16)   ; R1 = 0x00C60000
E_OR(R0, R0, R1)            ; R0 = 0xFAC60000
E_LOAD_SIMM(R1, 0x88, 8)    ; R1 = 0x00008800
E_OR(CFS, R0, R1)           ; CFS = 0xFAC68800
```

The assembler guide covers the `E_LOAD_32IMM` pseudo-instruction that bunny_build provides
to hide this.

## Boolean detection {#boolean-detection}

This is the part of EZH with no analogue in a conventional core, and it is the reason the
event latency row in the comparison table says "no cycle penalty".

### Bit-slices

Eight identical **bit-slices** each watch one signal and reduce it to a single bit. Each
slice has:

- an **input mux**, selecting which of the eight bit-slice input signals this slice
  watches — configured by `CFS[31:8]`, three bits per slice (slice *n* at bits
  `[3n+10 : 3n+8]`);
- an **event mux**, selecting what counts as an event on that signal — configured by
  `CFM[31:8]`, three bits per slice, same layout;
- two **outputs**: one to the logical combiner, one chained into the next slice. Which one
  is live is set by the slice's **OR-enable** bit in `CFM[7:0]`.

`CFS[7:0]` reads back the live input status of the eight slices.

The eight event-mux settings (the names are the ISA database's):

| Value | Name | Behaviour |
|---|---|---|
| 0 | `BS_1` | Always 1 regardless of input |
| 1 | `BS_RISE` | 1 on a rising edge — **sticky** |
| 2 | `BS_FALL` | 1 on a falling edge — **sticky** |
| 3 | `BS_CHANGE` | 1 on either edge — **sticky** |
| 4 | `BS_SIG` | 1 while the input is high (level) |
| 5 | `BS_SIGN` | 1 while the input is low (level) |
| 6 | `BS_0` | Always 0 — **this is how you disable a slice** |
| 7 | `BS_EVENT` | 1 on either edge — **not sticky**, real-time |

The sticky/real-time distinction is the one to internalise. Settings 1–3 latch: once the
edge fires, the slice stays asserted until you clear it, and **the clear is any write to
`CFM`**. Setting 7 is the same any-edge detection without the latch. Sticky is what you
want for "did this happen while I was busy"; real-time is what you want for "is this
happening now".

Note the corollary: **any write to `CFS` or `CFM` clears the `BS` flag**, sticky slices
included. Reconfiguring the detector is not a free operation.

### The logical combiner: how terms are built

The chain between slices is what turns eight bits into a Boolean expression. Each slice
either routes its result to the logical combiner (OR-enable = 1, ending a term) or ANDs it
into the next slice (OR-enable = 0, continuing a term). The combiner ORs everything it
receives:

```
LC = LC0 | LC1 | LC2 | LC3 | LC4 | LC5 | LC6 | LC7
```

So the OR-enable pattern *is* the expression's shape. With slices 0–7 watching events
A, B, C, D, F, G, H, I and OR-enable set on slices 2, 3, 5 and 7:

```
(A & B & C) | D | (F & G) | (H & I)
```

The first slice's "from previous" input is tied to 1 so that a term can start anywhere,
and the chain terminates at slice 7, whose result always reaches the combiner.

`LC` drives the `BS`/`NBS` conditions and gates the hold instructions.

### Holding

[[E_HOLD]] stops execution until `LC` goes to 1. That is the whole mechanism — no
interrupt, no vector, no save/restore:

```
E_LOAD_IMM(CFS, 0)          ; slice 0 watches input 0
E_LOAD_IMM(CFM, 0x101)      ; slice 0 = rising edge, OR-enabled
...
E_HOLD                      ; park here until it fires
E_PUSH(R0)                  ; resumes here
```

### Vectored holding

[[E_VECTORED_HOLD]] is the dispatching form: hold until *any* OR-term fires, then branch
to the vector-table entry belonging to the term that fired. Conceptually it is
"`HOLD` + `GOTO`/`GOSUB` to vector" — the closest analogue is Arm's `WFI` followed by
interrupt dispatch, except there is no interrupt controller involved and the return
address is saved in `RA` automatically (suppressible with the `NRA` option, as
[[E_VECTORED_HOLD_NRA]]).

The table pointer is passed in a register — commonly `PC`, which places the table
immediately after the hold. By default it has eight entries of one instruction each.

Two dispatch rules, both easy to get wrong:

**Which vector fires for an ANDed term: the *last* slice in the term.** For
`A + B + CD + EF + G` with A on slice 0, B on 1, C/D on 2/3, E/F on 4/5, G on 6:

| Term fires | Vector taken |
|---|---|
| A | 0 |
| B | 1 |
| C & D | 3 |
| E & F | 5 |
| G | 6 |

**When several terms fire at once, the earlier term wins.** Slice 0 outranks slice 7.

Because dispatch is positional, every one of the eight entries must be populated — an
unexpected trigger on an unused slice will still dispatch to its slot. Fill the unused
ones with [[E_NOP]] or a branch to a recovery path rather than leaving them to run into
whatever follows.

```
E_VECTORED_HOLD(PC)
E_NOP                    ; flushed
E_NOP                    ; flushed
; --- vector table ---
E_NOP                    ; slice 0 - unused
E_NOP                    ; slice 1 - unused
E_GOTO(bs2_handler)      ; slice 2
E_GOTO(bs3_handler)      ; slice 3
E_NOP                    ; slice 4 - unused
E_NOP                    ; slice 5 - unused
E_NOP                    ; slice 6 - unused
E_GOTO(bs7_handler)      ; slice 7
```

A handler for a sticky slice must clear the latch, which is any `CFM` write —
conventionally `E_BSET_IMM(CFM, CFM, <slice>)`.

### Accelerated and large-vector forms

The two [[E_NOP]]s above are wasted cycles: the vectored hold flushes them. The
accelerated form keeps them for selected vectors. [[E_ACC_VECTORED_HOLD]] takes the table
pointer *and* a mask of which vectors should execute the two shadow instructions:

```
label
    E_ACC_VECTORED_HOLD(PC, 0x04)   ; accelerate vector 2 only
    E_COND_GOTO(UNS, label)         ; runs if vector 2 fired: scheduled return
    E_BTOG_IMM(GPO, GPO, 0)         ; runs if vector 2 fired: the actual work
    ...
```

If vector 2 fires, those two instructions execute *while* the branch to the handler is in
flight — a scheduled return to the hold plus one instruction of real work, before the
handler is even reached. If any other vector fires, they are flushed as usual.

The **large vector table** variants ([[E_VECTORED_HOLD_LV]],
[[E_ACC_VECTORED_HOLD_LV]]) give each entry four instructions instead of one. Four is not
arbitrary: a scheduled branch plus two unflushed instructions is three, so the fourth slot
is exactly enough for a single-cycle branch onward to a longer handler.

> **Unverified — dispatch latency.** The specification puts the minimum at four cycles for
> an accelerated hold (one to detect and compute the vector, two accelerated instructions,
> one in the vector entry). AN14650 quotes roughly six cycles from trigger to hold release
> for all four vectored-hold variants. The two figures measure different intervals and are
> not necessarily in conflict; both are on the bench list.

## Pending trap {#pending-trap}

The pending trap is a latching layer between the pin inputs and the bit-slices, and a back
door that lets the Arm drive bit-slice state directly. It lives in `EZHB_PENDTRAP`:

| Bits | Field |
|---|---|
| `[23:16]` | Pending trap enable, one bit per slice |
| `[15:8]` | Status polarity |
| `[7:0]` | Request / status |

With the trap enabled, bits `[7:0]` latch input transitions: a bit goes 0 → 1 when its
input goes 0 → 1 and stays there until cleared by software, even if the input falls back.
Setting the polarity byte to `0xFF` inverts the sense, so the latch captures falling edges
instead.

The third use is the interesting one: because the bit-slices see the *trap* bits rather
than the raw pins when the trap is enabled, writing those bits from the Arm synthesises
bit-slice events in software.

| Trap bit `[7:0]` | Presented to the bit-slice as |
|---|---|
| `0` | Low level |
| `1` | High level |
| `0` → `1` | Rising edge |
| `1` → `0` | Falling edge |

So the Arm can fire an EZH vector by writing a register — an Arm → EZH doorbell that lands
on the same dispatch path as a real pin event. The trap is disabled by default.

## GPIO {#gpio}

Up to 32 pins are wired directly into the register file: `GPO` (output), `GPD`
(direction, 1 = output), `GPI` (input, read-only). No AHB transaction, no peripheral
access — a pin write is a register write, single cycle. This is the single largest source
of EZH's advantage in bit-banged protocol work.

Because they are ordinary registers, the whole instruction set applies:
`E_BSET_IMM(GPO, GPO, 21)`, `E_BCLR_IMM(GPD, GPD, 19)`, `E_BTOG_IMM(GPO, GPO, 0)`, and
`E_BTST_IMMS(GPI, GPI, 19)` to test an input into the flags.

On top of that, [[E_MODIFY_GPO_BYTE]] applies a clear mask, a set mask and a toggle mask to
the bottom byte of `GPO` — three read-modify-writes in one cycle. That is the instruction
for driving a parallel bus.

(Note that the older sources sometimes call this opcode `E_GPO_BYTE_MODIFY`; the mnemonic
that exists is [[E_MODIFY_GPO_BYTE]].)

## Heartbeat timer {#heartbeat}

A 16-bit auto-reloading down-counter that "beats" each time it reaches zero. The reload
value is set by [[E_HEART_RYTHM]] (or [[E_HEART_RYTHM_IMM]]); any use of the opcode
replaces the reload value, loads the counter, and starts counting on the next cycle. The
default reload is 0, meaning a beat every cycle — and in that state the counter is
clock-gated, so the default costs nothing.

Two ways to use it:

**[[E_WAIT_FOR_BEAT]]** — halt until the next beat. Alignment on demand, for the
instruction that must happen on the grid:

```
E_HEART_RYTHM_IMM(7500)     ; at 150 MHz: ~20 kHz beat
E_BSET_IMM(GPO, GPO, 21)
E_WAIT_FOR_BEAT
E_BCLR_IMM(GPO, GPO, 21)
E_WAIT_FOR_BEAT             ; ~10 kHz square wave (one beat per half period)
```

> **Off-by-one, unresolved.** A reload of 0 beats every cycle, which implies the period is
> `reload + 1` cycles and puts the example above at 19,997 Hz rather than 20,000 — you
> would load 7499 for exactly 20 kHz. Published examples use the round number and quote
> the round frequency, so either they are approximating or the period is `reload` with 0
> special-cased. The difference is 0.013% and irrelevant to most uses, but it matters for
> long-running bit-banged protocols where the error accumulates. Measure before relying on
> an exact rate.

**[[E_SYNCH_ALL_TO_BEAT]]** — switch modes so that *every* instruction executes only on a
beat. It takes a 1-bit immediate, so the mode is a toggle rather than a one-way door:
turn it on for the timing-critical stretch and back off afterwards to run at full speed.
This buys two things:

- **Power.** The core runs slower by the rhythm factor. If EZH is faster than the task
  needs, this converts the surplus into savings.
- **Snap-to-grid determinism.** The mode is implemented by stalling the execute stage, so
  between beats the core still fetches, decodes, and drains outstanding data transactions.
  Instruction timing becomes deterministic *even when running from memory shared with
  another AHB controller* — the bus contention hides inside the slack. For sampled I/O
  this is the difference between a jittery bit-bang and a clean one.

## Execution supervisor {#supervisor}

The execution supervisor is the hardware that makes [[E_TIGHT_LOOP]] free. It tracks a
loop's end address and iteration count and rewrites the fetch address when the end is
reached — no branch instruction, no bubble (see [tight loop](#pipeline)).

[[E_TIGHT_LOOP]] takes an end-address register and a count register:

```
E_LOAD_IMM(R0, 15)          ; count
E_ADD_IMM(R1, PC, 8)        ; end address = first instruction past the body
E_TIGHT_LOOP(R1, R0)
E_BSET_IMM(GPD, GPD, 0)     ; one-shot (see the two-ahead section)
E_BTOG_IMM(GPO, GPO, 0)     ; body
```

Three properties worth committing to memory:

- **The body executes `1 + count` times.** A count of 15 gives 16 iterations.
- **The setup registers are free after arming.** The supervisor captures the values; `R0`
  and `R1` above can be overwritten inside the loop body without disturbing it.
- **The instruction immediately after [[E_TIGHT_LOOP]] runs once**, on entry — the loop
  body starts one instruction later. This is the pipeline lookahead showing through, and
  it is a useful slot rather than a wart.

## Stack and return address {#stack-ra}

There is no automatic stack management. `SP` is a register the software maintains;
[[E_PUSH]] and [[E_POP]] are aliases over [[E_STR]] and [[E_LDR]] with the pointer
hardcoded to `SP` and the growth direction fixed **upward**.

What the hardware *does* do automatically is save the return address into `RA`:

- **[[E_GOSUB]]** always writes `RA`.
- **[[E_VECTORED_HOLD]]** writes `RA` unless the `NRA` option is used.
- **[[E_GOTO]] with the `L` option** ([[E_GOTO_REGL]]) writes `RA`.

**The saved value accounts for the delay slots.** An ordinary branch saves the address of
the instruction that follows it. A *scheduled* branch saves that address plus four — the
instruction after the two delay slots — because the two shadow instructions have already
executed by the time the handler returns, and re-running them would be wrong. This is the
"return with offset" behaviour the architecture advertises, and it means returning through
`RA` is correct in both cases without the caller knowing which kind of branch got it there.
(Behaviour confirmed by hardware analysis; advisory pending creator review.)

`RA` is a single register, so nested calls must preserve it themselves:

```
main
    E_LOAD_IMM(R0, 0xDD)
    E_GOSUB(f1)             ; RA = return into main
endfc
    E_GOSUB(endfc)          ; park

f1
    ...
    E_PUSH(RA)              ; preserve before clobbering
    E_GOSUB(f2)             ; RA = return into f1
    E_POP(RA)
    E_GOTO_REG(RA)          ; return to main

f2
    ...
    E_GOTO_REG(RA)          ; return to f1
```

## Breakpoint support {#breakpoint}

EZH has a hardware breakpoint, driven entirely from two control registers and usable
without a debugger — it is really a "call out to my own code at this address" facility,
which is what makes it good for self-diagnosis on a core that has no other visibility.

- `EZHB_BREAK_ADDR` — the instruction address to break on.
- `EZHB_BREAK_VECT` — the handler address.

The mechanism is a substitution in the fetch path: when the instruction bus would fetch
`EZHB_BREAK_ADDR`, EZH substitutes `EZHB_BREAK_VECT`. Two consequences follow directly:

1. **If the instruction would have been flushed, the breakpoint does not fire.** This is
   the correct behaviour — a breakpoint should trip on execution, not on prefetch — and it
   comes out of the design for free.
2. **The instruction at `EZHB_BREAK_ADDR` never executes.** It is replaced, not preceded.
   So point `EZHB_BREAK_ADDR` at an [[E_NOP]] you inserted for the purpose; otherwise you
   have silently deleted an instruction from your program.

The handler returns by reading `EZHB_BREAK_ADDR` back with [[E_PER_READ]], adding 4, and
branching:

```
; handler at EZHB_BREAK_VECT - dump registers where the Arm can see them
E_PUSH(R4)
E_PUSH(R5)
E_PUSH(R6)
E_PUSH(R7)
E_PER_READ(R0, EZHBREAKADDR)
E_ADD_IMM(R0, R0, 4)
E_GOTO_REG(R0)                  ; resume after the break site
```

The register-address symbols above are bunny_build's (`include/ezh_arch.h`):
`EZHBREAKADDR`, `EZHBREAKVECT`, `ARM2EZH`, `EZH2ARM`. Published NXP listings spell some
of them with an extra underscore (`EZH_BREAKADDR`, `EZH_ARM2EZH`); those names do not
exist in this codebase.

> **Two different things get called "base".** bunny_build's
> `LPC_EZH_ARCH_B_CON_BASE` points at `EZHB_BOOT`, *not* at the start of the peripheral —
> the vendor block has 0x20 of reserved space ahead of it. So bunny_build's offsets run
> **0x20 lower** than the peripheral-relative offsets in the register table above:
> `EZHBREAKADDR` is `CON_BASE + 0x10`, the same register the table lists at `0x30`.
> Cross-reference the two without noticing and every offset is off by 0x20.

**A tight loop wins over a breakpoint at the same address.** If the address the execution
supervisor is about to rewrite is also the breakpoint address, the loop rewrite happens
first and the breakpoint does not fire — the substitution never gets the chance, because
the address was replaced before the comparison. Setting a breakpoint on the last
instruction of a [[E_TIGHT_LOOP]] body is therefore not a reliable way to catch each
iteration. (Ordering confirmed by hardware analysis; advisory pending creator review.)

> **Do not place a breakpoint inside a scheduled branch's shadow.** It fires correctly, but
> on return the pending branch is gone: you re-execute the shadow instructions and then
> fall through instead of branching. Recovering from this requires copying the shadow
> elsewhere and re-entering through the original branch — possible, but not worth it. See
> [two-ahead](#two-ahead).

## Error and emergency mode {#emergency}

Emergency mode exists to shut a system down in a controlled way, not to recover from a
fault. Three things can enter it:

- the external emergency input asserting,
- an `ERROR` response on **either** AHB bus (suppressible: `EZHB_CTRL` bit 2 makes EZH
  ignore AHB errors),
- a software request, via `EZHB_EMER_SEL` bit 9, with the software-emergency mechanism
  enabled by bit 8.

On entry, EZH branches at the next possible instruction cycle to `EZHB_EMER_VECT`. From
there nothing is restricted — the emergency handler is ordinary code and can do anything.

What makes it *emergency* mode is that it is **one-way**. Once entered, it cannot be left
except by resetting EZH, either by dropping the ignition bit in `EZHB_CTRL` or by resetting
the block. Subsequent emergency assertions and AHB errors have no further effect.

**On the `EZHB_EMER_SEL` bit 8 confusion.** AN14650's register table describes bit 8 as
enabling the software emergency mechanism, but the `EZH_SetEmergencyMode` listing in the
same document *clears* bit 8 on its enable path and sets it on its disable path. The two
contradict each other. NXP's own machine-readable register description for the part
settles it: the field is named **`EN`**, alongside `RQ` for the bit 9 request. The
register table is right and the code listing is inverted — **write 1 to bit 8 to enable
software emergency.**

> Strictly, the vendor data gives the field name and description but no enumerated
> values, so active-high is inferred from NXP's own naming convention rather than stated.
> That convention is consistent and visible in this very register block: inverted-sense
> bits get negative names — `EZHB_CTRL` bit 2 is `ERRDIS`, "Error Disable" — while
> positive-sense bits are `EN`, `START`, `RQ`, `BUFEN`, `SYNCEN`. Confirm on the bench if
> it matters to your shutdown path.

## Arm ↔ EZH interaction {#arm-ezh}

Everything the Arm can say to EZH, and everything EZH can say back, goes through the APB
control register block and a small number of dedicated paths. This section collects all of
them.

### The EZHB control register block

| Name | Off | Acc | Contents |
|---|---|---|---|
| `EZHB_BOOT` | `0x20` | RW | `ADDR[31:2]` boot address. The low two bits are not part of the field — 4-byte alignment is structural, not a convention |
| `EZHB_CTRL` | `0x24` | RW | `WKEY[31:16]` key `0xC0DE`, required on every write · `SYNCEN[4]` AHB synchronisation, must be 1 · `BUFEN[3]` bufferable AHB writes · `ERRDIS[2]` error disable — set to ignore AHB errors, clear and an error raises emergency · `EXF[1]` external flag, drives `EX`/`NEX` · `START[0]` ignition |
| `EZHB_PC` | `0x28` | RO | EZH program counter — observable from the Arm |
| `EZHB_SP` | `0x2C` | RO | EZH stack pointer — observable from the Arm |
| `EZHB_BREAK_ADDR` | `0x30` | RW | `ADDR[31:2]` breakpoint address |
| `EZHB_BREAK_VECT` | `0x34` | RW | `VEC[31:2]` breakpoint handler |
| `EZHB_EMER_VECT` | `0x38` | RW | `VEC[31:2]` emergency handler |
| `EZHB_EMER_SEL` | `0x3C` | RW | `RQ[9]` software emergency request · `EN[8]` software emergency enable |
| `EZHB_ARM2EZH` | `0x40` | RW | `GP[31:2]` general purpose — conventionally the parameter-block pointer · `IE[1:0]` EZH→Arm interrupt enable/mode |
| `EZHB_EZH2ARM` | `0x44` | RW | `GP[31:0]` general purpose; writing it interrupts the Arm when `IE == 0b10` |
| `EZHB_PENDTRAP` | `0x48` | RW | `EN[23:16]` · `POL[15:8]` · `STATUS[7:0]` — see [pending trap](#pending-trap) |

Field names above are NXP's own, from the vendor register description. On MCX parts the
peripheral is named `SMARTDMA0` rather than `EZH`, and its INPUTMUX registers are named
`SMARTDMAARCHB_INMUX[n]` — "Arch B" in the silicon's own register naming.

The `0xC0DE` key in the upper half of `EZHB_CTRL` is required on **every** write — a
read-modify-write that preserves the top half will silently do nothing.

> **Core versus wrapper — worth knowing when you go looking for answers.** The `EZHB_*`
> block is not part of the EZH core. It is the NXP peripheral wrapper built around the
> core, which is why its base address, and sometimes its contents, vary by part. The
> architecture-level sources describe the core: they speak of an *emergency input signal*,
> an *external condition input*, a *breakpoint address fed in from the system* — never the
> registers that drive them. Those registers are documented only in per-chip Reference
> Manuals and application notes.
>
> The practical consequence: a question about instruction behaviour, flags, the pipeline
> or the bit-slices can be settled from architecture sources. A question about an `EZHB_*`
> register's bit polarity cannot — it needs the Reference Manual for your part, or a
> bench. Two of the open questions in this chapter fall on the wrapper side of that line.

### Arm → EZH

**Boot and ignition.** Write `EZHB_BOOT`, write `EZHB_ARM2EZH`, then set the ignition bit
(with the key, and with AHB synchronisation enabled). Dropping ignition resets the core —
this is also the only way out of emergency mode.

**The parameter block.** `EZHB_ARM2EZH[31:2]` conventionally holds a pointer to a struct
of arguments; the low two bits are the interrupt-mode field, so EZH masks them off before
use. This is how the Arm hands EZH its stack address, buffer pointers, and configuration:

```
E_PER_READ(R6, ARM2EZH)
E_LSR(R6, R6, 2)             ; discard the mode bits
E_LSL(R6, R6, 2)
E_LDR(SP, R6, 0)             ; first member: the stack
```

**The external flag.** `EZHB_CTRL` bit 1 is a one-bit mailbox the Arm can set and EZH can
test with the `EX`/`NEX` conditions. EZH cannot set or clear it, only observe it.

**The pending trap.** With the trap enabled, the Arm can write `EZHB_PENDTRAP[7:0]` to
synthesise bit-slice edges, firing an EZH vector directly. See
[pending trap](#pending-trap).

**Trigger sources.** Anything routed into `EZH_INPUTMUX[0..7]` — peripheral interrupts,
timer matches, GPIO — reaches the bit-slices without Arm involvement at all.

**Breakpoints and emergency.** `EZHB_BREAK_ADDR`/`EZHB_BREAK_VECT` and
`EZHB_EMER_SEL[9]` are both Arm-side controls over EZH execution.

**Observation.** `EZHB_PC` and `EZHB_SP` are readable at any time — the minimum viable
debugger.

> **Unverified — `TxEV`/`__SEV()`.** Internal material describes EZH as able to monitor the
> Arm's `TxEV` event signal, raised by the `__SEV()` intrinsic, giving a direct Arm → EZH
> wakeup that pairs with an EZH → Arm interrupt for two-way handshaking. No public source
> confirms it. Pending creator review or a Reference Manual.

### EZH → Arm

There are four mechanisms, and they are genuinely different — not variations on one.

**1. [[E_INT_TRIGGER]] → the EZH NVIC slot.** EZH has its own interrupt line into the
NVIC. [[E_INT_TRIGGER]] fires a single-cycle pulse on it, and **the common output always
fires, regardless of the 24-bit argument**. The argument selects only which of the 24
*additional* hijack channels pulse alongside it (mechanism 2 below). This is the ordinary
"I'm done, come look" signal. [[E_INT_TRIGGER]] is one of the very few opcodes that cannot
be conditional — the 24-bit mask occupies the bits the condition field would use.

> **`E_INT_TRIGGER(0)` is well-defined, and it is the idiomatic end-of-program signal.**
> Zero selects no hijack channels, while the common interrupt still fires — exactly what
> a program wants when it is done and has no peripheral to impersonate. This is why the
> historical corpus ends programs with it.
>
> Be aware that AN14650 §4.2.14 states the argument must be a positive number greater
> than zero. That is contradicted by the architecture specification (which lists *no*
> restrictions on this opcode and states the common interrupt is always triggered), by
> AN14650's own instruction reference in §5.21, and by every program in the sample corpus.
> Read it as advice for the hijack case — where a zero mask would indeed be pointless —
> rather than a constraint on the instruction.

**2. [[E_INT_TRIGGER]] → interrupt hijack.** EZH also drives a wider interrupt output bus
where each bit maps onto *another peripheral's* interrupt line. This lets EZH impersonate
a peripheral toward the Cortex-M: `E_INT_TRIGGER(1 << 3)` raises the third hijackable
interrupt, and the Arm's existing handler for that peripheral runs. The hijack function
must be enabled in SYSCON.

> **How many channels?** The instruction encoding settles the upper bound: the immediate
> is a 24-bit field, so at most **24** channels are addressable from EZH code. Published
> descriptions of the output bus say 32 bits, fewer on some parts — that is the width of
> the hardware bus, not of the field an instruction can drive. Treat 24 as the number that
> matters when writing code, and expect the per-part count to be lower still.

**3. `EZHB_EZH2ARM` handshake.** When `EZHB_ARM2EZH[1:0] == 0b10`, *any* write to
`EZHB_EZH2ARM` interrupts the Arm — and the written value is the payload. This is the
mechanism for "here is the buffer I just filled", combining notification and data in one
[[E_PER_WRITE]].

**4. Event out.** The same `EZHB_ARM2EZH` mode field can select an event-out signal rather
than an interrupt, for waking the Arm from `WFE` without an ISR.

Interrupt enable is ordinary NVIC work on the Arm side; the EZH IRQ number is per-part and
lives in the [platform guide](platform.html).

> **Unverified — EZH during Arm debug halt.** Internal material states that once started,
> EZH continues executing while the Arm is halted at a debug breakpoint. If true this is
> important for debugging — the coprocessor does not stop when you stop. On the bench list.

## Known limits and open questions {#open-questions}

Collected from the sections above, the claims in this chapter that are not yet settled by a
public source, a bench result, or creator review:

| Item | Section | Confidence | Resolution path |
|---|---|---|---|
| `TxEV`/`__SEV()` monitoring | [Arm ↔ EZH](#arm-ezh) | Single source — one internal deck, nothing else | Creator review or RM |
| EZH runs while Arm is halted | [Arm ↔ EZH](#arm-ezh) | Single source — one internal deck, nothing else | Bench |
| Vectored-hold dispatch latency | [Boolean detection](#boolean-detection) | Two figures (4 vs ~6 cycles) that may measure different intervals | Bench |
| Heartbeat period: `reload` or `reload + 1` | [heartbeat](#heartbeat) | Published examples imply one, the reload-0 behaviour implies the other | Bench |
| Shift-by-register amounts ≥ 32 | [ALU and shifter](#alu-shifter) | All sources agree; never confirmed on silicon | Bench |
| `E_INT_TRIGGER(0)` behaviour | [Arm ↔ EZH](#arm-ezh) | **Resolved** — spec states the common interrupt always fires and lists no restrictions | Closed; bench optional |
| `PC` source read = current + 8 bytes | [two-ahead](#two-ahead) | Derived three ways, plus hardware analysis and a database cross-check | Bench, to confirm |
| Boot word not executed | [system context](#system-context) | Four independent directions agree, incl. a program that puts data there | Bench, to confirm |
| `EZHB_EMER_SEL[8]` polarity | [emergency](#emergency) | **Resolved** from the vendor register description; active-high inferred from naming | Bench, non-blocking |

The list is ordered by how much is genuinely unknown. The first four are open questions.
The last five are settled to the point where a bench session would be confirming an
answer rather than looking for one.

The full bench list, including the encoding-level questions raised by the ISA database
verification pass, is tracked in the `ezh-instruction-set-docs` plan under
`hardware-adjudication`.
