#include <gtest/gtest.h>

#include "exception_demo.h"

TEST(ExceptionDemoTest, CheckedDivide) {
    EXPECT_DOUBLE_EQ(checked_divide(10.0, 2.0), 5.0);
    EXPECT_THROW(checked_divide(10.0, 0.0), std::invalid_argument);
}

TEST(ExceptionDemoTest, ClampRange) {
    EXPECT_EQ(clamp_range(5, 1, 10), 5);
    EXPECT_THROW(clamp_range(20, 1, 10), std::out_of_range);
    EXPECT_THROW(clamp_range(0, 1, 10), std::out_of_range);
}

TEST(ExceptionDemoTest, ValidatePositive) {
    EXPECT_NO_THROW(validate_positive(1));
    EXPECT_THROW(validate_positive(0), ValidationError);
    EXPECT_THROW(validate_positive(-1), ValidationError);
}

TEST(ExceptionDemoTest, TryParseInt) {
    int result;
    EXPECT_TRUE(try_parse_int("42", result));
    EXPECT_EQ(result, 42);
    EXPECT_FALSE(try_parse_int("abc", result));
    EXPECT_FALSE(try_parse_int("", result));
}
