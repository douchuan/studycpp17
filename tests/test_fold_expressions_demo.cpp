#include <gtest/gtest.h>

#include "fold_expressions_demo.h"

TEST(FoldExpressionsTest, Sum) {
    EXPECT_EQ(sum(1, 2, 3), 6);
    EXPECT_EQ(sum(10), 10);
}

TEST(FoldExpressionsTest, Product) {
    EXPECT_EQ(product(2, 3, 4), 24);
    EXPECT_EQ(product(5), 5);
}

TEST(FoldExpressionsTest, SumWithOffset) {
    EXPECT_EQ(sum_with_offset(10, 1, 2, 3), 16);
    EXPECT_EQ(sum_with_offset(0, 1, 2, 3), 6);
}

TEST(FoldExpressionsTest, AllTrue) {
    EXPECT_TRUE(all_true(true, true, true));
    EXPECT_FALSE(all_true(true, false, true));
}
