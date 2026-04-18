#include <gtest/gtest.h>

#include "two_pointers_demo.h"

TEST(TwoPointersDemoTest, TwoSumSorted) {
    auto [a, b] = two_sum_sorted({2, 7, 11, 15}, 9);
    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 1);
}
TEST(TwoPointersDemoTest, ThreeSum) {
    auto result = three_sum({-1, 0, 1, 2, -1, -4});
    EXPECT_EQ(result.size(), 2u);
}
TEST(TwoPointersDemoTest, MaxArea) { EXPECT_EQ(max_area({1, 8, 6, 2, 5, 4, 8, 3, 7}), 49); }
TEST(TwoPointersDemoTest, Trap) { EXPECT_EQ(trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}), 6); }
