"""Exploration driver: boot a target to the main menu, run a list of actions,
and save a screenshot after each one. Used to map out screens and button
coordinates before turning a path into a scenario.

  C:\\iwd2-tools\\venv\\Scripts\\python tests/e2e/drive.py --target original --out OUT \\
      click:645,262 wait:2 shot:after-new-game key:esc

Actions:
  click:X,Y   rclick:X,Y   dclick:X,Y   drag:X0,Y0,X1,Y1   move:X,Y
  key:NAME    type:TEXT    wait:SECONDS shot:NAME          settle
"""

from __future__ import annotations

import argparse
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
sys.path.insert(0, str(Path(__file__).resolve().parent / "scenarios"))

from harness.game import Game  # noqa: E402
from test_s1_boot import boot_to_main_menu  # noqa: E402


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--target", default="original", choices=["original", "reimpl"])
    ap.add_argument("--play-dir", default=r"C:\iwd2-play")
    ap.add_argument("--out", required=True)
    ap.add_argument("--no-boot", action="store_true", help="don't wait for the main menu first")
    ap.add_argument("actions", nargs="*")
    args = ap.parse_args()

    out = Path(args.out)
    g = Game(target=args.target, play_dir=Path(args.play_dir), out_dir=out)
    g.launch()
    try:
        if not args.no_boot:
            boot_to_main_menu(g)
        g.screenshot("start")
        for i, a in enumerate(args.actions):
            kind, _, arg = a.partition(":")
            nums = [int(v) for v in arg.split(",")] if kind in ("click", "rclick", "dclick", "drag", "move") else []
            if kind == "click":
                g.click(*nums)
            elif kind == "rclick":
                g.click(*nums, button="right")
            elif kind == "dclick":
                g.double_click(*nums)
            elif kind == "drag":
                g.drag(*nums)
            elif kind == "move":
                g.move(*nums)
            elif kind == "key":
                g.press(arg)
            elif kind == "type":
                g.type_text(arg)
            elif kind == "wait":
                time.sleep(float(arg))
            elif kind == "settle":
                g.wait_stable(settle=1.0, timeout=30)
            elif kind == "shot":
                g.screenshot(arg)
                continue
            else:
                raise SystemExit(f"unknown action {a}")
            time.sleep(0.8)
            g.screenshot(f"{i:02d}-{kind}")
        print(f"ok, screenshots in {out}")
        return 0
    except Exception as e:
        print(f"FAILED: {e}")
        try:
            g.screenshot("error")
        except Exception:
            pass
        return 1
    finally:
        g.close()


if __name__ == "__main__":
    sys.exit(main())
