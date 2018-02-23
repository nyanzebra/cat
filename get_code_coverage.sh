#!/bin/zsh
for filename in `find ./src | egrep --exclude-dir='./tst' '(\.cpp|\.hpp)'`;
do
  gcov-7 -n -o . $filename > /dev/null;
done
