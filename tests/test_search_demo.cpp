#include <gtest/gtest.h>

#include "search_demo.h"

TEST(SearchDemoTest, BinarySearch) {
    std::vector<int> sorted = {1, 2, 3, 4, 5};
    EXPECT_TRUE(binary_search(sorted, 3));
    EXPECT_FALSE(binary_search(sorted, 0));
    EXPECT_FALSE(binary_search(sorted, 6));
}

TEST(SearchDemoTest, Minmax) {
    auto [min_val, max_val] = minmax({3, 1, 4, 1, 5});
    EXPECT_EQ(min_val, 1);
    EXPECT_EQ(max_val, 5);
}

TEST(SearchDemoTest, CountValue) {
    EXPECT_EQ(count_value({1, 2, 2, 3, 2}, 2), 3);
    EXPECT_EQ(count_value({1, 2, 3}, 4), 0);
    EXPECT_EQ(count_value({}, 1), 0);
}
