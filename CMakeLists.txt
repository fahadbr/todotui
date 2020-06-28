# vim:foldmethod=marker
cmake_minimum_required(VERSION 3.12)

cmake_policy(SET CMP0079 NEW)
cmake_policy(SET CMP0076 NEW)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

include("cmake/SetupHunter.cmake")

project(todotui VERSION 0.1.0 LANGUAGES CXX)

get_filename_component(TODOTUI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src ABSOLUTE)

find_package(GTest CONFIG REQUIRED)
find_package(ncursesw CONFIG REQUIRED)
find_package(ncurses++w CONFIG REQUIRED)

add_executable(todotui src/main.cpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

enable_testing()

add_subdirectory(src/tui)
add_subdirectory(src/todo)

target_include_directories(todotui PUBLIC
  "${PROJECT_BINARY_DIR}"
  )

