# vim:foldmethod=marker
cmake_minimum_required(VERSION 3.12)

cmake_policy(SET CMP0079 NEW)
cmake_policy(SET CMP0076 NEW)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)
set(CMAKE_CXX_FLAGS, "-lncurses++")

#include("cmake/HunterGate.cmake")
#HunterGate(
    #URL "https://github.com/cpp-pm/hunter/archive/v0.23.260.tar.gz"
    #SHA1 "13775235910a3fa85644568d1c5be8271de72e1c"
#)

project(todotui VERSION 0.1.0 LANGUAGES CXX)

get_filename_component(TODOTUI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src ABSOLUTE)


# googletest {{{
# Download and unpack googletest at configure time
configure_file(cmake/googletest.cmake googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )

if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )

if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Now simply link against gtest or gtest_main as needed. Eg
# add_executable(example example.cpp)
# target_link_libraries(example gtest_main)
# add_test(NAME example_test COMMAND example)

# }}} end googletest

add_executable(todotui src/main.cpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

enable_testing()

add_subdirectory(src/ncurses)
add_subdirectory(src/todotxt)

target_include_directories(todotui PUBLIC
  "${PROJECT_BINARY_DIR}"
  )

