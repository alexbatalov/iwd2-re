#!/usr/bin/env python3
"""Translation progress inventory for iwd2-re.

Compares `// 0xADDR` annotations in src/ against the function list of the
original iwd2.exe and reports what is left.

Function list sources, best first:
  1. functions.json exported by tools/ghidra/ExportFunctions.java
     (has sizes, thunk/library flags and call graph)
  2. function_names.db (plain text "0xADDR Name", Ghidra export shipped with IEex)

Both live outside the repo. Point at them with IWD2_TOOLS_DIR (default
C:\\iwd2-tools) or --functions.

Usage:
  py -I tools/inventory.py            # print summary
  py -I tools/inventory.py --write    # also write docs/progress.json
  py -I tools/inventory.py --check    # CI ratchet: fail if progress regressed
"""

from __future__ import annotations

import argparse
import json
import os
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
SRC = REPO / "src"
PROGRESS = REPO / "docs" / "progress.json"
EXCLUSIONS = REPO / "tools" / "inventory_exclusions.txt"

# Game code starts at the beginning of .text. The end is where statically
# linked library code (MFC, CRT) begins. Refined from Ghidra analysis; see
# docs/session-log.md.
GAME_START = 0x401000
GAME_END = 0x7DA200

ANNOTATION = re.compile(r"^// (0x[0-9A-F]+)\s*$", re.M)
INCOMPLETE = re.compile(r"TODO: Incomplete")
# Names that are compiler or tool artifacts, never written by hand.
ARTIFACT_NAME = re.compile(r"^(Unwind@|SEH_|switchD|caseD|thunk_|nullsub)")


def tools_dir() -> Path:
    return Path(os.environ.get("IWD2_TOOLS_DIR", r"C:\iwd2-tools"))


def load_functions(path: Path | None) -> tuple[list[dict], str]:
    candidates = [path] if path else [tools_dir() / "functions.json", tools_dir() / "function_names.db"]
    for p in candidates:
        if p and p.exists():
            if p.suffix == ".json":
                data = json.loads(p.read_text(encoding="utf-8"))
                for f in data:
                    f["addr"] = int(f["addr"], 16) if isinstance(f["addr"], str) else f["addr"]
                return data, str(p)
            funcs = []
            for line in p.read_text(encoding="utf-8", errors="replace").splitlines():
                parts = line.split(None, 1)
                if len(parts) == 2 and parts[0].startswith("0x"):
                    funcs.append({"addr": int(parts[0], 16), "name": parts[1].strip()})
            return funcs, str(p)
    sys.exit(f"error: no function list found (tried {', '.join(str(c) for c in candidates)})")


def load_exclusions() -> set[int]:
    out = set()
    if EXCLUSIONS.exists():
        for line in EXCLUSIONS.read_text(encoding="utf-8").splitlines():
            line = line.split("#", 1)[0].strip()
            if line:
                out.add(int(line.split()[0], 16))
    return out


def scan_source() -> tuple[dict[int, list[str]], Counter]:
    annotations: dict[int, list[str]] = defaultdict(list)
    incomplete: Counter = Counter()
    for p in sorted(SRC.rglob("*")):
        if p.suffix not in (".cpp", ".h"):
            continue
        text = p.read_text(encoding="utf-8", errors="replace")
        rel = p.relative_to(REPO).as_posix()
        for m in ANNOTATION.finditer(text):
            annotations[int(m.group(1), 16)].append(rel)
        n = len(INCOMPLETE.findall(text))
        if n:
            incomplete[rel] = n
    return annotations, incomplete


def is_countable(f: dict, exclusions: set[int]) -> bool:
    if not (GAME_START <= f["addr"] < GAME_END):
        return False
    if f["addr"] in exclusions:
        return False
    if ARTIFACT_NAME.match(f.get("name", "")):
        return False
    if f.get("is_thunk") or f.get("is_library"):
        return False
    return True


