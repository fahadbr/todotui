
target_link_libraries(todotui PUBLIC PkgConfig::ncurses++w)

add_library(tui
	app.h
	app.cpp
)

target_include_directories(tui PUBLIC ${TODOTUI_SOURCE_DIR})

target_link_libraries(todotui PUBLIC tui)
