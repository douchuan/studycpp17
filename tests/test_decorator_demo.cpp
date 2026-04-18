#include <gtest/gtest.h>

#include "decorator_demo.h"

TEST(DecoratorDemoTest, PlainText) {
    PlainText plain("hello");
    EXPECT_EQ(plain.read(), "hello");
}

TEST(DecoratorDemoTest, UpperDecorator) {
    auto upper = std::make_unique<UpperDecorator>(std::make_unique<PlainText>("hello"));
    EXPECT_EQ(upper->read(), "HELLO");
}
