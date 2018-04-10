#!/bin/zsh

if [[ -e bin ]]; then
  rm -rf bin
fi
mkdir bin
cd bin
cmake ../src
make clean
make cat ARGS=-V
./cat -i /Users/robertbaldwin/Documents/GitHub/cat/tst/basic_main.cat -o /Users/robertbaldwin/Documents/GitHub/cat/tst/basic_main.o;
