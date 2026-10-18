#!/bin/bash
# Test script for Linux/macOS

set -e

echo "=== C++ Mini Projects Test Runner ==="
echo ""

if [ ! -d "build" ]; then
    echo "ERROR: Build directory not found. Run build-all.sh first"
    exit 1
fi

echo "Running tests..."
echo ""

ctest --test-dir build --output-on-failure

echo ""
echo "All tests passed!"
