#include <gtest/gtest.h>

#include "optional_demo.h"

TEST(OptionalDemoTest, DictLookup) {
    std::unordered_map<std::string, int> dict = {{"a", 1}, {"b", 2}};
    auto result = dict_lookup(dict, "a");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 1);
}

TEST(OptionalDemoTest, DictLookupMissing) {
    std::unordered_map<std::string, int> dict = {{"a", 1}};
    auto result = dict_lookup(dict, "z");
    EXPECT_FALSE(result.has_value());
}

TEST(OptionalDemoTest, SafeDivide) {
    auto result = safe_divide(10.0, 2.0);
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(*result, 5.0);
}

TEST(OptionalDemoTest, SafeDivideByZero) {
    auto result = safe_divide(10.0, 0.0);
    EXPECT_FALSE(result.has_value());
}

TEST(OptionalDemoTest, AddOptionals) {
    auto result = add_optionals(3, 4);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 7);
}

TEST(OptionalDemoTest, AddOptionalsWithNullopt) {
    auto result = add_optionals(3, std::nullopt);
    EXPECT_FALSE(result.has_value());
}
