#!/bin/bash
# run_tests.sh - Bash equivalent of run_tests.bat
set -e

CONFIG="${1:-Debug}"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RUNNER="$SCRIPT_DIR/basic_test_runner/build/bin/test"

if [ ! -f "$RUNNER" ]; then
    echo "ERROR: Test runner not found at '$RUNNER'. Please run 'build_all.sh' to build the tests first."
    exit 1
fi

"$RUNNER"
RESULT=$?
if [ $RESULT -ne 0 ]; then
    echo "Some tests failed."
    exit $RESULT
else
    echo "All tests passed."
fi
