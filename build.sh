#!/bin/bash

CUR_DIR=$(cd `dirname $0`;pwd)
mkdir ${CUR_DIR}/build -p
cd build
cmake ..
cd ..
make -j`grep -c "^processor" /proc/cpuinfo`
