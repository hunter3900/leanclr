#!/bin/bash
# build_all.sh - Bash equivalent of build_all.bat
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"

CONFIG="${1:-Debug}"
ARCH="${2:-x64}"

echo "=== Config: $CONFIG | Arch: $ARCH ==="

echo "build basic_test_runner"
pushd "$SCRIPT_DIR/basic_test_runner"
./build.sh "$CONFIG"
popd

echo "All tests built successfully."
