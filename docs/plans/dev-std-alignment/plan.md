+++
type = "plan"
id = "dev-std-alignment"
status = "pending"
created = "2026-07-21"

[[steps]]
id = "repo-hygiene-files"
title = "Add required repo files: AGENTS.md, CHANGELOG.md, CONTRIBUTING.md, LICENSE, .gitattributes, .clang-format, .clang-tidy"
status = "pending"

[[steps]]
id = "cmake-presets"
title = "Add CMakePresets.json with ninja + compile_commands lanes"
status = "pending"

[[steps]]
id = "test-orchestration"
title = "Register validator under ctest and add tests/rack.toml + signoff.toml"
status = "pending"

[[steps]]
id = "required-docs"
title = "Add docs/setup.html, docs/architecture.html, docs/design/, docs/contracts/, docs/releases/"
status = "pending"

[[steps]]
id = "audit-clean"
title = "dev-std audit . passes with full scope"
status = "pending"
depends_on = ["repo-hygiene-files", "cmake-presets", "test-orchestration", "required-docs"]

[[steps]]
id = "design-doc-intent-audit"
title = "Audit design docs, ADRs, and requirements against implementation"
status = "pending"
depends_on = ["audit-clean"]

[[steps]]
id = "test-runtime-impact-audit"
title = "Audit new test runtime impact"
status = "pending"
depends_on = ["audit-clean"]

[[steps]]
id = "external-review"
title = "Obtain independent external review"
status = "pending"
depends_on = ["audit-clean", "design-doc-intent-audit", "test-runtime-impact-audit"]

[[exit_criteria]]
id = "signoff"
title = "Focused signoff passes"
status = "pending"

[[exit_criteria]]
id = "full-audit-passes"
title = "dev-std audit . --scope all passes on the cpp-library profile"
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

# Align bunny_build to wn-dev-std cpp-library profile

Bring bunny_build into full compliance with the wn-dev-std `cpp-library` profile
(2026.7.18). The bootstrap (pyproject.toml, dev-std.toml, docs/plans) is already in
place; this plan covers the rest: required repo files, CMake presets, clang-format /
clang-tidy, ctest + rack test orchestration, and the required docs tree.

Notes:

- bunny_build is C (not C++) and must stay buildable both on host PCs and inside
  embedded/Zephyr targets — profile rules that assume a pure host library (sanitizer
  lanes, warnings-as-errors scope) get applied to the host/validator lanes first.
- The existing `test/cl_build` validator (camera byte-for-byte comparison) becomes
  the first ctest-registered test.
- Runs after the EZH documentation effort is underway; docs tree layout should not
  conflict with what `ezh-instruction-set-docs` chooses in `choose-doc-toolchain`.
