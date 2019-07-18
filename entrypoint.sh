#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
BUILD_DIR="$SCRIPT_DIR/../build"

set -ex

cmake -H$SCRIPT_DIR -B$SCRIPT_DIR/build -DBUILD_TESTS=On
cmake --build $SCRIPT_DIR/build

