"""pytest setup for T5 scripted play.

Run from the repo root with the harness venv:
  C:\\iwd2-tools\\venv\\Scripts\\python -m pytest tests/e2e --target original
  C:\\iwd2-tools\\venv\\Scripts\\python -m pytest tests/e2e --target reimpl

These tests take over the real mouse and keyboard. Don't touch them while a
run is going. Run the original first: its screenshots become the reference
for the reimpl run (tests/e2e/golden/, gitignored).
"""

from __future__ import annotations

import os
import time
from pathlib import Path

import pytest

from harness.game import Game

E2E = Path(__file__).resolve().parent


def pytest_addoption(parser):
    parser.addoption("--target", default="original", choices=["original", "reimpl"])
    parser.addoption("--play-dir", default=os.environ.get("IWD2_PLAY_DIR", r"C:\iwd2-play"))
    parser.addoption("--exe", default=None, help="override the exe to launch")


@pytest.fixture(scope="session")
def target(request) -> str:
    return request.config.getoption("--target")


@pytest.fixture(scope="session")
def play_dir(request) -> Path:
    p = Path(request.config.getoption("--play-dir"))
    if not (p / "CHITIN.KEY").exists():
        pytest.skip(f"no game in {p}; run tools/make_play_dir.ps1")
    return p


@pytest.fixture
def out_dir(request, target) -> Path:
    stamp = time.strftime("%Y%m%d-%H%M%S")
    d = E2E / "out" / f"{stamp}-{target}-{request.node.name}"
    d.mkdir(parents=True, exist_ok=True)
    return d


@pytest.fixture
def golden_dir(request) -> Path:
    d = E2E / "golden" / request.node.name
    d.mkdir(parents=True, exist_ok=True)
    return d


@pytest.hookimpl(hookwrapper=True)
def pytest_runtest_makereport(item, call):
    outcome = yield
    rep = outcome.get_result()
    setattr(item, "rep_" + rep.when, rep)


@pytest.fixture
def game(request, target, play_dir, out_dir):
    exe = request.config.getoption("--exe")
    g = Game(target=target, play_dir=play_dir, out_dir=out_dir, exe=Path(exe) if exe else None)
    g.launch()
    try:
        yield g
        rep = getattr(request.node, "rep_call", None)
        if rep is not None and rep.failed:
            try:
                g.screenshot("failure")
            except Exception:
                g.screenshot_desktop("failure")
    finally:
        g.close()
