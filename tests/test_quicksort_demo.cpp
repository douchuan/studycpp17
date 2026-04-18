#include <gtest/gtest.h>

#include "quicksort_demo.h"

TEST(QuickSortDemoTest, Sort) {
    std::vector<int> a = {5, 2, 8, 1, 9};
    quick_sort(a);
    EXPECT_EQ(a, (std::vector<int>{1, 2, 5, 8, 9}));
}
TEST(QuickSortDemoTest, QuickSelect) { EXPECT_EQ(quick_select({3, 2, 1, 5, 6, 4}, 2), 5); }
