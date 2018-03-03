#!/bin/bash

#CMAKE
CMAKE_URL="https://cmake.org/files/v3.9/cmake-3.9.1-Linux-x86_64.tar.gz"
mkdir cmake && wget --no-check-certificate -O - ${CMAKE_URL} | tar --strip-components=1 -xz -C cmake
export PATH=${DEPS_DIR}/cmake/bin:${PATH}
#CODECOV
apt-get update && apt-get install -y python-pip
pip install codecov
#LLVM
LLVM_INSTALL=${DEPS_DIR}/llvm/install
LLVM_VERSION="3.9.1";
LLVM_URL="http://llvm.org/releases/${LLVM_VERSION}/llvm-${LLVM_VERSION}.src.tar.xz"
LIBCXX_URL="http://llvm.org/releases/${LLVM_VERSION}/libcxx-${LLVM_VERSION}.src.tar.xz"
LIBCXXABI_URL="http://llvm.org/releases/${LLVM_VERSION}/libcxxabi-${LLVM_VERSION}.src.tar.xz"
mkdir -p llvm llvm/build llvm/projects/libcxx llvm/projects/libcxxabi
wget -O - ${LLVM_URL} | tar --strip-components=1 -xJ -C llvm
wget -O - ${LIBCXX_URL} | tar --strip-components=1 -xJ -C llvm/projects/libcxx
wget -O - ${LIBCXXABI_URL} | tar --strip-components=1 -xJ -C llvm/projects/libcxxabi
(cd llvm/build && cmake .. -DCMAKE_INSTALL_PREFIX=${LLVM_INSTALL})
(cd llvm/build/projects/libcxx && make install -j2)
(cd llvm/build/projects/libcxxabi && make install -j2)
export CXXFLAGS="-isystem ${LLVM_INSTALL}/include/c++/v1"
export LDFLAGS="-L ${LLVM_INSTALL}/lib -l c++ -l c++abi"
export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${LLVM_INSTALL}/lib"
COVERAGE=gcov
