#include <gtest/gtest.h>

#include "iterator_demo.h"

TEST(IteratorDemoTest, NthElement) { EXPECT_EQ(nth_element({10, 20, 30}, 1), 20); }

TEST(IteratorDemoTest, Next) {
    std::vector<int> v = {1, 2, 3, 4};
    auto it = find_n_steps(v.begin(), 2);
    EXPECT_EQ(*it, 3);
}

TEST(IteratorDemoTest, CopyAndDouble) {
    auto result = copy_and_double({1, 2, 3});
    EXPECT_EQ(result, (std::vector<int>{2, 4, 6}));
}

TEST(IteratorDemoTest, DistanceFound) { EXPECT_EQ(count_until({10, 20, 30}, 20), 1); }

TEST(IteratorDemoTest, DistanceNotFound) {
    // distance to end when not found
    EXPECT_EQ(count_until({10, 20, 30}, 99), 3);
}

TEST(IteratorDemoTest, SumViaForEach) { EXPECT_EQ(sum_via_for_each({1, 2, 3, 4}), 10); }
