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

- Phase A, translated by parallel agents (one worktree each, then merged):
  - `CInfGame`: `UpdateCharacterSlots`, `SetupCharacters`, `GetProtagonist`, `SelectToolbar`, `SynchronousUpdate`, `CacheResFileWithResource`, `SaveGame`, `Marshal`, `Unmarshal`.
  - Marshal functions: `CGameArea::Marshal`, `CGameTrigger::Marshal`, `CWorldMap::Marshal`, `CGameSprite::Marshal`, `CGameSpriteEquipment::Marshal`.
  - `CDimm::CompressDirectory`, `CGameEffectList::RemoveAllOfType`, plus small helpers.
- Fixes I made along the way:
  - `NonBlockingWaitForSignal` was a stub, which hung the single-player save.
  - The 8-byte resref used as a file name had no terminator, so `ICEWIND2.GAM` was written under a garbage name.
  - `WriteSetUp` created one-character folder paths, so compressed CD2 BIFs couldn't be cached and the area's WED failed to load.
  - Test tooling: an on-demand hang stack dump (`iwd2re-dump-<pid>` event).

**Current state of S2 on the rebuild:** a new game with a premade party **reaches the world screen** at Targos (AR1000). The map, action bar and HP counters render. Still different from the original:
- The Prologue chapter screen is skipped.
- Party sprites and portraits aren't drawn.
- Hedron's opening dialogue doesn't start.
- Starting gold isn't checked yet.

**Next (Phase A continues)**
1. Make S2 wait for the chapter screen, and find why it's skipped (`CScreenChapter`, the chapter text resources and the call after `LoadGame`).
2. Find why sprites and portraits don't draw (`CGameSprite` render/AIUpdate TODOs, `CScreenWorld` portrait panel). Use the hang/crash tools and compare screenshots with the original.
3. Opening dialogue: the area script and dialogue start (`CMessage` TODOs, `CScreenWorld` dialogue).
4. Stubs left behind:
   - `CSearchBitmap::GetNearestOpenSquare` (0x548B80), which only matters for multiplayer late joins.
   - `CResFile::sub_789A20`/`sub_789CE0` (BIF cache helpers).
   - `CInfGame::CachingRequirements` (0x5A04B0).
   - `CBaldurMessage::WaitForSignal`/`KickOutWaitingForSignal`.
   - `sub_5A79E0`/`sub_5A7BF0`, which only convert old save versions.
   - `CBaldurMessage::sub_43D8D0`, multiplayer.
5. The `CCreatureFileHeader` tail layout is wrong (about 0x2AA bytes instead of 0x37C), so CRE saves aren't byte-compatible after offset 0x294. Fix this before checking save compatibility (S10).

**Notes for next session**
- `inventory.py` counts a function as done once annotated, even with `TODO: Incomplete` inside, so bytes done (69%) overstates progress. Consider subtracting the sizes of functions that contain TODOs.
- The T4 hook-DLL spike hasn't started. `mfc.h` has VC6 support (`_MSC_VER == 1200`), so a VC6 + MFC 4.2 build would match the original's `CString`/heap ABI. That's worth checking before writing shims.
- Builds must run from PowerShell, because Git Bash mangles MSBuild `/m`.
- Play tests take over the mouse. Never run them in parallel.
