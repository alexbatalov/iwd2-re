# How to translate a function

This is the working guide for translating functions from the original `iwd2.exe` into `src/`. Read [translation-plan.md](translation-plan.md) for the overall plan.

## Local setup (outside the repo, never committed)

| Path | What |
|---|---|
| `C:\iwd2-ref` | Pristine GOG 2.01 install. Read-only reference. Hashes are in [reference-hashes.md](reference-hashes.md). |
| `C:\iwd2-play` | Disposable test copy. Rebuild it with `tools\make_play_dir.ps1`. |
| `C:\iwd2-tools\decomp\0xADDR.c` / `.asm` | Ghidra decompilation and disassembly for each function |
| `C:\iwd2-tools\functions.json` | Every function with name, size, callers, callees and signature |
| `C:\iwd2-tools\venv` | Python for the play tests (Pillow, NumPy, pytest) |

## Tools

- `py -I tools/peek.py s 0x8B0B4C`: read a C string from the exe (assert messages, file names). `d`/`w`/`b`/`f` read dwords, words, bytes and floats; `name 0xADDR` looks up a function.
- `grep -rh -A1 "^// 0xADDR$" src`: what the repo already calls that address.
- `py -I tools/inventory.py`: progress, plus the most-needed untranslated functions.
- `powershell -ExecutionPolicy Bypass -File tools\check.ps1`: build, inventory ratchet and unit tests (including layout).
- Build only: `& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" --build build --config RelWithDebInfo --target iwd2-re -- /m /nologo /v:minimal`. Run it from PowerShell, because Git Bash turns `/m` into a path.
- Play tests: `C:\iwd2-tools\venv\Scripts\python -m pytest tests/e2e/scenarios/test_s2_new_game.py --target reimpl`. They take over the mouse and keyboard.
- Crash reports: the rebuild writes `iwd2re-crash.txt` (symbolized stack) and `.dmp` to `IWD2RE_CRASH_DIR` or the current directory.

## Workflow per function

1. Read **both** `0xADDR.asm` and `0xADDR.c`. The asm is the truth. Ghidra drops arguments to `__thiscall` calls and almost every call shows up as `Foo()`, so get arguments from the `PUSH`es and `ECX` in the asm.
2. Name every callee with `grep -rh -A1 "^// 0x<callee>$" src`. If a callee isn't in `src`, read its asm. Small ones (< ~60 bytes) are often inlined template helpers you should add. Note larger missing callees in your report rather than translating the whole tree.
3. Map every `[reg + offset]` to an annotated member (`/* 05A0 */ CString m_sName;`). Add missing members to headers with offset comments, replacing `field_XXX` padding or `unknown` arrays at the right position.
4. Use the assert strings: `PUSH 0x8b019c` / `PUSH 0x104c` before `CALL 0x780c00` is `UTIL_ASSERT` at `__FILE__` `peek s 0x8b019c` and `__LINE__` 0x104c. Copy the `// __FILE__:` / `// __LINE__:` comment style used everywhere.
5. Write code in the surrounding style. Keep the original's order of side effects, and don't "fix" original bugs (mark them `// NOTE:` or `// FIXME:`).
6. Put `// 0xADDR` on the line above the definition and remove `// TODO: Incomplete.` once the function is complete.
7. Build. Then run the cheapest test that covers the function.

## Pitfalls found so far

- **Multi-character literals are byte-reversed.** The original compares file signatures as little-endian DWORDs (`CMP [EAX], 0x204D5449` is `"ITM "`). In MSVC `'ITM '` is 0x49544D20, so write `' MTI' /* "ITM " */`. Check the constant in the asm every time.
- **Inlined `CResHelper::SetResRef`.** A block that compares a `CResRef`, calls `CDimm::GetResObject` (0x786DF0) and then `CRes::Request` (0x77E610) is an inlined `SetResRef(resRef, TRUE, TRUE)`. Write it as one call with `// NOTE: Uninline.`
- **Identical code folding.** One address can be the body of many tiny functions (empty virtuals, `CResHelper` getters, destructors). The same `// 0xADDR` in several places is expected. Ghidra names such an address after whichever caller it saw first (e.g. `C2DArray_Destruct`).
- **Struct packing.** The original was built with 2-byte packing. Header offset annotations reflect that. The unit test `annotated member offsets match the original layout` checks every annotation, compiled with `/Zp2`. Mismatches already known are listed in `tests/layout/known_mismatches.txt`. Don't add new ones, and remove entries you fix.
- **Globals.** `0x8CF6D8` is `g_pChitin` (`cDimm` at +0x542), `0x8CF6DC` is `g_pBaldurChitin` (`m_pObjectGame` at +0x1C54, `m_pEngineSinglePlayer` at +0x1C94). `0x780C00` is the assert handler.
- **Empty CString.** `MOV reg, [0x8C1758]` followed by a store is an inlined default `CString` constructor. `0x8C5CF8` is the empty string `""`.
- **The factory has gaps.** Check `CBaldurChitin::AllocResObject` / `CChitin::AllocResObject` when a resource type silently fails to load.
