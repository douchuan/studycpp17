#include <gtest/gtest.h>

#include "strategy_demo.h"

TEST(StrategyDemoTest, BubbleSort) {
    std::vector<int> data = {5, 3, 4, 1, 2};
    SortContext ctx(std::make_unique<BubbleSort>());
    ctx.sort(data);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(StrategyDemoTest, QuickSort) {
    std::vector<int> data = {5, 3, 4, 1, 2};
    SortContext ctx(std::make_unique<QuickSortStrategy>());
    ctx.sort(data);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(StrategyDemoTest, SwitchStrategy) {
    SortContext ctx(std::make_unique<BubbleSort>());
    EXPECT_EQ(ctx.strategy_name(), "BubbleSort");
    ctx.set_strategy(std::make_unique<QuickSortStrategy>());
    EXPECT_EQ(ctx.strategy_name(), "QuickSort");
}
