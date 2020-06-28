# vim:foldmethod=marker
add_library(todotxt
	list.h
	list.cpp
	item.h
	item.cpp
)

target_link_libraries(todotui todotxt)


# test {{{

add_executable(todotxt_test
	item_test.cpp
)
target_link_libraries(todotxt_test PUBLIC todotxt GTest::gtest_main)
add_test(NAME todotxt COMMAND todotxt_test)

# }}}
