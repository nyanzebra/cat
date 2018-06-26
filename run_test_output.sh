#!/bin/bash
rm -f cattest
clang++ __main.cpp tst/bin/output -o cattest -x ir
chmod 755 ./cattest
./cattest
