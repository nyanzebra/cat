cmake_minimum_required(VERSION 3.9)

enable_testing()

# Cmake module path (if exists)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../cmake)

# We probably don't want this to run on every build.
option(COVERALLS "Generate coveralls data" OFF)

if (COVERALLS)
    include(Coveralls)
endif()

set(UNIX_COMPILER "g++")
set(OSX_COMPILER "clang++")
set(MSVC_COMPILER "msvc")

set(CXX_WARNING_LEVEL "-Wall")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++14 -fpermissive -ftest-coverage -fprofile-arcs" CACHE STRING "CXX flags" FORCE)
set(CMAKE_CXX_STANDARD "17" CACHE STRING "Default standard CXX")
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "Default disallow extensions")
set(CMAKE_CXX_COMPILE_FEATURES "${CMAKE_CXX_COMPILE_FEATURES} CXX_STD_14" CACHE STRING "Default CXX compile features")
set(CMAKE_CXX_STANDARD_REQUIRED OFF CACHE BOOL "Default standard not required")

#GTEST
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-src)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-build)
# Download and unpack googletest at configure time
configure_file("../cmake/gtest.txt" ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# #TODO: add in llvm download and build here, no need to include in project dirs
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

if(TARGET gtest)
else()
  # Add googletest directly to our build. This defines
  # the gtest and gtest_main targets.
  add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                   ${CMAKE_BINARY_DIR}/googletest-build
                   EXCLUDE_FROM_ALL)
endif()


set(CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/../")
get_filename_component(ABSOLUTE_PATH "${CMAKE_SOURCE_DIR}" ABSOLUTE)
file(GLOB SRCS ${ABSOLUTE_PATH}/tst/*.cpp)
file(GLOB HEADERS ${ABSOLUTE_PATH}/src/*/*.hpp)
include_directories("${ABSOLUTE_PATH}/src/")
set(SRCS ${SRCS} ${HEADERS})
add_executable(cat ${SRCS})

target_link_libraries(cat gtest_main) #llvm_main)

if (COVERALLS)
  # Create the coveralls target.
  coveralls_setup("${SRCS}"	ON)
endif()

add_test(cat ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cat)
