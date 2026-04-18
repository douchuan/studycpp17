#include <gtest/gtest.h>

#include "if_constexpr_demo.h"

TEST(IfConstexprTest, DescribeIntegral) {
    std::string result = describe(42);
    EXPECT_EQ(result, "integral: 42");
}

TEST(IfConstexprTest, DescribeFloat) {
    // to_string produces platform-dependent precision, check prefix only
    std::string result = describe(3.14);
    EXPECT_EQ(result.substr(0, 14), "floating-point");
}

TEST(IfConstexprTest, DescribeString) {
    std::string result = describe(std::string("hello"));
    EXPECT_EQ(result, "string: hello");
}

TEST(IfConstexprTest, IsContainerLike) {
    EXPECT_FALSE(is_container_like<int>());
    EXPECT_FALSE(is_container_like<double>());
    EXPECT_TRUE(is_container_like<std::string>());
}
