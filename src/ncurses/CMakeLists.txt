set(CURSES_NEED_NCURSES True)
set(CURSES_NEED_WIDE True)

find_package(Curses REQUIRED)
include_directories( ${CURSES_INCLUDE_DIRS} )
target_link_libraries( todotui ${CURSES_LIBRARIES} )

#target_sources(todotui)
