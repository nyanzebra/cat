#!/bin/bash

which $CMAKE
mkdir tst/bin
$CMAKE -Btst/bin -Htst -DCMAKE_BUILD_TYPE=Debug
pwd
ls
ls ./tst
cd ./tst/bin
make clean
make cat
./cat
# Codecov
./get_code_coverage.sh
codecov
