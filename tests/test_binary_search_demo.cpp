#include <gtest/gtest.h>

#include "binary_search_demo.h"

TEST(BinarySearchDemoTest, SearchFound) { EXPECT_EQ(binary_search_manual({1, 2, 3, 5, 7}, 5), 3); }
TEST(BinarySearchDemoTest, SearchNotFound) { EXPECT_EQ(binary_search_manual({1, 2, 3}, 4), -1); }
TEST(BinarySearchDemoTest, LowerBound) { EXPECT_EQ(lower_bound_manual({1, 2, 5, 5, 7}, 5), 2); }
TEST(BinarySearchDemoTest, UpperBound) { EXPECT_EQ(upper_bound_manual({1, 2, 5, 5, 7}, 5), 4); }
TEST(BinarySearchDemoTest, FindMinRotated) { EXPECT_EQ(find_min_rotated({4, 5, 1, 2, 3}), 1); }
TEST(BinarySearchDemoTest, SearchRotatedFound) {
    EXPECT_EQ(search_rotated({4, 5, 6, 7, 0, 1, 2}, 0), 4);
}
TEST(BinarySearchDemoTest, SearchRotatedNotFound) {
    EXPECT_EQ(search_rotated({4, 5, 6, 7, 0, 1, 2}, 3), -1);
}