def build_report(funcs: list[dict], source: str) -> dict:
    annotations, incomplete = scan_source()
    exclusions = load_exclusions()
    countable = [f for f in funcs if is_countable(f, exclusions)]
    done = [f for f in countable if f["addr"] in annotations]
    todo = [f for f in countable if f["addr"] not in annotations]
    has_size = all("size" in f for f in countable)

    by_addr = {f["addr"]: f for f in funcs}
    duplicates = {hex(a).upper().replace("0X", "0x"): files for a, files in annotations.items() if len(files) > 1}
    beyond = sorted(a for a in annotations if a >= GAME_END)

    # Rank untranslated functions: callers that are already translated make a
    # function urgent (translated code calls it, so the build or game needs it).
    ranked = []
    if funcs and "callers" in funcs[0]:
        done_set = {f["addr"] for f in done}
        for f in todo:
            callers = [int(c, 16) if isinstance(c, str) else c for c in f.get("callers", [])]
            ranked.append((sum(1 for c in callers if c in done_set), f))
        ranked.sort(key=lambda t: (-t[0], t[1]["addr"]))
    else:
        ranked = [(0, f) for f in todo]

    report = {
        "function_list": Path(source).name,
        "game_range": [f"0x{GAME_START:X}", f"0x{GAME_END:X}"],
        "functions_total": len(countable),
        "functions_done": len(done),
        "incomplete_markers": sum(incomplete.values()),
        "incomplete_by_file": dict(incomplete.most_common()),
        "annotations_total": len(annotations),
        "annotations_not_function_start": sum(1 for a in annotations if a not in by_addr),
        "duplicate_annotations": duplicates,
        "annotations_beyond_game_range": [f"0x{a:X}" for a in beyond],
    }
    if has_size:
        report["bytes_total"] = sum(f["size"] for f in countable)
        report["bytes_done"] = sum(f["size"] for f in done)
    report["next"] = [
        {"addr": f"0x{f['addr']:X}", "name": f.get("name", ""), "translated_callers": n, **({"size": f["size"]} if "size" in f else {})}
        for n, f in ranked[:50]
    ]
    return report


def print_report(r: dict) -> None:
    pct = 100.0 * r["functions_done"] / max(1, r["functions_total"])
    print(f"function list: {r['function_list']}  game range {r['game_range'][0]}-{r['game_range'][1]}")
    print(f"functions: {r['functions_done']}/{r['functions_total']} ({pct:.1f}%)")
    if "bytes_total" in r:
        print(f"bytes:     {r['bytes_done']}/{r['bytes_total']} ({100.0 * r['bytes_done'] / max(1, r['bytes_total']):.1f}%)")
    print(f"TODO: Incomplete markers: {r['incomplete_markers']}")
    for f, n in list(r["incomplete_by_file"].items())[:10]:
        print(f"  {n:4} {f}")
    print(f"annotations: {r['annotations_total']} ({r['annotations_not_function_start']} not a function start, e.g. globals)")
    if r["duplicate_annotations"]:
        # Expected: the linker folds identical functions (e.g. empty virtuals)
        # into one address, so several methods share an annotation.
        print(f"shared annotations (identical-code folding): {len(r['duplicate_annotations'])}")
    if r["annotations_beyond_game_range"]:
        print(f"annotations beyond game range: {len(r['annotations_beyond_game_range'])}")
    print("next (most-needed untranslated):")
    for n in r["next"][:15]:
        print(f"  {n['addr']} {n['name']}  callers-done={n['translated_callers']}" + (f" size={n['size']}" if "size" in n else ""))


def check(r: dict) -> int:
    if not PROGRESS.exists():
        print("no docs/progress.json baseline; nothing to compare")
        return 0
    base = json.loads(PROGRESS.read_text(encoding="utf-8"))
    errors = []
    if base.get("function_list") == r["function_list"] and r["functions_done"] < base["functions_done"]:
        errors.append(f"functions_done dropped {base['functions_done']} -> {r['functions_done']}")
    # New stubs for functions that weren't in src before are fine (they come
    # with new annotations), so only fail if TODOs grew without new functions.
    grew = r["incomplete_markers"] - base["incomplete_markers"]
    added = r["functions_done"] - base["functions_done"] if base.get("function_list") == r["function_list"] else 0
    if grew > 0 and added < grew:
        errors.append(f"TODO: Incomplete grew {base['incomplete_markers']} -> {r['incomplete_markers']} "
                      f"with only {added} new functions")
    new_dups = set(r["duplicate_annotations"]) - set(base.get("duplicate_annotations", {}))
    if new_dups:
        errors.append(f"new duplicate annotations: {sorted(new_dups)}")
    for e in errors:
        print("FAIL:", e)
    if not errors:
        print("inventory check OK")
    return 1 if errors else 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--functions", type=Path, help="functions.json or function_names.db")
    ap.add_argument("--write", action="store_true", help="write docs/progress.json")
    ap.add_argument("--check", action="store_true", help="fail if progress regressed vs docs/progress.json")
    ap.add_argument("--json", action="store_true", help="print the report as JSON")
    args = ap.parse_args()

    funcs, source = load_functions(args.functions)
    r = build_report(funcs, source)
    if args.json:
        print(json.dumps(r, indent=2))
    else:
        print_report(r)
    rc = check(r) if args.check else 0
    if args.write:
        PROGRESS.write_text(json.dumps(r, indent=2) + "\n", encoding="utf-8")
        print(f"wrote {PROGRESS.relative_to(REPO)}")
    return rc


if __name__ == "__main__":
    sys.exit(main())
