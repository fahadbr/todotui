cmake_minimum_required(VERSION 3.12)

cmake_policy(SET CMP0079 NEW)
cmake_policy(SET CMP0076 NEW)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)


project(todotui VERSION 0.1.0 LANGUAGES CXX)

add_executable(todotui src/main.cpp)
add_subdirectory(src/ncurses)
add_subdirectory(src/todotxt)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(todotui PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
