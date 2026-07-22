+++
type = "plan"
id = "ezh-programming-models"
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

# Explore generally-useful EZH programming models beyond raw assembly

Parked; downstream of the documentation effort. bunny_build (on-target, two-pass,
C-function assembly) was step one. The question this plan answers: what programming
model would make EZH genuinely accessible?

Threads to explore:

- **Pseudo-instruction libraries**: bunny_build already works as a macro substrate —
  gibbon-d's `E_LOAD_32IMM` (PUSH/LOAD_SIMM x4/OR/POP composite) proves the pattern.
  A curated pseudo-instruction library (32-bit immediates, common idioms) is the
  cheapest win and feeds `bunny_build__psuedo_instr`.
- **Application skeletons**: the recurring shapes — run-one-command-and-stop (flat
  samples), multi-app RAM pool with offset dispatch + shared idle epilogue
  (gibbon-d), continuous stream w/ DMA + IRQ (avc camera) — could become parameterized
  templates rather than copy-paste.
- **Higher-level DSL / compiler**: only after the above; the ISA db plus simulator
  make this tractable to validate.
- Whatever emerges lives in bunny_build.
