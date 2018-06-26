enable_testing()

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

if(TARGET gtest)
else()
  # Add googletest directly to our build. This defines
  # the gtest and gtest_main targets.
  add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                   ${CMAKE_BINARY_DIR}/googletest-build
                   EXCLUDE_FROM_ALL)
endif()

set(CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/tst/")
get_filename_component(ABSOLUTE_PATH "${CMAKE_SOURCE_DIR}" ABSOLUTE)
message("ABS ${ABSOLUTE_PATH}")

set(TEST_PATH "${ABSOLUTE_PATH}")
message("TST ${TEST_PATH}")
file(GLOB TEST_SRCS ${TEST_PATH} *.cpp)
file(GLOB TEST_HEADERS ${TEST_PATH} *.hpp)
message("TST_SRC ${TEST_SRCS}")
message("TEST_HEAD ${TEST_HEADERS}")

include_directories("${ABSOLUTE_PATH}/../src/")
set(SRCS ${SRCS} ${HEADERS} ${TEST_SRCS} ${TEST_HEADERS})
message("ALL ${SRCS}")
add_executable(catt ${SRCS})

llvm_map_components_to_libnames(llvm_libs support core irreader target passes all)
target_link_libraries(catt gtest_main ${llvm_libs} catcl) #llvm_main)

if (COVERALLS)
  # Create the coveralls target.
  coveralls_setup("${SRCS}"	ON)
endif()

add_test(catt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/catt)
