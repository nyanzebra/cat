#!/bin/zsh

if [[ -e tst/bin ]]; then
  rm -rf tst/bin
fi
mkdir tst/bin
cd tst/bin
cmake ../..
make clean
make catt ARGS=-V
tst/catt;
