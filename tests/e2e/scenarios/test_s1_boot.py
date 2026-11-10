"""S1: boot to the main menu, look around, quit.

Coordinates are client-area pixels at 800x600 and were read off screenshots
of the original game."""

from __future__ import annotations

from harness.screen import mostly_black
from checkpoints import checkpoint


def skip_movies(game, presses: int = 6):
    # Logos and the intro movie: Esc skips each one, the way a player would.
    for _ in range(presses):
        game.press("esc")
        game.wait_stable(settle=0.8, timeout=20)


def test_s1_boot_to_main_menu(game, golden_dir):
    x, y, w, h = game.client_rect()
    assert (w, h) == (800, 600), f"expected an 800x600 window, got {w}x{h}"

    skip_movies(game)
    menu = checkpoint(game, golden_dir, "main-menu", settle=2.0)
    assert not mostly_black(menu), "main menu is black"
