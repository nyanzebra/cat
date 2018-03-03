#!/bin/zsh

which cmake
cmake -Btst/bin -Htst -DCMAKE_BUILD_TYPE=Debug
pwd
ls
cd tst/bin
make clean
make cat
./cat
# Codecov
./get_code_coverage.sh
codecov
