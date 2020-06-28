#include "item.h"

#include <gtest/gtest.h>

TEST(Item, TestMixed) {
  todo::Item test_item{"(A) 2020-06-11 this is a @context and this is a +tag h:1"};
  EXPECT_EQ(test_item.complete(), false);
  EXPECT_EQ(test_item.date_added(), "2020-06-11");
  EXPECT_EQ(test_item.priority(), 'A');
  EXPECT_EQ(test_item.contexts()[0], "context");
  EXPECT_EQ(test_item.tags()[0], "tag");
  // EXPECT_EQ(test_item.extensions()[0].first, "h");
  // EXPECT_EQ(test_item.extensions()[0].second, "1");
  EXPECT_TRUE(test_item.hidden());
}

TEST(Item, TestDateAdded) {
  todo::Item test_item{"2020-06-11 2020-06-12 2020-06-13 2020-06-14"};
  EXPECT_EQ(test_item.date_added(), "2020-06-11");
}

TEST(Item, TestDateComplete) {
  todo::Item test_item{"x 2020-06-12 2020-06-11 2020-6-13 2020-6-14"};
  EXPECT_EQ(test_item.complete(), true);
  EXPECT_EQ(test_item.date_completed(), "2020-06-12");
  EXPECT_EQ(test_item.date_added(), "2020-06-11");
  EXPECT_FALSE(test_item.hidden());
}

TEST(Item, TestPriorityIncomplete) {
  todo::Item test_item{"(A) 2020-06-11 (C) this is a @context and this is a +tag h:1"};
  EXPECT_EQ(test_item.complete(), false);
  EXPECT_EQ(test_item.priority(), 'A');
}

TEST(Item, TestPriorityComplete) {
  todo::Item test_item{"x 2020-06-12 (D) 2020-06-11 (C) this is a @context and this is a +tag h:1"};
  EXPECT_EQ(test_item.complete(), true);
  EXPECT_EQ(test_item.date_completed(), "2020-06-12");
  EXPECT_EQ(test_item.priority(), 'D');
  EXPECT_EQ(test_item.date_added(), "2020-06-11");
}

TEST(Item, TestTags) {
  todo::Item test_item{"(A) 2020-06-11 this is a +tag and this is another +tag +different_tag"};
  EXPECT_EQ(test_item.complete(), false);
  EXPECT_EQ(test_item.priority(), 'A');
  EXPECT_EQ(test_item.tags().size(), 2);  // ensure no duplicates
  EXPECT_TRUE(todo::ContainsItem(test_item.tags(), "tag"));
  EXPECT_TRUE(todo::ContainsItem(test_item.tags(), "different_tag"));
}

TEST(Item, TestContexts) {
  todo::Item test_item{"(A) 2020-06-11 this is a @ctx and this is another @ctx @context"};
  EXPECT_EQ(test_item.complete(), false);
  EXPECT_EQ(test_item.priority(), 'A');
  EXPECT_EQ(test_item.contexts().size(), 2);  // ensure no duplicates
  EXPECT_TRUE(todo::ContainsItem(test_item.contexts(), "ctx"));
  EXPECT_TRUE(todo::ContainsItem(test_item.contexts(), "context"));
}

TEST(Item, TestDueDate) {
  todo::Item test_item{"(A) 2020-06-11 this is a @ctx and this is another @ctx @context due:2020-06-30"};
  EXPECT_EQ(test_item.due_date(), "2020-06-30");
}

TEST(Item, TestDueMalformed) {
  todo::Item test_item{"(A) 2020-06-11 this is a @ctx and this is another @ctx @context due:boogers"};
  EXPECT_EQ(test_item.due_date(), "");
}

TEST(Item, TestThresholdDate) {
  todo::Item test_item{"(A) 2020-06-11 this is a @ctx and this is another @ctx @context t:2020-06-30"};
  EXPECT_EQ(test_item.threshold_date(), "2020-06-30");
}

TEST(Item, TestThresholdMalformed) {
  todo::Item test_item{"(A) 2020-06-11 this is a @ctx and this is another @ctx @context t:boogers"};
  EXPECT_EQ(test_item.threshold_date(), "");
}

TEST(Item, TestHidden) {
  todo::Item hidden_item{"(A) 2020-06-11 this is a @ctx and this is another @ctx @context h:1"};
  EXPECT_TRUE(hidden_item.hidden());
  todo::Item nonhidden_item{"(A) 2020-06-11 this is a @ctx and this is another @ctx @context h:0"};
  EXPECT_FALSE(nonhidden_item.hidden());
}

// TEST(Item, TestNotHidden) {
//  todo::Item nonhidden_item{"(A) 2020-06-11 this is a @ctx and this is another @ctx @context"};
//  EXPECT_FALSE(nonhidden_item.hidden());
//}

TEST(Item, TestRecurrance) {
  todo::Item test_item{"(A) 2020-06-11 this is a @ctx and this is another @ctx @context rec:2w"};
  EXPECT_EQ(test_item.recurrance(), "2w");
}
