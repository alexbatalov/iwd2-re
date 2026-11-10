# Build a disposable test copy of the game (IWD2_PLAY_DIR) from the pristine
# reference (IWD2_REF_DIR). Large read-only folders are linked with junctions,
# small and writable files are copied, and icewind2.ini is set up for testing
# (windowed, 32 bpp, cheats on, intro movies off).
#
# Usage: powershell -ExecutionPolicy Bypass -File tools\make_play_dir.ps1 [-Ref C:\iwd2-ref] [-Play C:\iwd2-play] [-FullScreen]
param(
    [string]$Ref = $(if ($env:IWD2_REF_DIR) { $env:IWD2_REF_DIR } else { "C:\iwd2-ref" }),
    [string]$Play = $(if ($env:IWD2_PLAY_DIR) { $env:IWD2_PLAY_DIR } else { "C:\iwd2-play" }),
    [switch]$FullScreen
)
$ErrorActionPreference = "Stop"

if (-not (Test-Path (Join-Path $Ref "CHITIN.KEY"))) { throw "no CHITIN.KEY in $Ref" }
if ((Resolve-Path $Ref).Path -eq [IO.Path]::GetFullPath($Play)) { throw "play dir must differ from ref dir" }

if (Test-Path $Play) {
    # Remove junctions first so their targets (the reference) are never touched.
    Get-ChildItem $Play -Force | Where-Object { $_.Attributes -band [IO.FileAttributes]::ReparsePoint } | ForEach-Object { cmd /c rmdir "$($_.FullName)" | Out-Null }
    Remove-Item $Play -Recurse -Force
}
New-Item -ItemType Directory $Play | Out-Null

$linked = @("Data", "CD2", "Music", "Sounds")
$skip = @("__redist", "__support", "app", "commonappdata", "tmp", "webcache.zip", "manual.pdf") + $linked
foreach ($d in $linked) {
    cmd /c mklink /J "$Play\$d" "$Ref\$d" | Out-Null
}
Get-ChildItem $Ref -Force | Where-Object { $skip -notcontains $_.Name } | ForEach-Object {
    Copy-Item $_.FullName (Join-Path $Play $_.Name) -Recurse -Force
}
# The reference is read-only; the copy must be writable.
Get-ChildItem $Play -Recurse -File -Force -ErrorAction SilentlyContinue | Where-Object { $_.IsReadOnly } | ForEach-Object { $_.IsReadOnly = $false }

function Set-Ini([string[]]$lines, [string]$section, [string]$key, [string]$value) {
    $out = New-Object System.Collections.Generic.List[string]
    $inSection = $false; $done = $false
    foreach ($l in $lines) {
        if ($l -match '^\[(.+)\]') {
            if ($inSection -and -not $done) { $out.Add("$key=$value"); $done = $true }
            $inSection = ($Matches[1] -eq $section)
        } elseif ($inSection -and $l -match "^$([regex]::Escape($key))=") {
            $out.Add("$key=$value"); $done = $true; continue
        }
        $out.Add($l)
    }
    if (-not $done) {
        if (-not $inSection) { $out.Add("[$section]") }
        $out.Add("$key=$value")
    }
    return ,$out.ToArray()
}

$ini = Join-Path $Play "icewind2.ini"
$lines = Get-Content $ini
$p = $Play.TrimEnd('\')
$lines = Set-Ini $lines "Alias" "HD0:" "$p\"
$lines = Set-Ini $lines "Alias" "CD1:" "$p\Data\"
$lines = Set-Ini $lines "Alias" "CD2:" "$p\CD2\"
$lines = Set-Ini $lines "Program Options" "Full Screen" $(if ($FullScreen) { "1" } else { "0" })
$lines = Set-Ini $lines "Program Options" "BitsPerPixel" "32"
$lines = Set-Ini $lines "Program Options" "Screen Position X" "0"
$lines = Set-Ini $lines "Program Options" "Screen Position Y" "0"
$lines = Set-Ini $lines "Game Options" "Cheats" "1"
foreach ($m in "BISLOGO", "INFELOGO", "WOTC", "INTRO") { $lines = Set-Ini $lines "Movies" $m "1" }
Set-Content -Path $ini -Value $lines -Encoding ASCII

Write-Host "play dir ready: $Play"
