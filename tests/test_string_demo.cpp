#include <gtest/gtest.h>

#include "string_demo.h"

TEST(StringDemoTest, Split) {
    auto tokens = split("a,b,c", ',');
    ASSERT_EQ(tokens.size(), 3u);
    EXPECT_EQ(tokens[0], "a");
    EXPECT_EQ(tokens[1], "b");
    EXPECT_EQ(tokens[2], "c");
}

TEST(StringDemoTest, SplitNoDelim) {
    auto tokens = split("hello", ',');
    ASSERT_EQ(tokens.size(), 1u);
    EXPECT_EQ(tokens[0], "hello");
}

TEST(StringDemoTest, SplitEmpty) {
    auto tokens = split("", ',');
    ASSERT_EQ(tokens.size(), 1u);
    EXPECT_EQ(tokens[0], "");
}

TEST(StringDemoTest, Trim) {
    EXPECT_EQ(trim("  hello  "), "hello");
    EXPECT_EQ(trim("\thello\n"), "hello");
    EXPECT_EQ(trim("hello"), "hello");
    EXPECT_EQ(trim("   "), "");
    EXPECT_EQ(trim(""), "");
}

TEST(StringDemoTest, IsPalindrome) {
    EXPECT_TRUE(is_palindrome("racecar"));
    EXPECT_TRUE(is_palindrome(""));
    EXPECT_TRUE(is_palindrome("a"));
    EXPECT_TRUE(is_palindrome("abba"));
    EXPECT_FALSE(is_palindrome("hello"));
    EXPECT_FALSE(is_palindrome("abc"));
}
