#include <gtest/gtest.h>

#include "inline_variables_demo.h"

TEST(InlineVariablesTest, Constants) { EXPECT_DOUBLE_EQ(PI, 3.14159265358979323846); }

TEST(InlineVariablesTest, Counter) {
    global_counter = 0;
    EXPECT_EQ(get_counter(), 0);
    increment_counter();
    increment_counter();
    EXPECT_EQ(get_counter(), 2);
}

TEST(InlineVariablesTest, IsSpecial) {
    EXPECT_TRUE(is_special_v<int>);
    EXPECT_TRUE(is_special_v<double>);
    EXPECT_FALSE(is_special_v<float>);
    EXPECT_FALSE(is_special_v<std::string>);
}
