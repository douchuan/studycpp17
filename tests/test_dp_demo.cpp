#include <gtest/gtest.h>

#include "dp_demo.h"

TEST(DpDemoTest, Fib) {
    EXPECT_EQ(fib(0), 0);
    EXPECT_EQ(fib(1), 1);
    EXPECT_EQ(fib(10), 55);
}
TEST(DpDemoTest, ClimbStairs) {
    EXPECT_EQ(climb_stairs(1), 1);
    EXPECT_EQ(climb_stairs(5), 8);
}
TEST(DpDemoTest, Knapsack) { EXPECT_EQ(knapsack({2, 3, 4, 5}, {3, 4, 5, 7}, 7), 10); }
TEST(DpDemoTest, LCS) { EXPECT_EQ(longest_common_subsequence("abcde", "ace"), 3); }
TEST(DpDemoTest, LIS) {
    EXPECT_EQ(longest_increasing_subsequence({10, 9, 2, 5, 3, 7, 101, 18}), 4);
}
TEST(DpDemoTest, MaxSubarray) { EXPECT_EQ(max_subarray({-2, 1, -3, 4, -1, 2, 1, -5, 4}), 6); }
