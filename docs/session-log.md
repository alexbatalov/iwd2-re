# Session log

Newest first. Each entry covers what was done, what's blocked and what's next.

## 2026-11-11: Phase 0 setup, first Phase A fixes

**Done**
- Tooling: VS 2022 MFC + CMake components, innoextract, JDK 21, Ghidra 12.1.4, Python venv, all in `C:\iwd2-tools`.
- Pristine reference extracted to `C:\iwd2-ref` and hashes recorded. The installed `C:\GOG Games` copy is modded (IWD2EE/IEex), and its `iwd2.exe` differs in 80 bytes of `.data`.
- Ghidra export: `C:\iwd2-tools\functions.json` and `decomp\0xADDR.{c,asm}` for 32k functions.
- Repo: `iwd2-core` static library, doctest unit tests, generated layout test (`/Zp2`, 5,145 members, 2,609 known mismatches), inventory and ratchet, check script, CI on windows-2022, crash handler, play harness (S1 boot, S2 new game), exploration driver, `tools/peek.py`, [translating.md](translating.md).
- T5: S1 passes on the original and the rebuild (main menu and Options match). S2 golden run recorded on the original (Targos opening dialogue).
- Fixes found by S2 on the rebuild:
  - Premade party Done checked the wrong member.
  - Six resource parsers compared byte-reversed signatures (CHR, ITM, BAM, DLG, EFF, STO).
  - `CInfGame::ImportCharacter` translated, plus `CResBIO`, `CCharacterFile` and missing factory cases.

**Current state of S2 on the rebuild:** the premade party imports, then the game crashes in `CInfGame::WorldEngineActivated` because no area is loaded. The new-game path depends on stubs `UpdateCharacterSlots`, `SetupCharacters`, `SaveGame`, `Unmarshal`, `GetProtagonist` and `SelectToolbar` (all `CInfGame`). These are being translated in worktrees `C:\Users\Luke\Projects\iwd2-re-wt\{savegame,unmarshal,party,world}`.

**Notes for next session**
- `inventory.py` counts a function as done once annotated, even with `TODO: Incomplete` inside, so bytes done (69%) overstates progress. Consider subtracting the sizes of functions that contain TODOs.
- The T4 hook-DLL spike hasn't started. `mfc.h` has VC6 support (`_MSC_VER == 1200`), so a VC6 + MFC 4.2 build would match the original's `CString`/heap ABI. That's worth checking before writing shims.
- Builds must run from PowerShell, because Git Bash mangles MSBuild `/m`.
- Play tests take over the mouse. Never run them in parallel.
