#include <gtest/gtest.h>

#include "any_demo.h"

TEST(AnyDemoTest, DescribeInt) {
    std::any a = make_any_int(42);
    EXPECT_EQ(describe_any(a), "int: 42");
}

TEST(AnyDemoTest, DescribeString) {
    std::any a = make_any_str("hello");
    EXPECT_EQ(describe_any(a), "string: hello");
}

TEST(AnyDemoTest, DescribeDouble) {
    std::any a = 3.14;
    EXPECT_EQ(describe_any(a), "double: 3.140000");
}

TEST(AnyDemoTest, SafeGetString) {
    std::any a = 42;
    EXPECT_EQ(safe_get_string(a), "(not a string)");
    std::any b = std::string("world");
    EXPECT_EQ(safe_get_string(b), "world");
}
