#include <gtest/gtest.h>

#include "abstract_factory_demo.h"

TEST(AbstractFactoryDemoTest, LightFactoryCreatesLightComponents) {
    LightFactory factory;
    auto btn = factory.create_button();
    auto cb = factory.create_checkbox();
    EXPECT_EQ(btn->render(), "[LightButton]");
    EXPECT_EQ(cb->render(), "[LightCheckbox]");
}

TEST(AbstractFactoryDemoTest, DarkFactoryCreatesDarkComponents) {
    DarkFactory factory;
    auto btn = factory.create_button();
    auto cb = factory.create_checkbox();
    EXPECT_EQ(btn->render(), "[DarkButton]");
    EXPECT_EQ(cb->render(), "[DarkCheckbox]");
}
