#include <gtest/gtest.h>

#include "mergesort_demo.h"

TEST(MergeSortDemoTest, Sort) {
    std::vector<int> a = {5, 2, 8, 1, 9};
    merge_sort(a);
    EXPECT_EQ(a, (std::vector<int>{1, 2, 5, 8, 9}));
}
TEST(MergeSortDemoTest, CountInversions) { EXPECT_EQ(count_inversions({2, 4, 1, 3, 5}), 3); }
