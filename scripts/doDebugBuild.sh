#!/bin/bash

SCRIPT_DIR=$(cd $(dirname $0);pwd)
TOP_DIR=$(dirname ${SCRIPT_DIR})

cmake -S ${TOP_DIR}/src -B ${TOP_DIR}/build -DCMAKE_BUILD_TYPE=Debug
cmake --build ${TOP_DIR}/build
