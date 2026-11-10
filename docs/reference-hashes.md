# Reference game files

The reference is the GOG installer `setup_icewind_dale_2_2.01_fixes_(77030).exe` (+ `-1.bin`), extracted with innoextract 1.9 (`innoextract --gog -e`). GOG keeps `IWD2.exe`, `icewind2.ini`, `Keymap.ini` and `Party.ini` in `__support/app/`. The installer copies them to the game root, so `tools/make_play_dir.ps1` expects them there.

| File | SHA-256 |
|---|---|
| `iwd2.exe` (from `__support/app/IWD2.exe`) | `ba56349a30240058fa9b110dca5b92c32715492356c80017df9648c838a9db8e` |
| `CHITIN.KEY` | `4e157c811ffe059f65a2d1135a5c85b550796b3e98c6b848c49107c87d5ed531` |
| `dialog.tlk` | `22cc615196c55cdcb7bea6e0cd7d1654ee972f20e745621ad1a276bb24de137d` |
| `icewind2.ini` (GOG default) | `3cce870bc8385eedf5aa831b5127ded4d172ceafa0e5d4e2e792bb6a567e5b9e` |
| `Keymap.ini` | `4a935e74de33fc7277f35d59c2c7a75b4fe86373ac1a04e9d77fec0a0a65a1c4` |
| `Party.ini` | `e0f93c949a90c6ba1affd18b257cf7cd4ef795f188ff9bd0e250e60b8814b787` |
| `binkw32.dll` | `65d87646770fa871a58d9d27cdfb5a1ad991dd64900f0ea35b0678457c902d41` |

The data is 133 BIF files under `Data/` and `CD2/Data/`, plus 188 files in `Override/`.

## `iwd2.exe` layout

| Section | VA | Virtual size |
|---|---|---|
| `.text` | `0x401000` | `0x4458F1` |
| `.rdata` | `0x847000` | `0x5D7D2` |
| `.data` | `0x8A5000` | `0x175E81` |
| `.rsrc` | `0xA1B000` | `0x5A60` |

The image base is `0x400000`. Spot checks show function prologues at the annotated addresses `0x401090`, `0x421820`, `0x7D8E80` and `0x7DA0A0`.

## Modded installs are not references

An install with IWD2EE + IEex (as in `C:\GOG Games\Icewind Dale II`) has an `iwd2.exe` of the same size but a different hash (80 bytes patched in `.data` at `0x8BA0CC` and `0x8BA110`). Its `dialog.tlk` and `Override/` are rewritten too. Don't test against it.
