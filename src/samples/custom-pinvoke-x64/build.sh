#!/bin/bash
# build.sh for custom-pinvoke-win64 (Linux/macOS)
set -e
BUILD_DIR="build"
BUILD_TYPE=${1:-Debug}

cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cmake --build "$BUILD_DIR" --target custom-pinvoke -- -j$(nproc || sysctl -n hw.ncpu)
EXE="$BUILD_DIR/bin/custom-pinvoke"
if [ -f "$EXE" ]; then
  echo "Built: $EXE"
else
  echo "Warning: expected exe not found at $EXE"
fi
echo "Done."
