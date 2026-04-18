#include <gtest/gtest.h>

#include "sliding_window_demo.h"

TEST(SlidingWindowDemoTest, LongestOnes) {
    EXPECT_EQ(longest_ones({1, 1, 0, 1, 1, 1, 0, 1}, 1), 6);
}
TEST(SlidingWindowDemoTest, LongestSubstringNoRepeat) {
    EXPECT_EQ(longest_substring_no_repeat("abcabcbb"), 3);
    EXPECT_EQ(longest_substring_no_repeat("bbbbb"), 1);
}
TEST(SlidingWindowDemoTest, SlidingWindowMax) {
    auto result = sliding_window_max({1, 3, -1, -3, 5, 3, 6, 7}, 3);
    EXPECT_EQ(result, (std::vector<int>{3, 3, 5, 5, 6, 7}));
}
