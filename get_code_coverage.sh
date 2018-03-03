#!/bin/bash
for filename in `find ./src | egrep --exclude-dir='./tst' '(\.cpp|\.hpp)'`;
do
  $COVERAGE -n -o . $filename > /dev/null;
done
