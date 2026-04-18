#include <gtest/gtest.h>

#include "set_demo.h"

TEST(SetDemoTest, UniqueSet) {
    auto s = unique_set({3, 1, 2, 1, 3});
    std::set<int> expected = {1, 2, 3};
    EXPECT_EQ(s, expected);
}

TEST(SetDemoTest, Intersection) {
    std::set<int> a = {1, 2, 3};
    std::set<int> b = {2, 3, 4};
    auto inter = set_intersection(a, b);
    EXPECT_EQ(inter, (std::set<int>{2, 3}));
}

TEST(SetDemoTest, Difference) {
    std::set<int> a = {1, 2, 3, 4};
    std::set<int> b = {3, 4, 5};
    auto diff = set_difference(a, b);
    EXPECT_EQ(diff, (std::set<int>{1, 2}));
}

TEST(SetDemoTest, Contains) {
    std::unordered_set<std::string> s = {"a", "b"};
    EXPECT_TRUE(contains(s, "a"));
    EXPECT_FALSE(contains(s, "c"));
}
