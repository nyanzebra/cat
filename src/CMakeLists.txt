PROJECT(catc)

cmake_minimum_required(VERSION 3.9)
message("${CMAKE_SOURCE_DIR}")
# Cmake module path (if exists)
#set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../cmake)

# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

get_filename_component(ABSOLUTE_PATH "${CMAKE_SOURCE_DIR}/src" ABSOLUTE)
message("${ABSOLUTE_PATH}")
file(GLOB_RECURSE SRCS ${ABSOLUTE_PATH} *.cpp)
file(GLOB_RECURSE HEADERS ${ABSOLUTE_PATH} *.hpp)
message("SRC ${SRCS}")
message("HEAD ${HEADERS}")
include_directories("${ABSOLUTE_PATH}")
set(SRCS ${SRCS} ${HEADERS} main.cpp)
add_library(catcl ${SRCS})
add_executable(catc ${SRCS})
set_target_properties(catc PROPERTIES LINKER_LANGUAGE CXX)

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
target_link_libraries(catc ${llvm_libs})
