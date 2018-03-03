#!/bin/bash

which $CMAKE
mkdir ./tst/bin
#$CMAKE -B./tst/bin -H./tst -DCMAKE_BUILD_TYPE=Debug
cd tst
$CMAKE .. -DCMAKE_BUILD_TYPE=Debug
cd bin
make clean
make cat
./cat
# Codecov
./get_code_coverage.sh
codecov
