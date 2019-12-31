#! /bin/sh

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

set -ex

mkdir -p $SCRIPT_DIR/build-docker

docker build -t module_python_builder $SCRIPT_DIR
docker run      --rm -t \
                -v "$SCRIPT_DIR:/home/builder/code" \
                -v "$SCRIPT_DIR/build-docker:/home/builder/build" \
                -u $(id -u):$(id -g) \
                --name module_python_builder_container \
                module_python_builder

mv $SCRIPT_DIR/build-docker $SCRIPT_DIR/build-docker-temp
mkdir $SCRIPT_DIR/build-docker
mv $SCRIPT_DIR/build-docker-temp/libModulePython.so $SCRIPT_DIR/build-docker/libModulePython.so
rm -rf $SCRIPT_DIR/build-docker-temp