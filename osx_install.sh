#!/bin/bash

brew install cmake || brew upgrade cmake;
brew install python || brew upgrade python;
pip2 install codecov;
COVERAGE=gcov-7
CMAKE=cmake
./script.sh
