#include <gtest/gtest.h>

#include "factory_method_demo.h"

TEST(FactoryMethodDemoTest, FactoryACreatesProductA) {
    FactoryA factory;
    auto p = factory.create();
    EXPECT_EQ(p->name(), "ProductA");
}

TEST(FactoryMethodDemoTest, FactoryBCreatesProductB) {
    FactoryB factory;
    auto p = factory.create();
    EXPECT_EQ(p->name(), "ProductB");
}
