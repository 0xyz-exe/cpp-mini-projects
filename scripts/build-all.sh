#!/bin/bash
# Build script for Linux/macOS

set -e

PROJECT=""
if [ $# -gt 0 ]; then
    PROJECT="$1"
fi

echo "=== C++ Mini Projects Build Script ==="
echo ""

# Check tools
if ! command -v cmake &> /dev/null; then
    echo "ERROR: cmake not found"
    exit 1
fi

if ! command -v g++ &> /dev/null; then
    echo "ERROR: g++ not found"
    exit 1
fi

echo "Tools detected:"
echo "  CMake: $(cmake --version | head -n1)"
echo "  G++:   $(g++ --version | head -n1)"
echo ""

# Configure
if [ ! -d "build" ]; then
    echo "Configuring build system..."
    cmake -B build -G Ninja || cmake -B build
fi

# Build
echo "Building..."
if [ -n "$PROJECT" ]; then
    echo "  Target: $PROJECT"
    cmake --build build --target "$PROJECT"
else
    echo "  Building all projects"
    cmake --build build
fi

echo ""
echo "Build successful!"
