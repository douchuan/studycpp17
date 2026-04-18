#include <gtest/gtest.h>

#include "backtracking_demo.h"

TEST(BacktrackingDemoTest, Permute) {
    auto result = permute({1, 2, 3});
    EXPECT_EQ(result.size(), 6u);
}
TEST(BacktrackingDemoTest, Subsets) {
    auto result = subsets({1, 2});
    EXPECT_EQ(result.size(), 4u);
}
TEST(BacktrackingDemoTest, NQueens) {
    EXPECT_EQ(n_queens(4), 2);
    EXPECT_EQ(n_queens(8), 92);
}
