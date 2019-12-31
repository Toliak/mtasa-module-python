#! /bin/sh

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

set -ex

cd $SCRIPT_DIR/tests/environment

docker build -t module_python_tester .

docker run  --rm -t \
            -u $(id -u):$(id -g) \
            -v $SCRIPT_DIR/tests/environment/deathmatch:/home/mtasa/mods/deathmatch \
            -v $SCRIPT_DIR/build-docker:/home/mtasa/x64/modules \
            module_python_tester