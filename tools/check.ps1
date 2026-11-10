# T0 build gate + T1 inventory check + T2 unit tests.
# Usage: powershell -ExecutionPolicy Bypass -File tools\check.ps1 [-Config RelWithDebInfo] [-SkipTests]
param(
    [string]$Config = "RelWithDebInfo",
    [string]$BuildDir = "build",
    [switch]$SkipTests
)
$ErrorActionPreference = "Stop"
$repo = Split-Path -Parent $PSScriptRoot
Set-Location $repo

$cmake = (Get-Command cmake -ErrorAction SilentlyContinue).Source
if (-not $cmake) {
    $vs = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath
    $cmake = Join-Path $vs "Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
}
$ctest = Join-Path (Split-Path $cmake) "ctest.exe"

if (-not (Test-Path "$BuildDir\CMakeCache.txt")) {
    & $cmake -B $BuildDir -G "Visual Studio 17 2022" -A Win32
    if ($LASTEXITCODE) { exit $LASTEXITCODE }
}

$log = Join-Path $BuildDir "build-$Config.log"
& $cmake --build $BuildDir --config $Config -- /m /nologo /v:minimal 2>&1 | Tee-Object -FilePath $log | Select-String -Pattern "error|warning C" | Select-Object -Last 40
if ($LASTEXITCODE) { Write-Host "BUILD FAILED (see $log)"; exit $LASTEXITCODE }

# Report warnings from files compiled in this run. Incremental builds only see
# changed files, so this is a report, not a ratchet: fix new warnings you see.
$warnings = @(Select-String -Path $log -Pattern "warning C\d+" | ForEach-Object { $_.Line.Trim() } | Sort-Object -Unique)
Write-Host "warnings in this build: $($warnings.Count)"
$warnings | Select-Object -First 20 | ForEach-Object { Write-Host "  $_" }

py -I tools\inventory.py --check | Select-Object -Last 3
if ($LASTEXITCODE) { exit $LASTEXITCODE }

if (-not $SkipTests) {
    & $ctest --test-dir $BuildDir -C $Config --output-on-failure
    if ($LASTEXITCODE) { exit $LASTEXITCODE }
}
Write-Host "check OK"
