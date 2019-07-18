#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

set -ex

docker build -t module_python_builder $SCRIPT_DIR
docker run --rm -it \
                -v "$SCRIPT_DIR:/home/builder/code" \
                -v "$SCRIPT_DIR/build:/home/builder/build" \
                -u 0:0 \
                --name module_python_builder_container \
                module_python_builder
