cmake_minimum_required(VERSION 3.10)

project(todotui VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CURSES_NEED_NCURSES True)
set(CURSES_NEED_WIDE True)

add_executable(todotui src/main.cc)
find_package(Curses REQUIRED)
include_directories( ${CURSES_INCLUDE_DIRS} )
target_link_libraries( todotui ${CURSES_LIBRARIES} )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(todotui PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
