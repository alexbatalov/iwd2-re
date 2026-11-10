#!/usr/bin/env python3
"""Read strings, numbers and bytes from the original iwd2.exe by address.

  py -I tools/peek.py s 0x8B0B4C 0x8B019C      # C strings
  py -I tools/peek.py d 0x8A6478 4             # 4 dwords
  py -I tools/peek.py w 0x851884 8             # 8 words
  py -I tools/peek.py b 0x8C5CF8 16            # 16 bytes
  py -I tools/peek.py f 0x847A30 2             # 2 floats;  F = doubles
  py -I tools/peek.py name 0x5A0F50            # function name from functions.json

The exe comes from IWD2_REF_DIR (default C:\\iwd2-ref).
"""

from __future__ import annotations

import json
import os
import struct
import sys
from pathlib import Path


def load_pe(path: Path):
    d = path.read_bytes()
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    nsec = struct.unpack_from("<H", d, pe + 6)[0]
    opt = struct.unpack_from("<H", d, pe + 20)[0]
    base = struct.unpack_from("<I", d, pe + 24 + 28)[0]
    secs = []
    for i in range(nsec):
        o = pe + 24 + opt + 40 * i
        name = d[o:o + 8].rstrip(b"\0").decode()
        vsz, va, rsz, raw = struct.unpack_from("<IIII", d, o + 8)
        secs.append((name, base + va, vsz, raw, rsz))
    return d, secs


def read(d, secs, addr: int, n: int) -> bytes:
    for _, va, vsz, raw, rsz in secs:
        if va <= addr < va + max(vsz, rsz):
            off = addr - va
            chunk = d[raw + off: raw + min(rsz, off + n)] if off < rsz else b""
            return chunk + b"\0" * (n - len(chunk))  # .bss reads as zero
    raise SystemExit(f"0x{addr:X} is not in any section")


def main() -> int:
    if len(sys.argv) < 3:
        print(__doc__)
        return 1
    kind, args = sys.argv[1], sys.argv[2:]
    ref = Path(os.environ.get("IWD2_REF_DIR", r"C:\iwd2-ref"))
    if kind == "name":
        tools = Path(os.environ.get("IWD2_TOOLS_DIR", r"C:\iwd2-tools"))
        funcs = {int(f["addr"], 16): f for f in json.loads((tools / "functions.json").read_text(encoding="utf-8"))}
        for a in args:
            f = funcs.get(int(a, 16))
            print(f"0x{int(a, 16):X} {f['name'] if f else '?'} {f.get('signature', '') if f else ''}")
        return 0
    d, secs = load_pe(ref / "iwd2.exe")
    if kind == "s":
        for a in args:
            addr = int(a, 16)
            raw = read(d, secs, addr, 512).split(b"\0", 1)[0]
            print(f"0x{addr:X} {raw.decode('latin-1')!r}")
        return 0
    addr = int(args[0], 16)
    count = int(args[1]) if len(args) > 1 else 1
    fmt, size = {"d": ("<I", 4), "i": ("<i", 4), "w": ("<H", 2), "b": ("<B", 1), "f": ("<f", 4), "F": ("<d", 8)}[kind]
    data = read(d, secs, addr, count * size)
    vals = [struct.unpack_from(fmt, data, i * size)[0] for i in range(count)]
    if kind in ("d", "w", "b"):
        print(" ".join(f"0x{v:X}" for v in vals))
    else:
        print(" ".join(str(v) for v in vals))
    return 0


if __name__ == "__main__":
    sys.exit(main())
