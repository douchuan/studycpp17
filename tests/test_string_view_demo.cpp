#include <gtest/gtest.h>

#include "string_view_demo.h"

TEST(StringViewTest, CountWords) {
    EXPECT_EQ(count_words("hello world"), 2);
    EXPECT_EQ(count_words("one"), 1);
    EXPECT_EQ(count_words(""), 0);
    EXPECT_EQ(count_words("  a  b  "), 2);
}

TEST(StringViewTest, Head) {
    EXPECT_EQ(head("abcdef", 3), "abc");
    EXPECT_EQ(head("hi", 10), "hi");
    EXPECT_EQ(head("test", 0), "");
}

TEST(StringViewTest, CountChar) {
    EXPECT_EQ(count_char("hello", 'l'), 2);
    EXPECT_EQ(count_char("hello", 'z'), 0);
    EXPECT_EQ(count_char("", 'a'), 0);
}
