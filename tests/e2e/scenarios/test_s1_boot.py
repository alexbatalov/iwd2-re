"""S1: boot to the main menu, look around, quit.

Coordinates are client-area pixels at 800x600 and were read off screenshots
of the original game."""

from __future__ import annotations

import time

from harness.screen import diff_ratio, mostly_black
from checkpoints import checkpoint

# Main menu buttons (centre points), from the original at 800x600.
MAIN_MENU = {
    "game_mode": (645, 143),
    "new_game": (645, 262),
    "load_game": (645, 294),
    "options": (645, 410),
    "quit_game": (645, 442),
}


def boot_to_main_menu(game, timeout: float = 90.0, stable_for: float = 3.0):
    """Skip logos and the intro movie like a player (Esc while a movie plays),
    then wait for a static, non-black screen: the main menu."""
    deadline = time.time() + timeout
    prev = game.grab()
    stable_since = time.time()
    last_esc = 0.0
    while time.time() < deadline:
        time.sleep(0.5)
        cur = game.grab()
        if diff_ratio(prev, cur) > 0.01:
            stable_since = time.time()
            if time.time() - last_esc > 2.5:
                game.press("esc")
                last_esc = time.time()
        elif time.time() - stable_since >= stable_for and not mostly_black(cur):
            return cur
        prev = cur
    raise TimeoutError("never reached a static main menu")


def test_s1_boot_to_main_menu(game, golden_dir):
    x, y, w, h = game.client_rect()
    assert (w, h) == (800, 600), f"expected an 800x600 window, got {w}x{h}"

    boot_to_main_menu(game)
    checkpoint(game, golden_dir, "main-menu")

    game.click(*MAIN_MENU["options"])
    checkpoint(game, golden_dir, "options")
