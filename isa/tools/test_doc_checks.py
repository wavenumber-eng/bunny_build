"""Regression checks for mnemonic validation and documentation filtering."""

import contextlib
import copy
import io
import json
import os
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import check_docs
import expand_mnemonics
import extract_fsl
import gen_docs


class ValidationChecks(unittest.TestCase):
    def test_swapped_mnemonic_bindings_fail(self):
        data = copy.deepcopy(expand_mnemonics.load())
        form = next(f for f in data[2]["mov"]["forms"] if f["name"] == "reg")
        form["mnemonic"]["binds"] = ["cond", "s", "n"]
        report = io.StringIO()
        with patch.object(expand_mnemonics, "load", return_value=data), patch(
            "sys.argv", ["expand_mnemonics.py", "--header", str(extract_fsl.BUNDLED_HEADER)]
        ), contextlib.redirect_stdout(report):
            self.assertEqual(expand_mnemonics.main(), 1)
        self.assertIn("FAIL base E_MOVS", report.getvalue())
        self.assertIn("FAIL base E_MVN", report.getvalue())

    def test_full_check_always_runs_mnemonic_validation(self):
        commands = []
        with patch.dict(os.environ, {}, clear=True), patch.object(
            gen_docs, "run_command", side_effect=lambda command: commands.append(command) or 0
        ):
            self.assertEqual(gen_docs.preflight(full=True), 0)
        self.assertTrue(any("isa/tools/expand_mnemonics.py" in c for c in commands))
        self.assertTrue(any("isa/tools/verify_fsl.py" in c for c in commands))

    def test_private_catalog_is_used_and_missing_catalog_fails(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "markers.json"
            path.write_text(json.dumps({"markers": ["restricted example title"]}))
            with patch.dict(os.environ, {"BUNNY_BUILD_PRIVATE_MARKERS": str(path)}):
                self.assertIn(
                    "restricted example title",
                    check_docs.source_marker_hits(
                        "Restricted Example Title", check_docs.non_public_markers()
                    ),
                )
                path.unlink()
                with self.assertRaises(OSError):
                    check_docs.non_public_markers()

    def test_directive_wrapper_must_emit_argument_unchanged(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "reference.h"
            path.write_text('#define E_DCD(loc) __asm(".word "#loc)\n'
                            '#define E_GOSUB(a30) E_DCD((a30+3))\n')
            _, inventory, _, errors = extract_fsl.extract(path)
            self.assertEqual(errors, [])
            self.assertEqual(inventory["E_GOSUB"]["base"], 3)
            path.write_text('#define E_DCD(loc) __asm(".word 0")\n'
                            '#define E_GOSUB(a30) E_DCD((a30+3))\n')
            _, _, _, errors = extract_fsl.extract(path)
            self.assertTrue(any("emit its argument unchanged" in e for e in errors))


if __name__ == "__main__":
    unittest.main()
