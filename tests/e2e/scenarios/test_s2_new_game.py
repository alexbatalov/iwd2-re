"""S2/S3: start a new game with a premade party and arrive in the world.

Path (original, 800x600): main menu -> New Game -> Select Party ->
"Lady's Lament" -> Done -> loading -> Prologue chapter screen -> Done ->
world screen at Targos with Hedron's opening dialogue."""

from __future__ import annotations

import time

from harness.screen import diff_ratio
from checkpoints import checkpoint
from test_s1_boot import MAIN_MENU, boot_to_main_menu

SELECT_PARTY = {
    "new_party": (124, 149),
    "ladys_lament": (124, 211),
    "done": (537, 562),
    "cancel": (398, 562),
}
CHAPTER_DONE = (514, 548)
# Bottom panel during dialogue: speaker portrait and text area.
DIALOG_REGION = (0, 318, 800, 282)
CHAPTER_TITLE_REGION = (170, 30, 460, 40)


def wait_region_changes(game, region, timeout: float, threshold: float = 0.2):
    """Wait until `region` changes a lot compared with now (a new screen)."""
    before = game.grab()
    deadline = time.time() + timeout
    while time.time() < deadline:
        time.sleep(0.5)
        cur = game.grab()
        if diff_ratio(before, cur, region=region) > threshold:
            return cur
    raise TimeoutError(f"region {region} never changed")


def test_s2_new_game_premade_party(game, golden_dir):
    boot_to_main_menu(game)

    game.click(*MAIN_MENU["new_game"])
    checkpoint(game, golden_dir, "select-party")

    game.click(*SELECT_PARTY["ladys_lament"])
    checkpoint(game, golden_dir, "select-party-ladys-lament")

    game.click(*SELECT_PARTY["done"])
    # The loading screen ("Starting Game...") shows a random hint, so don't
    # compare it. Wait for its title to give way to the Prologue chapter
    # screen, and compare only that title (the story text scrolls).
    time.sleep(1.5)
    wait_region_changes(game, CHAPTER_TITLE_REGION, timeout=120)
    checkpoint(game, golden_dir, "prologue-title", region=CHAPTER_TITLE_REGION, settle=2.0)

    game.click(*CHAPTER_DONE)
    wait_region_changes(game, DIALOG_REGION, timeout=120)
    # The world animates (water, people), so compare only the dialogue panel.
    checkpoint(game, golden_dir, "targos-opening-dialog", region=DIALOG_REGION, timeout=90, settle=2.0)
