#!/bin/zsh

if [[ -e bin ]]; then
  rm -rf bin
fi
mkdir bin
cd bin
cmake ..
make clean
make catc ARGS=-V
./catc -i /Users/robertbaldwin/Documents/GitHub/cat/tst/basic_main.cat -o /Users/robertbaldwin/Documents/GitHub/cat/tst/basic_main.o;
clang++ /Users/robertbaldwin/Documents/GitHub/cat/tst/__main.cpp /Users/robertbaldwin/Documents/GitHub/cat/tst/basic_main.o -o /Users/robertbaldwin/Documents/GitHub/cat/tst/basic_main
