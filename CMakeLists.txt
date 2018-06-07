cmake_minimum_required(VERSION 3.9)

# Cmake module path (if exists)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# We probably don't want this to run on every build.
option(COVERALLS "Generate coveralls data" OFF)

if (COVERALLS)
    include(Coveralls)
endif()

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

set(UNIX_COMPILER "g++")
set(OSX_COMPILER "clang++")
set(MSVC_COMPILER "msvc")

set(CXX_WARNING_LEVEL "-Wall")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++14 -fpermissive -ftest-coverage -fprofile-arcs" CACHE STRING "CXX flags" FORCE)
set(CMAKE_CXX_STANDARD "14" CACHE STRING "Default standard CXX")
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "Default disallow extensions")
set(CMAKE_CXX_COMPILE_FEATURES "${CMAKE_CXX_COMPILE_FEATURES} CXX_STD_14" CACHE STRING "Default CXX compile features")
set(CMAKE_CXX_STANDARD_REQUIRED OFF CACHE BOOL "Default standard not required")

enable_testing()

add_subdirectory(src)
add_subdirectory(tst)
