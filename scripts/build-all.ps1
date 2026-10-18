# Build script for Windows PowerShell
param(
    [string]$Project = ""
)

$ErrorActionPreference = "Stop"

$env:PATH = "C:\msys64\mingw64\bin;$env:PATH"

Write-Host "=== C++ Mini Projects Build Script ===" -ForegroundColor Cyan
Write-Host ""

# Check tools
$cmake = Get-Command cmake.exe -ErrorAction SilentlyContinue
$gpp = Get-Command g++.exe -ErrorAction SilentlyContinue
$ninja = Get-Command ninja.exe -ErrorAction SilentlyContinue

if (-not $cmake) {
    Write-Host "ERROR: cmake not found" -ForegroundColor Red
    Write-Host "Install: winget install -e --id Kitware.CMake"
    exit 1
}

if (-not $gpp) {
    Write-Host "ERROR: g++ not found" -ForegroundColor Red
    Write-Host "Install MinGW-w64 via MSYS2: winget install -e --id MSYS2.MSYS2"
    Write-Host "Then run: C:\msys64\usr\bin\bash.exe -lc 'pacman -S --noconfirm mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja'"
    exit 1
}

Write-Host "Tools detected:" -ForegroundColor Green
Write-Host "  CMake: $(cmake --version | Select-Object -First 1)"
Write-Host "  G++:   $(g++ --version | Select-Object -First 1)"
Write-Host ""

# Configure
if (-not (Test-Path "build")) {
    Write-Host "Configuring build system..." -ForegroundColor Yellow
    & cmake -B build -G Ninja
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Configure failed" -ForegroundColor Red
        exit 1
    }
}

# Build
Write-Host "Building..." -ForegroundColor Yellow
if ($Project) {
    Write-Host "  Target: $Project" -ForegroundColor Cyan
    & cmake --build build --target $Project
} else {
    Write-Host "  Building all projects" -ForegroundColor Cyan
    & cmake --build build
}

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed" -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "Build successful!" -ForegroundColor Green
