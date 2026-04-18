#include <gtest/gtest.h>

#include "flyweight_demo.h"

TEST(FlyweightDemoTest, SharedFont) {
    FontFactory factory;
    auto f1 = factory.get_font("Arial");
    auto f2 = factory.get_font("Arial");
    EXPECT_EQ(f1, f2);
    EXPECT_EQ(*f1, "Arial");
}

TEST(FlyweightDemoTest, DifferentFonts) {
    FontFactory factory;
    auto f1 = factory.get_font("Arial");
    auto f2 = factory.get_font("Times");
    EXPECT_NE(f1, f2);
}
