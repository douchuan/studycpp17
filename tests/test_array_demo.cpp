#include <gtest/gtest.h>

#include "array_demo.h"

TEST(ArrayDemoTest, MakeArray) {
    auto a = make_array();
    EXPECT_EQ(a.size(), 5u);
    EXPECT_EQ(a[0], 3);
}

TEST(ArrayDemoTest, ArraySum) { EXPECT_EQ(array_sum(make_array()), 14); }

TEST(ArrayDemoTest, ArrayMax) { EXPECT_EQ(array_max(make_array()), 5); }

TEST(ArrayDemoTest, ArraySort) {
    auto a = make_array();
    array_sort(a);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[4], 5);
}

TEST(ArrayDemoTest, FilledArray) {
    auto a = filled_array(7);
    for (int x : a) EXPECT_EQ(x, 7);
}
