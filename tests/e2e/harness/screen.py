"""Image comparison helpers for screenshots."""

from __future__ import annotations

import numpy as np


def _arr(img, region=None):
    a = np.asarray(img.convert("RGB"), dtype=np.int16)
    if region:
        x, y, w, h = region
        a = a[y:y + h, x:x + w]
    return a


def diff_ratio(a, b, region=None, tolerance: int = 24) -> float:
    """Fraction of pixels that differ by more than `tolerance` in any channel."""
    x, y = _arr(a, region), _arr(b, region)
    if x.shape != y.shape:
        return 1.0
    return float((np.abs(x - y).max(axis=2) > tolerance).mean())


def similar(a, b, max_diff: float = 0.01, region=None, mask=None) -> bool:
    """True if images match within `max_diff` (fraction of differing pixels).
    `mask` is a list of (x, y, w, h) rectangles to ignore (animations, cursor)."""
    x, y = _arr(a, region), _arr(b, region)
    if x.shape != y.shape:
        return False
    d = np.abs(x - y).max(axis=2) > 24
    for mx, my, mw, mh in mask or []:
        d[my:my + mh, mx:mx + mw] = False
    return float(d.mean()) <= max_diff


def mostly_black(img, threshold: float = 0.98) -> bool:
    a = _arr(img)
    return float((a.max(axis=2) < 16).mean()) >= threshold
