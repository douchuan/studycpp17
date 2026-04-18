#include <gtest/gtest.h>

#include "sort_demo.h"

TEST(SortDemoTest, SortAsc) {
    auto result = sort_asc({3, 1, 4, 1, 5});
    std::vector<int> expected = {1, 1, 3, 4, 5};
    EXPECT_EQ(result, expected);
}

TEST(SortDemoTest, SortDesc) {
    auto result = sort_desc({3, 1, 4});
    std::vector<int> expected = {4, 3, 1};
    EXPECT_EQ(result, expected);
}

TEST(SortDemoTest, TopK) {
    auto result = top_k({5, 2, 8, 1, 9}, 3);
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result, (std::vector<int>{1, 2, 5}));
}

TEST(SortDemoTest, TopKZero) {
    auto result = top_k({1, 2, 3}, 0);
    EXPECT_TRUE(result.empty());
}

TEST(SortDemoTest, TopKAll) {
    auto result = top_k({3, 1, 2}, 10);
    std::vector<int> expected = {1, 2, 3};
    EXPECT_EQ(result, expected);
}

TEST(SortDemoTest, IsSorted) {
    EXPECT_TRUE(is_sorted({1, 2, 3}));
    EXPECT_FALSE(is_sorted({3, 1, 2}));
    EXPECT_TRUE(is_sorted({}));
    EXPECT_TRUE(is_sorted({1}));
}
