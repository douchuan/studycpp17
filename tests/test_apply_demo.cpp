#include <gtest/gtest.h>

#include "apply_demo.h"

TEST(ApplyDemoTest, ApplyAdd) { EXPECT_EQ(apply_add({1, 2, 3}), 6); }

TEST(ApplyDemoTest, ApplyGreet) {
    auto result = apply_greet({"Bob", 25});
    EXPECT_EQ(result, "Bob is 25");
}

TEST(ApplyDemoTest, MakePointLabel) {
    auto result = make_point_label({10, 20});
    EXPECT_EQ(result, "(10,20)");
}
