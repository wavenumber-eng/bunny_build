+++
type = "plan"
id = "ezh-browser-simulator"
status = "pending"
created = "2026-07-21"
depends_on = ["ezh-instruction-set-docs"]

[[steps]]
id = "work"
title = "Execute plan work"
status = "pending"

[[steps]]
id = "design-doc-intent-audit"
title = "Audit design docs, ADRs, and requirements against implementation"
status = "pending"
depends_on = ["work"]

[[steps]]
id = "test-runtime-impact-audit"
title = "Audit new test runtime impact"
status = "pending"
depends_on = ["work"]

[[steps]]
id = "external-review"
title = "Obtain independent external review"
status = "pending"
depends_on = ["work", "design-doc-intent-audit", "test-runtime-impact-audit"]

[[exit_criteria]]
id = "signoff"
title = "Focused signoff passes"
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

# EZH browser simulator (C core to WebAssembly, with debugging)

Parked until the ISA db from `ezh-instruction-set-docs` exists — the simulator's
decoder should be generated from / validated against it, never hand-duplicated.

Vision:

- Instruction-set simulator core written in portable C (same discipline as
  bunny_build: plain .c/.h, host- and target-buildable), compiled to WebAssembly for
  a browser-hosted experience.
- Debugging is the point, not a stretch goal: breakpoints, single-step,
  register/flag/GPO-GPI-GPD views, disassembly (from the ISA db), cycle counts.
- Reference points: `docs/InstructionSetSimulator.tgz` in the ezh archive (NXP's
  simulator — inspect before writing anything) and `ezh_tb_package.sv` for pipeline
  behavior (advisory; it was an experiment).
- The camera generator blob is the natural first conformance program: simulate it
  and compare bus traffic/GPO activity against expectations.
