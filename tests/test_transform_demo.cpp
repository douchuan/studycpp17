#include <gtest/gtest.h>

#include "transform_demo.h"

TEST(TransformDemoTest, Transform) {
    auto result = transform(std::vector<int>{1, 2, 3}, [](int x) { return x * 2; });
    std::vector<int> expected = {2, 4, 6};
    EXPECT_EQ(result, expected);
}

TEST(TransformDemoTest, TransformEmpty) {
    auto result = transform(std::vector<int>{}, [](int x) { return x * 2; });
    EXPECT_TRUE(result.empty());
}

TEST(TransformDemoTest, Filter) {
    auto result = filter(std::vector<int>{1, 2, 3, 4, 5}, [](int x) { return x % 2 == 0; });
    std::vector<int> expected = {2, 4};
    EXPECT_EQ(result, expected);
}

TEST(TransformDemoTest, FilterNone) {
    auto result = filter(std::vector<int>{1, 3, 5}, [](int x) { return x % 2 == 0; });
    EXPECT_TRUE(result.empty());
}

TEST(TransformDemoTest, ReduceSum) {
    auto result = reduce(std::vector<int>{1, 2, 3}, 0, std::plus<int>());
    EXPECT_EQ(result, 6);
}

TEST(TransformDemoTest, ReduceProduct) {
    auto result = reduce(std::vector<int>{1, 2, 3, 4}, 1, std::multiplies<int>());
    EXPECT_EQ(result, 24);
}
