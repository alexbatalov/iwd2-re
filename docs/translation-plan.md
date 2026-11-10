# IWD2-RE: Plan to finish translating the original game

This plan is for an Opus 5.5 session (or a series of them) working in this repo. The goal is to translate every remaining game function in the original `iwd2.exe` into C++ in `src/`, then show the result is correct, up to a party actually playing the game.

Read this whole file before starting. Sections 1–3 explain the situation, section 4 covers setup, section 5 is the translation loop, section 6 is the test hierarchy, and section 7 has the phase order and exit criteria.

---

## 1. Where the project stands (measured 2026-11-11)

| Metric | Value | Source |
|---|---|---|
| Commits | 2,657, last on 2023-12-29 ("Add CGameSprite::ResolveInstants") | `git log` |
| Source files | ~400 in `src/` (+ `src/music`), one CMake target `iwd2-re` (Win32, MFC, C++17) | `CMakeLists.txt` |
| `// 0xADDR` annotations in `src/` | 9,299 unique (functions + globals) | grep |
| Annotations that match a function start in the function list | 6,862 | diff vs `function_names.db` |
| Function-list entries (excluding `Unwind@` funclets) | 12,780 | `function_names.db` |
| Game code range | `0x401000` – about `0x7DA100`. Everything above is MFC, the CRT, zlib and DirectPlay glue. **Do not translate that part.** | address distribution |
| Function-list entries in game range with no annotation | about 2,950. This includes thunks, compiler-generated destructors and SEH helpers, so the README's count of about 1,800 real functions is plausible. | diff |
| `// TODO: Incomplete.` markers | 371 across 69 files | grep |
| Biggest incomplete areas | CMessage (33), CGameSprite (32), CVidMode (20), CScreenCharacter (19), CInfGame (19), CStore (16), CVidCell (14), CScreenStore/Inventory (12 each), CDerivedStats (11), CScreenWorld (10) | grep |
| README status | Functions 80%, code bytes 53%. The game reaches the menus, party selection and character creation, but not the world screen. | `README.md` |

### Code conventions (follow them exactly)
- Each translated function or global gets a `// 0xADDR` comment directly above its definition in the `.cpp` (uppercase hex, no leading zeros beyond 6 digits, e.g. `// 0x4010C0`).
- Header members are annotated with their original offsets, `/* 05A0 */ CString m_sName;`, and vtable slots with `/* 0008 */`. Struct layout must match the original. Don't reorder or resize members, and fill gaps with `unknown`-style padding named the way the surrounding code already does it.
- Partial work is marked `// TODO: Incomplete.` (sometimes with a reason). Assertions use `UTIL_ASSERT` / `UTIL_ASSERT_MSG` with the original file/line strings when known.
- Commit style is one logical change per commit, titled `Add Class::Method`, `Complete Class ctor`, `Fix ...`. Copy the existing history.
- Formatting follows `.clang-format` / `.editorconfig`.

---

## 2. The environment you're working in

### Machine
- Windows 11, VS 2022 Community, MSVC 14.41.34120, Python 3.12 (`py`), git (Git Bash and PowerShell both available).
- **Missing right now:** the VS components *C++ MFC for v143 build tools (x86 & x64)* (there is no `atlmfc` folder) and *C++ CMake tools for Windows*. There is also no JDK, Ghidra or innoextract. Section 4 installs them.

