"""Golden screenshot checkpoints.

The original game records each checkpoint into tests/e2e/golden/<test>/.
The rebuild must then match it within tolerance."""

from __future__ import annotations

from pathlib import Path

from PIL import Image

from harness.screen import diff_ratio


def checkpoint(game, golden_dir: Path, name: str, max_diff: float = 0.02, mask=None, settle: float = 1.0,
               region=None, timeout: float = 30.0):
    """Wait for the screen (or `region`, x/y/w/h) to settle, save it, and
    compare it to the original's golden image of the same checkpoint."""
    img = game.wait_stable(settle=settle, region=region, timeout=timeout)
    game.shots += 1
    img.save(game.out_dir / f"{game.shots:03d}-{name}.png")
    golden = golden_dir / f"{name}.png"
    if game.target == "original":
        img.save(golden)
        return img
    if not golden.exists():
        raise AssertionError(f"no golden image {golden}; run with --target original first")
    ref = Image.open(golden)
    d = diff_ratio(ref, img, region=region)
    if mask:
        from harness.screen import similar
        ok = similar(ref, img, max_diff=max_diff, mask=mask, region=region)
    else:
        ok = d <= max_diff
    assert ok, f"checkpoint {name}: {d:.1%} of pixels differ from the original (limit {max_diff:.1%})"
    return img
