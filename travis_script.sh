#!/bin/bash

echo $PATH
which cmake
cmake -Btst/bin -Htst -DCMAKE_BUILD_TYPE=Debug
cd tst/bin
make clean
make cat
./cat
cd ../..
# Codecov
./get_code_coverage.sh
codecov
