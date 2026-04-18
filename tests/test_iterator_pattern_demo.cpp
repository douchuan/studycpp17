#include <gtest/gtest.h>

#include "iterator_pattern_demo.h"

TEST(IteratorPatternDemoTest, IterateAllElements) {
    std::vector<int> nums = {10, 20, 30};
    VectorIterator<int> it(nums);
    EXPECT_TRUE(it.has_next());
    EXPECT_EQ(it.next(), 10);
    EXPECT_EQ(it.next(), 20);
    EXPECT_EQ(it.next(), 30);
    EXPECT_FALSE(it.has_next());
}

TEST(IteratorPatternDemoTest, EmptyVector) {
    std::vector<int> empty;
    VectorIterator<int> it(empty);
    EXPECT_FALSE(it.has_next());
}