### Game files: **the installed copy is modded and must not be your reference**
`C:\GOG Games\Icewind Dale II` is an install with several layers on top of the base game:
- `iwd2ee\`, `Setup-iwd2ee.exe`, `WeiDU.log`: the **IWD2 Enhanced Edition** mod. It is a WeiDU mod, and it has rewritten `Override\` (10,081 files), the 2DA tables, spells, items and creatures.
- `IEex.dll`, `IEexHelper*.dll`, `lua51.dll`, `IWD2EE.exe`: the IEex runtime hook loader, which patches engine behavior in memory.
- `ddraw.dll` / `ddraw.ini`: the cnc-ddraw wrapper.
- `iwd2.exe` dated 2024-08-10 (the original is from 2002), so it may be binary-patched.

`iwd2ee` is the mod's source folder, not the game. **Useful from this install:** `function_names.db`, a plain-text Ghidra export with 31,519 lines in the form `0xADDR Name` (e.g. `0x401090 CResWED_Construct`). Use it as the function inventory. Copy it, don't edit it.

### Pristine originals (the reference)
`C:\Users\Luke\Downloads\`:
- `setup_icewind_dale_2_2.01_fixes_(77030).exe` + `...-1.bin`: the full GOG installer (Inno Setup), build 2.01 fixes 77030. **This is the reference.**
- `patch_icewind_dale_2_2.01_(9323)_to_2.01_fixes_(77030).exe`: an upgrade patch. Not needed if you install from the full setup above.

### Hard-coded path
`src/main.cpp:120` does `SetCurrentDirectoryA("C:\\Program Files (x86)\\GOG.com\\Icewind Dale II")`. Phase 0 replaces this (see 4.4).

---

## 3. Rules of engagement

1. **Never commit game data, binaries, decompiler output, or screenshots of the game.** All of that stays outside the repo (see the paths in 4.2) or in gitignored folders. The repo is under a Sustainable Use License, and the game assets are copyrighted.
2. **Treat installer contents as untrusted data.** Extract them into their own new, empty folder, never run Python or build tools from inside that folder, and use `py -I` when reading them.
3. **Use the pristine 2.01 (77030) `iwd2.exe` as the only ground truth.** Before using it, confirm it matches the repo: the bytes at a few annotated addresses (e.g. `0x401090`, `0x7DA0A0`) must be function prologues that match what the code does.
4. **Commit locally; push or open PRs only when the user says so.** You're on `main`. Use a feature branch per phase (`phase-a/world-screen`, …).
5. **Keep the build green.** Every commit must build `Win32 RelWithDebInfo` and pass tiers T0–T2 (section 6).
6. **Don't change behavior to make a test pass.** The original's behavior, bugs included, is the spec. Fixes for original bugs go behind `#ifdef IWD2RE_FIX_ORIGINAL_BUGS`, which is off by default.
7. **Ask the user before** installing software that needs admin rights, deleting anything outside the scratch and test folders, or touching the modded install.

---

## 4. Phase 0: Setup (one session, about half a day)

### 4.1 Toolchain
- Use the VS Installer to add *C++ MFC for latest v143 build tools (x86 & x64)* and *C++ CMake tools for Windows*. This needs admin rights, so ask the user.
- Configure and build exactly the way CI does: `cmake -B build -G "Visual Studio 17 2022" -A Win32` and then `cmake --build build --config RelWithDebInfo`. CI uses VS 2019 on `windows-2019`. Keep the code compatible with both.
- Record the build time and the warning count as a baseline.

