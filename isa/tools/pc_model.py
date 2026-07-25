"""EZH PC-relative arithmetic: one model, self-tested against the sources.

Every PC-relative idiom in the documentation depends on two facts that are easy
to state and easy to get wrong:

  * a `PC` source read yields the current instruction's address + 8 bytes
    (two 32-bit instruction words, because the pipeline runs two ahead);
  * immediate operands are NOT in uniform units - the ALU immediate forms
    (`imm12s`: E_ADD_IMM, E_SUB_IMM) take raw BYTES, while the load/store
    offset (`offset8s`: E_LDR, E_STR) is scaled by access size, so one
    instruction is `1` for a word access.

A single off-by-one-word here silently breaks label tables, tight-loop bounds
and computed branches. This module is the one place that arithmetic lives, with
a self-test built from worked examples in the authoritative sources so that
changing the model breaks loudly.

Run standalone:
    uv run python isa/tools/pc_model.py
"""

from __future__ import annotations

WORD = 4
#: A PC source read returns the current instruction's address plus this many
#: bytes. On the bench list for silicon confirmation; derived independently from
#: three worked examples and corroborated by hardware analysis.
PC_READ_OFFSET = 8


def pc_read(instr_addr: int) -> int:
    """Value a `PC` source read yields when executing at `instr_addr`."""
    return instr_addr + PC_READ_OFFSET


def alu_imm_target(instr_addr: int, imm_bytes: int) -> int:
    """Target of `E_ADD_IMM(Rd, PC, imm)` - the immediate is raw bytes."""
    return pc_read(instr_addr) + imm_bytes


def ldr_word_target(instr_addr: int, offset_words: int) -> int:
    """Address loaded by `E_LDR(Rd, PC, off)` - the offset is word-scaled."""
    return pc_read(instr_addr) + offset_words * WORD


def instr_delta(instr_addr: int, target: int) -> float:
    """Distance from an instruction to a target, in instruction words."""
    return (target - instr_addr) / WORD


# ---------------------------------------------------------------------------
# Self-test: worked examples whose intended result the sources state outright.
# Each case is (description, computed, expected-in-instruction-words-from-the-
# instruction itself).
# ---------------------------------------------------------------------------

def _cases() -> list[tuple[str, int, int, float]]:
    """Return (description, anchor address, computed target, expected delta).

    The anchor travels with each case rather than being recovered from the
    description text, so adding a case cannot silently mis-anchor it.
    """
    a = 0x1000
    out: list[tuple[str, int, int, float]] = []

    # Label-table idiom: E_ADD_IMM(R7, PC, -4) immediately followed by the
    # table, intended to point at the first table entry (the next instruction).
    out.append(("label table: E_ADD_IMM(Rn, PC, -4) -> next instruction",
                a, alu_imm_target(a, -4), 1))

    # 16x16 multiply: E_LDR(R0, PC, 7) at word 0 reaches the multiplicand DCD
    # nine words down the listing; E_LDR(R1, PC, 7) one word later reaches the
    # multiplier, also nine words from itself. Two anchors, one offset.
    out.append(("multiply: E_LDR(R0, PC, 7) at word 0 -> word 9",
                a, ldr_word_target(a, 7), 9))
    out.append(("multiply: E_LDR(R1, PC, 7) at word 1 -> word 10",
                a + WORD, ldr_word_target(a + WORD, 7), 9))

    # Scheduled branch: E_ADD_IMMS(PC, PC, 8) is documented as branching four
    # instructions ahead of the current one.
    out.append(("scheduled branch: E_ADD_IMMS(PC, PC, 8) -> +4 instructions",
                a, alu_imm_target(a, 8), 4))

    # Tight loop: E_ADD_IMM(R1, PC, 8) must yield the first instruction PAST a
    # one-instruction body. Counting from the E_ADD_IMM itself:
    #   a+0  E_ADD_IMM(R1, PC, 8)
    #   a+4  E_TIGHT_LOOP(R1, R0)
    #   a+8  one-shot            (runs once, on loop entry)
    #   a+12 body                (three words after the E_ADD_IMM)
    #   a+16 first instruction past the body   <- wanted, +4 words
    out.append(("tight loop: E_ADD_IMM(R1, PC, 8) -> instruction past body",
                a, alu_imm_target(a, 8), 4))

    # A negative word-scaled offset, exercising the ldr path in the other
    # direction - otherwise no case distinguishes a sign error there.
    out.append(("word-scaled negative: E_LDR(Rd, PC, -3) -> -1 instruction",
                a, ldr_word_target(a, -3), -1))

    return out


def selftest(verbose: bool = False) -> list[str]:
    """Return a list of failure messages; empty means the model holds."""
    failures: list[str] = []
    for desc, anchor, computed, expected_words in _cases():
        got = instr_delta(anchor, computed)
        if got != expected_words:
            failures.append(
                f"{desc}: expected {expected_words:+g} instructions, got {got:+g}"
            )
        elif verbose:
            print(f"ok   {desc}  ({got:+g} instructions)")
    return failures


def main() -> int:
    print(f"PC_READ_OFFSET = {PC_READ_OFFSET} bytes ({PC_READ_OFFSET // WORD} instruction words)\n")
    failures = selftest(verbose=True)
    print()
    if failures:
        for f in failures:
            print(f"FAIL {f}")
        print(f"\n{len(failures)} failure(s)")
        return 1
    print("PC model reproduces every worked example.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
