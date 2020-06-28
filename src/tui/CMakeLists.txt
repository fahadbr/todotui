set(CURSES_NEED_NCURSES True)
set(CURSES_NEED_WIDE True)


target_link_libraries(todotui PkgConfig::ncursesw PkgConfig::ncurses++w)

add_library(ncursespp
	window.h
	window.cpp
	app.h
	app.cpp
)

# TODO: this is temporary
target_include_directories(ncursespp PUBLIC ${TODOTUI_SOURCE_DIR})

target_link_libraries(todotui ncursespp)