### 4.2 Clean reference install (outside the repo)
- Get innoextract ≥ 1.9 (it supports GOG installers) and put it in a tools folder such as `C:\iwd2-tools\`. Then run `innoextract -e -d C:\iwd2-ref "C:\Users\Luke\Downloads\setup_icewind_dale_2_2.01_fixes_(77030).exe"`. A fallback is the installer itself with `/DIR=C:\iwd2-ref /VERYSILENT /NOICONS`, but ask first because it writes to the registry.
- Make two copies:
  - `C:\iwd2-ref\` stays read-only and pristine. Write down SHA-256 hashes of `iwd2.exe`, `CHITIN.KEY` and `dialog.tlk` in `docs/reference-hashes.md`. That file **is** committed, since hashes aren't copyrighted.
  - `C:\iwd2-play\` is the working copy that tests run in. It needs `icewind2.ini` with `Full Screen=0` and `BitsPerPixel=32` (the reimpl only supports windowed 32-bpp), `Movies` skipped where possible, and `Cheats=1` for test setup. Rebuild it from `iwd2-ref` before each e2e run.
- Compare the hash of the modded `C:\GOG Games\...\iwd2.exe` with the pristine one and record whether it's patched. Never run tests against the modded install.

### 4.3 Disassembly and decompilation cache
- Install a JDK (Temurin 21) and Ghidra (11.x) under `C:\iwd2-tools\`.
- Run headless: import `C:\iwd2-ref\iwd2.exe`, then apply names from `function_names.db` with a small Ghidra script. Also apply the class and struct names that already exist in `src/` headers. A Python pass that turns the offset-annotated headers into Ghidra struct definitions is worth writing, because it makes the decompiler output far more readable.
- Export **per-function** files to `C:\iwd2-tools\decomp\0xADDR.{c,asm}`, plus `functions.json` holding `{addr, name, size, callers, callees, is_thunk, is_library}`. This is the material the translation loop reads. It never goes in the repo.

### 4.4 Repo tooling (committed)
- `tools/inventory.py` reads `functions.json` + `src/`, writes `docs/progress.json`, and prints:
  - functions translated / total (game range only, with thunks, SEH, `Unwind@` and library code excluded)
  - bytes translated / total (the README's "code" metric)
  - the `TODO: Incomplete` count per file
  - the top 50 untranslated functions **ranked by how many already-translated or critical-path functions call them**
- `tools/next.py --area <class|addr-range> --n 20` prints the next batch to work on.
- Replace the hard-coded game path with an env var `IWD2_GAME_DIR`, falling back to the exe's own folder and then the old path. This is a small change, so commit it on its own.
- Add `.gitignore` entries for `build*/`, `tests/e2e/out/` and `tests/e2e/golden/`.
- Restructure CMake: move everything except `main.cpp` into a static library `iwd2-core` so test executables can link it. Keep `iwd2-re.exe` building the same way it does today.

**Exit criteria:** a clean build, `inventory.py` numbers that roughly match the README, a pristine reference with its hashes recorded, the decomp cache present, and T0–T2 scaffolding in place (section 6).

---

## 5. The translation loop

### 5.1 Unit of work
Work on one class, or one cluster of functions that call each other, per batch, usually 5–30 functions. Pick the cluster with `tools/next.py`, and follow the phase order in section 7.

### 5.2 Per function
1. Read the decompiled `0xADDR.c` **and** the `.asm`. Decompilers get these wrong: `__thiscall` on virtual calls, 16-bit vs 32-bit fields, signed/unsigned compares, x87 float order, `CString` refcount helpers, and inlined `CArray`/`CObList` code.
2. Find every member offset it touches and map each one to an annotated member. If a header is missing a member, add it with its offset comment and check that the class size still matches the original (`sizeof` from the allocation size in the ctor caller, e.g. `operator new(0x3D4C)`).
3. Write idiomatic code in the style of the surrounding file: the original names where they're known (from asserts, strings and `function_names.db`), MFC types, and the original control flow. Don't optimize. Keep the original order of side effects.
4. Put `// 0xADDR` above the definition. Remove the matching `TODO: Incomplete.` when the function is complete. If it can't be finished, leave a specific TODO that says what's missing.
5. Build. Then run the cheapest test tier that covers the function (6.2).

### 5.3 Per batch
- T0 and T1 must pass, plus T2/T3 for anything in their scope. T4 shadow checks run for functions that are eligible (6.4).
- Make one commit per function or per small, coherent group, titled the way existing commits are.
- Update `docs/progress.json` (regenerate it, never hand-edit).
- Every 5 batches, run T5 smoke (S1–S3) to catch integration regressions early.

### 5.4 Parallelism (when the session uses subagents)
- Split work **by file or class** so two agents never edit the same `.cpp` at once. Use worktree isolation for each agent. Header edits are where conflicts happen, so give the parent session ownership of shared headers (`CGameSprite.h`, `CInfGame.h`, `BalDataTypes.h`, `FileFormat.h`). Agents request header changes and the parent applies them.
- Each agent gets the class's decomp files, the relevant headers, these conventions (1, 5.2), and the rule that **it must build before it reports back**. The parent session reviews the diff against the `.asm` and then merges.
- About 4 agents in parallel is a good number. Integration and the linker are the bottleneck.

---

## 6. Test hierarchy

Each tier is slower and closer to real play than the one before it. Lower tiers gate every commit; higher tiers gate phases.

| Tier | What it proves | Speed | When it runs |
|---|---|---|---|
| T0 Build | Compiles and links on Win32 with no new warnings | min | every commit (CI) |
| T1 Static and inventory | Annotations are valid, layouts are consistent, progress only goes up | sec | every commit (CI) |
| T2 Unit | Pure logic is correct in isolation | sec | every commit (CI) |
| T3 Resource conformance | Every game file in the real data parses and loads the way the original does | min | every batch that touches parsing or loading; nightly |
| T4 Differential vs original exe | Each function behaves the same as the original, checked inside the running original game | min | per eligible function; phase gate |
| T5 Scripted human-style play | The game plays through real mouse and keyboard input; state and screenshots match the original | 10s of min | every 5 batches (smoke); phase gate (full) |
| T6 Exploratory and soak | Unscripted play by an agent, plus long autoplay, finds crashes and divergences | hours | end of phase |
| T7 Full playthrough | The whole campaign is completable | days | final milestone |

