#!/bin/bash

which $CMAKE
mkdir ./tst/bin
pwd
ls
ls ./tst
$CMAKE -B./tst/bin -H./tst -DCMAKE_BUILD_TYPE=Debug
cd ./tst/bin
make clean
make cat
./cat
# Codecov
./get_code_coverage.sh
codecov
