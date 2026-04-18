#include <gtest/gtest.h>

#include "vector_demo.h"

TEST(VectorDemoTest, Sum) {
    EXPECT_EQ(sum({1, 2, 3}), 6);
    EXPECT_EQ(sum({}), 0);
    EXPECT_EQ(sum({-1, 1}), 0);
}

TEST(VectorDemoTest, UniqueCopy) {
    auto result = unique_copy({3, 1, 2, 1, 3});
    std::vector<int> expected = {1, 2, 3};
    EXPECT_EQ(result, expected);
}

TEST(VectorDemoTest, UniqueCopyAlreadyUnique) {
    auto result = unique_copy({1, 2, 3});
    std::vector<int> expected = {1, 2, 3};
    EXPECT_EQ(result, expected);
}

TEST(VectorDemoTest, FindFirst) {
    auto result = find_first(std::vector<int>{1, 3, 5, 7}, [](int x) { return x > 4; });
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 5);
}

TEST(VectorDemoTest, FindFirstNotFound) {
    auto result = find_first(std::vector<int>{1, 2, 3}, [](int x) { return x > 10; });
    EXPECT_FALSE(result.has_value());
}
