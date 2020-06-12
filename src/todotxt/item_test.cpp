#include "gtest/gtest.h"
#include "item.h"

TEST(Item, TestBasic) {
	todo::Item test_item{"(A) 2020-06-11 this is a @context and this is a +tag"};
	EXPECT_EQ(test_item.complete(), false);
	EXPECT_EQ(test_item.date_added(), "2020-06-11");
	EXPECT_EQ(test_item.priority(), 'A');
	EXPECT_EQ(test_item.contexts()[0], "context");
	EXPECT_EQ(test_item.tags()[0], "tag");
}


