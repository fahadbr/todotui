# vim:foldmethod=marker
add_library(todo
	list.h
	list.cpp
	item.h
	item.cpp
)

target_link_libraries(todotui PUBLIC todo)


# test {{{

add_executable(todo_test
	item_test.cpp
)
target_link_libraries(todo_test PUBLIC todo GTest::gtest_main)
add_test(NAME todo COMMAND todo_test)

# }}}
