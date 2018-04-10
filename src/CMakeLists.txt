PROJECT(cat)

cmake_minimum_required(VERSION 3.9)
message("${CMAKE_SOURCE_DIR}")
# Cmake module path (if exists)
#set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../cmake)

set(UNIX_COMPILER "g++")
set(OSX_COMPILER "clang++")
set(MSVC_COMPILER "msvc")

set(CXX_WARNING_LEVEL "-Wall")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++14 -stdlib=libc++ -fpermissive -ftest-coverage -fprofile-arcs" CACHE STRING "CXX flags" FORCE)
set(CMAKE_CXX_STANDARD "14" CACHE STRING "Default standard CXX")
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "Default disallow extensions")
set(CMAKE_CXX_COMPILE_FEATURES "${CMAKE_CXX_COMPILE_FEATURES} CXX_STD_14" CACHE STRING "Default CXX compile features")
set(CMAKE_CXX_STANDARD_REQUIRED OFF CACHE BOOL "Default standard not required")


# # #TODO: add in llvm download and build here, no need to include in project dirs
# file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/llvm-download)
# file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/llvm-src)
# file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/llvm-build)
# # Download and unpack llvm at configure time
# configure_file("../cmake/llvm.txt" ${CMAKE_BINARY_DIR}/llvm-download/CMakeLists.txt)
# execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#   RESULT_VARIABLE result
# WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/llvm-download )
# if(result)
#   message(FATAL_ERROR "CMake step for llvm failed: ${result}")
# endif()
# execute_process(COMMAND ${CMAKE_COMMAND} --build .
#   RESULT_VARIABLE result
# WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/llvm-download )
# if(result)
#   message(FATAL_ERROR "Build step for llvm failed: ${result}")
# endif()
#
# add_subdirectory(${CMAKE_BINARY_DIR}/llvm-src
#                  ${CMAKE_BINARY_DIR}/llvm-build
#                  EXCLUDE_FROM_ALL)


find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

get_filename_component(ABSOLUTE_PATH "${CMAKE_SOURCE_DIR}" ABSOLUTE)
message("${ABSOLUTE_PATH}")
file(GLOB_RECURSE SRCS ${ABSOLUTE_PATH} *.cpp)
file(GLOB_RECURSE HEADERS ${ABSOLUTE_PATH} *.hpp)
include_directories("${ABSOLUTE_PATH}")
set(SRCS ${SRCS} ${HEADERS} main.cpp)
add_executable(cat ${SRCS})
set_target_properties(cat PROPERTIES LINKER_LANGUAGE CXX)

# list of llvm components
# aarch64
# aarch64asmparser
# aarch64asmprinter
# aarch64codegen
# aarch64desc
# aarch64disassembler
# aarch64info
# aarch64utils
# all
# all-targets
# amdgpu
# amdgpuasmparser
# amdgpuasmprinter
# amdgpucodegen
# amdgpudesc
# amdgpudisassembler
# amdgpuinfo
# amdgpuutils
# analysis
# arm
# armasmparser
# armasmprinter
# armcodegen
# armdesc
# armdisassembler
# arminfo
# armutils
# asmparser
# asmprinter
# binaryformat
# bitreader
# bitwriter
# bpf
# bpfasmprinter
# bpfcodegen
# bpfdesc
# bpfdisassembler
# bpfinfo
# codegen
# core
# coroutines
# coverage
# debuginfocodeview
# debuginfodwarf
# debuginfomsf
# debuginfopdb
# demangle
# dlltooldriver
# engine
# executionengine
# fuzzmutate
# globalisel
# hexagon
# hexagonasmparser
# hexagoncodegen
# hexagondesc
# hexagondisassembler
# hexagoninfo
# instcombine
# instrumentation
# interpreter
# ipo
# irreader
# lanai
# lanaiasmparser
# lanaiasmprinter
# lanaicodegen
# lanaidesc
# lanaidisassembler
# lanaiinfo
# libdriver
# lineeditor
# linker
# lto
# mc
# mcdisassembler
# mcjit
# mcparser
# mips
# mipsasmparser
# mipsasmprinter
# mipscodegen
# mipsdesc
# mipsdisassembler
# mipsinfo
# mirparser
# msp430
# msp430asmprinter
# msp430codegen
# msp430desc
# msp430info
# native
# nativecodegen
# nvptx
# nvptxasmprinter
# nvptxcodegen
# nvptxdesc
# nvptxinfo
# objcarcopts
# object
# objectyaml
# option
# orcjit
# passes
# powerpc
# powerpcasmparser
# powerpcasmprinter
# powerpccodegen
# powerpcdesc
# powerpcdisassembler
# powerpcinfo
# profiledata
# runtimedyld
# scalaropts
# selectiondag
# sparc
# sparcasmparser
# sparcasmprinter
# sparccodegen
# sparcdesc
# sparcdisassembler
# sparcinfo
# support
# symbolize
# systemz
# systemzasmparser
# systemzasmprinter
# systemzcodegen
# systemzdesc
# systemzdisassembler
# systemzinfo
# tablegen
# target
# transformutils
# vectorize
# windowsmanifest
# x86
# x86asmparser
# x86asmprinter
# x86codegen
# x86desc
# x86disassembler
# x86info
# x86utils
# xcore
# xcoreasmprinter
# xcorecodegen
# xcoredesc
# xcoredisassembler
# xcoreinfo


llvm_map_components_to_libnames(llvm_libs support core irreader target passes all)
target_link_libraries(cat ${llvm_libs})
