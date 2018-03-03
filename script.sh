#!/bin/bash

echo $PATH
which cmake
cmake -B./tst/bin -H./tst -DCMAKE_BUILD_TYPE=Debug
cd tst/bin
make clean
make cat
./cat
# Codecov
./get_code_coverage.sh
codecov
