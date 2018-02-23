#!/bin/zsh
for filename in `find . | egrep '(\.cpp|\.hpp)'`; 
do
  gcov-7 -n -o . $filename > /dev/null;
done
