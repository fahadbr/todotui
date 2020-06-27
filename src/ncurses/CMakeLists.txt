set(CURSES_NEED_NCURSES True)
set(CURSES_NEED_WIDE True)


find_package(Curses REQUIRED)
include_directories( ${CURSES_INCLUDE_DIRS} )
target_link_libraries( todotui ${CURSES_LIBRARIES} )

add_library(ncursespp
	window.h
	window.cpp
)

# TODO: this is temporary
target_include_directories(ncursespp PUBLIC ${TODOTUI_SOURCE_DIR})

target_link_libraries(todotui ncursespp)
