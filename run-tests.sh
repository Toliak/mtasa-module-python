#! /bin/sh

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

set -ex

rm -rf $SCRIPT_DIR/tests/environment/deathmatch/resources/python
cp -r $SCRIPT_DIR/tools/resource-python $SCRIPT_DIR/tests/environment/deathmatch/resources/python

rm -rf $SCRIPT_DIR/tests/environment/deathmatch/python/mtasa
cp -r $SCRIPT_DIR/tools/python/mtasa $SCRIPT_DIR/tests/environment/deathmatch/python/mtasa

cd $SCRIPT_DIR/tests/environment

docker build -t module_python_tester .

docker run  --rm -t \
            -u $(id -u):$(id -g) \
            -v $SCRIPT_DIR/tests/environment/deathmatch:/home/mtasa/mods/deathmatch \
            -v $SCRIPT_DIR/build-docker:/home/mtasa/x64/modules \
            module_python_tester