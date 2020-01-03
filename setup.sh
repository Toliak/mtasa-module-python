#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
BUILD_DIR="$SCRIPT_DIR/cmake-build-debug"

set -ex

mkdir -p $BUILD_DIR
python3.7 -m venv $BUILD_DIR/python

PYTHON_DIR=$BUILD_DIR/python

"$PYTHON_DIR/bin/pip" install -r $SCRIPT_DIR/python/requirements.txt