Tests that need game data read `IWD2_REF_DIR` (`C:\iwd2-ref`) and `IWD2_PLAY_DIR` (`C:\iwd2-play`) and **skip with a clear message** when those aren't set, so CI without the game still passes.

### 6.1 T0: Build
- The existing CI workflow, plus a local `tools/check.ps1` that builds RelWithDebInfo and Debug for Win32 and fails if the warning count goes up from the Phase 0 baseline.

### 6.2 T1: Static and inventory checks (`tools/inventory.py --check`)
- Every `// 0xADDR` is either a function start in `functions.json` or a known global or data address. No duplicates, and nothing above the game-code range.
- Annotated header offsets go up strictly, and the gaps match member sizes. Add `static_assert(offsetof(...) == 0x...)` and `static_assert(sizeof(...) == 0x...)` generation for the classes in the critical path. The repo has no layout asserts yet, so this is a cheap way to catch a whole class of bugs.
- Ratchet: functions translated must not go down, and the `TODO: Incomplete` count must not go up.

### 6.3 T2: Unit tests (`tests/unit`, GoogleTest or doctest vendored in `third_party/`)
- Executable `iwd2-tests.exe` linking `iwd2-core`.
- Targets: `C2DArray` lookups, `CRuleTables` (THAC0/BAB, saves, XP levels, dice), `CDerivedStats` math, `CAIScript`/`CAITrigger`/`CAIAction` parsing, `CAIObjectType` matching, `CCrypt`, `CResRef`, string and `CUtil` helpers, `CSearchBitmap`/`CPathSearch` on small hand-built maps, and effect opcode application on a stubbed sprite.
- Expected values come from the original, not from what the new code happens to return. Get them from T4 captures or from hand-traced asm. Never write "golden" values by running the new code.

### 6.4 T3: Resource conformance (`tests/resources`, needs `IWD2_REF_DIR`)
- Enumerate **every** resource in `CHITIN.KEY` plus `override/`, then load and parse each through the reimpl's `CRes*` classes. Nothing may crash, assert or leak.
- Compare fields against an independent Python reader of IESDP formats (`tools/iesdp/*.py`). Formats: KEY/BIFF, TLK, 2DA, IDS, BCS, DLG, CRE, ITM, SPL, EFF, ARE, WED, TIS, MOS, BAM, PLT, CHU, WMP, STO, PRO, VVC, GAM. The reimpl gets a `--dump-resource <type> <resref>` test entry point that prints JSON.
- Round-trips: BCS compile and decompile is byte-identical for every script. Writing GAM/CRE out of a loaded save is byte-identical to the input.
- Load each area (ARE + WED + TIS + search map) headlessly through `CGameArea` init, with no rendering.

### 6.5 T4: Differential testing against the original exe (`tools/hook/`)
This is the highest-value tier while the reimpl can't reach the world screen yet. It runs translated functions **inside the working original game**.

- Build `iwd2re-hook.dll` from `iwd2-core` (same sources) plus a small detour layer, and a launcher `iwd2re-launch.exe` that starts the pristine `iwd2.exe` suspended in `C:\iwd2-play`, injects the DLL, and resumes it.
- Modes, chosen per function in a config file:
  - **Shadow:** call the original, snapshot the inputs and `this` first, call the reimpl on a clone, and compare return value + touched memory. Log mismatches with a minidump. Good for pure or mostly pure functions: rules, stats, scripting conditions, parsing.
  - **Replace:** route all calls to the reimpl, then play normally (T5/T6 on the original exe). This proves the function in real context.
