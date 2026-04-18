#include <gtest/gtest.h>

#include "function_demo.h"

TEST(FunctionDemoTest, Adder) {
    auto add = make_adder();
    EXPECT_EQ(add(2, 3), 5);
}

TEST(FunctionDemoTest, AggregatorSum) {
    auto fn = make_aggregator("sum");
    EXPECT_EQ(fn({1, 2, 3}), 6);
    EXPECT_EQ(fn({}), 0);
}

TEST(FunctionDemoTest, AggregatorMax) {
    auto fn = make_aggregator("max");
    EXPECT_EQ(fn({3, 1, 4}), 4);
}

TEST(FunctionDemoTest, AggregatorUnknown) {
    auto fn = make_aggregator("avg");
    EXPECT_EQ(fn({1, 2, 3}), 0);
}

TEST(FunctionDemoTest, MapVec) {
    auto result = map_vec({1, 2, 3}, [](int x) { return x + 10; });
    EXPECT_EQ(result, (std::vector<int>{11, 12, 13}));
}

TEST(FunctionDemoTest, Doubler) {
    auto doubler = make_doubler();
    EXPECT_EQ(doubler(5), 10);
}
