#include <gtest/gtest.h>

#include "variant_demo.h"

TEST(VariantTest, IsString) {
    EXPECT_TRUE(is_string(std::string("hello")));
    EXPECT_FALSE(is_string(42));
    EXPECT_FALSE(is_string(3.14));
}

TEST(VariantTest, IsNumber) {
    EXPECT_TRUE(is_number(42));
    EXPECT_TRUE(is_number(3.14));
    EXPECT_FALSE(is_number(std::string("x")));
}

TEST(VariantTest, ToNumber) {
    EXPECT_DOUBLE_EQ(to_number(42), 42.0);
    EXPECT_DOUBLE_EQ(to_number(2.5), 2.5);
    EXPECT_DOUBLE_EQ(to_number(std::string("x")), 0.0);
}

TEST(VariantTest, Describe) {
    EXPECT_EQ(describe(42), "int: 42");
    EXPECT_EQ(describe(3.14), "double: 3.140000");
    EXPECT_EQ(describe(std::string("hi")), "string: hi");
    EXPECT_EQ(describe(true), "bool: true");
}