- **ABI hazards, which the Phase 0/A spike must solve or work around before scaling up:**
  - **Heaps:** the original links its own CRT and MFC (MFC 4.2 era). In the hook build, route `operator new/delete`, `malloc/free` and MFC allocations to the original's allocator addresses.
  - **`CString`:** MFC 4.2's `CStringData` layout (`nRefs, nDataLength, nAllocLength`) is **different** from MSVC 2022's ATL `CStringT`. The hook build needs a binary-compatible `CString` shim, or else functions that create or destroy `CString`s stay shadow-only with deep-compare.
  - `CObList`/`CPtrList`/`CArray` node layouts are fine if the shim allocator is used. Vtables are fine as long as header slot annotations are correct (they're checked here for free).
  - Floating point: compile the hook build with `/arch:IA32` and the x87 behavior the original used, or allow ULP tolerance and log it.
- **Spike gate:** get 20 varied functions working in shadow and replace mode. If the `CString` and heap problems are still unsolved after about one session, drop T4 to "shadow for POD-only functions" and lean on T3/T5.
- **Determinism hooks** (also used by T5): fix the CRT `rand()` seed and virtualize `timeGetTime`/`GetTickCount` so game ticks step in lockstep with the harness.

### 6.6 T5: Scripted human-style play (`tests/e2e/`, Python, run on the interactive desktop)
This plays the game the way a person does. It sends real window input, has no backdoor for actions, and asserts on what a player could see, plus an internal state probe.

**Harness (`tests/e2e/harness/`)**
- `game.py`: launches either target (`--target original` = pristine exe via `iwd2re-launch` with determinism hooks; `--target reimpl` = `iwd2-re.exe` with `--deterministic`), waits for the window, puts it at a fixed position at 800×600, and kills it on teardown or timeout. It also watches for crashes, asserts and hangs (no frame change for N seconds while unpaused).
- `input.py`: `SendInput` mouse and keyboard with human-like motion. That means curved paths, 80–250 ms dwell times, real key down and up, and drag-and-drop with intermediate moves. Coordinates are window-relative. Avoid instant teleport clicks, because hover states, tooltips and drag thresholds are part of what's being tested.
- `screen.py`: captures the client area (PrintWindow or DXGI), masks animated regions, compares perceptually (SSIM ≥ threshold) and does template matching on UI anchors.
- `probe.py`: reads game state for assertions. The current screen/engine, area resref, party list with name, HP, XP, gold, position, selected and action, the open panel, the pause state and the game tick. The reimpl exposes this through a named pipe in test builds. The original exposes the *same JSON shape* through `iwd2re-hook.dll`, which reads known globals (`g_pBaldurChitin` → `m_pObjectGame` …). Asserting on the probe keeps tests robust. Screenshots are a secondary check.
- `vision.py` (optional): UI anchor templates are captured from **original** runs into gitignored `tests/e2e/golden/`.
- **Ground truth:** run each scenario against `original` first to record golden probe traces and screenshots locally. Then run `reimpl` and diff. Traces are compared at checkpoints, which are game ticks where the scenario pauses (Space).
- Input automation needs the foreground desktop. Run scenarios **one at a time**, don't touch the mouse while they run, and use a Windows Sandbox or VM if the user wants their desktop free.

**Scenarios (`tests/e2e/scenarios/`), roughly in the order the reimpl will be able to pass them**

| ID | Scenario | Key assertions |
|---|---|---|
| S1 | Boot, main menu, Options (change gamma, sound, keymap, back), Quit | No crash, menus render, ini changes persist |
| S2 | New game, pick a pregenerated party, create one custom character (race, class, abilities, skills, feats, portrait, name), start | Character stats from the probe match the original for identical choices |
| S3 | Chapter intro and movie skip, arrive at the first area (Targos docks) | Area resref, party spawn positions, ambient sounds start, world screen renders |
| S4 | Select individual and all, click-to-move, formation change, pause/unpause, scroll the map with keys and the screen edge | Positions after N ticks match the original within tolerance, and pathing goes around obstacles |
| S5 | Talk to the first NPC on the docks: open dialogue, choose responses, end | Dialogue text, the shown response set and journal and variable changes match |
| S6 | First goblin fight: attack, cast a spell, use a quick item, let a character die or be revived | Combat log, damage and XP match under a fixed seed, and the creature death sequence plays |
| S7 | Loot a container or corpse, inventory drag-drop, equip and unequip, ground pile, quick slots | Inventory contents and weight, AC/BAB changes |
| S8 | Rest, memorize spells, level up through the character record | Spell slots and level-up stats match |
| S9 | Store buy and sell, journal, area map, world map travel to a second area | Gold, item lists, area transition, fog of war |
| S10 | Quick save, quit to menu, load, compare | The GAM/ARE/CRE in the save match before and after. The reimpl save is also loadable by the **original** exe and the reverse. |
| S11 | Load a library of reference saves (made by playing the original, at least one per chapter and per major area), pan the camera, open each screen | Each loads without crash, and screenshots and probe match the original |

S1–S2 are already achievable (the README says those screens work). Use them as T5 bring-up tests in Phase 0/A.

### 6.7 T6: Exploratory play and soak
- **Agent playtester:** a session (or subagent) with harness tools (`screenshot`, `click`, `drag`, `key`, `probe`) gets player-level goals, for example "clear the Targos docks and reach the palisade", "finish a full rest cycle", or "sell all loot". It plays with no script and files each problem as a markdown bug report in `tests/e2e/out/bugs/`. Each report has steps, the probe trace and screenshots, and a note on whether the original does the same thing under the same seed. Run it on both targets so differences stand out.
- **Soak:** party AI scripts on, random but valid commands (move, attack the nearest enemy, rest, area transitions) for 2–8 hours. Watch for asserts, crashes, memory growth (private bytes sampled every minute) and frame-time spikes.
- **Monkey UI:** random clicks and keys confined to the current panel for 30 min per screen. Look for crashes or stuck UI states.

### 6.8 T7: Full playthrough
- A per-chapter checklist (prologue through chapter 6 and the ending), played mainly by the agent playtester using reference saves to skip ahead, plus a manual pass by the user. The checklist lives in `docs/playthrough.md`.

---

## 7. Phase order and exit criteria

Work in the order that unlocks playability, because each phase makes the higher test tiers usable.

**Phase 0: Setup** (section 4). Exit: as listed in 4.4.

**Phase A: Reach the world screen.** Finish the incomplete parts and missing callees on the path New Game → load area → render world → move party:
`CInfGame` (new game, area load and save), `CGameArea` (load, AIUpdate, Render), `CScreenWorld`, `CInfinity` and `CVidMode`/`CVidCell` rendering (20 + 14 TODOs), `CGameSprite` core (AIUpdate, movement, animation, the rest of `ResolveInstants`), `CSearchBitmap`/`CPathSearch`, `CMessage` handlers used in single player (33 TODOs; SP still routes through messages), and `CGameAnimationType*` used by the pregen party.
Also do the T4 spike in this phase.
Exit: S1–S4 pass on reimpl, S3/S4 probe traces match the original, and T3 area loading passes for all areas.

**Phase B: Core gameplay.** Combat, effects (all `CGameEffect` opcodes), spells, scripting actions and triggers, dialogue, `CDerivedStats`, containers and items, inventory, character record, level up, rest.
Exit: S5–S8 pass and match. T4 shadow-clean for the rules, stats and opcode functions.

**Phase C: The rest of the screens and systems.** Stores (`CStore`/`CScreenStore`), journal, maps, world map, save and load, chapter screens, movies, projectiles, visibility and fog, sounds and music edge cases.
Exit: S9–S11 pass, and saves are compatible both ways with the original.

**Phase D: The long tail.** Every remaining function in the game range: multiplayer and DirectPlay (`CMessage`, `CScreenMultiPlayer`, `CNetwork`), unused debug paths, error paths, remaining `TODO: Incomplete`.
Exit: `inventory.py` reports 100% of game-range functions with no `TODO: Incomplete`. Library and CRT exclusions are listed explicitly in `tools/inventory_exclusions.txt`, with a reason for each.

**Phase E: Verification.** A 4-hour T6 soak with no crashes, T7 playthrough complete, and the README status updated.

### Session hygiene
- Start each session by running `tools/inventory.py` and reading `docs/progress.json` plus the last 20 commits. End each session by updating `docs/session-log.md` with what was done, what's blocked, and the next batch.
- When a function's behavior is unclear, check the original under a debugger (x32dbg attached to the pristine exe in `C:\iwd2-play`) before guessing. Record what you find as a short code comment only if it isn't obvious from the code.
- Report outcomes honestly in the session log, including failing tiers, skipped scenarios and any function that was translated but not verified above T0.
