# Test script for Windows PowerShell
param(
    [switch]$Verbose
)

$ErrorActionPreference = "Stop"

$env:PATH = "C:\msys64\mingw64\bin;$env:PATH"

Write-Host "=== C++ Mini Projects Test Runner ===" -ForegroundColor Cyan
Write-Host ""

if (-not (Test-Path "build")) {
    Write-Host "ERROR: Build directory not found. Run build-all.ps1 first" -ForegroundColor Red
    exit 1
}

Write-Host "Running tests..." -ForegroundColor Yellow
Write-Host ""

if ($Verbose) {
    & ctest --test-dir build --output-on-failure
} else {
    & ctest --test-dir build
}

if ($LASTEXITCODE -ne 0) {
    Write-Host ""
    Write-Host "Some tests failed" -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "All tests passed!" -ForegroundColor Green
