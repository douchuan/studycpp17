#include <gtest/gtest.h>

#include "command_demo.h"

TEST(CommandDemoTest, LightOn) {
    Light light;
    LightOnCommand cmd(&light);
    cmd.execute();
    EXPECT_TRUE(light.is_on());
}

TEST(CommandDemoTest, UndoLightOn) {
    Light light;
    LightOnCommand cmd(&light);
    cmd.execute();
    cmd.undo();
    EXPECT_FALSE(light.is_on());
}

TEST(CommandDemoTest, InvokerHistory) {
    Light light;
    CommandInvoker invoker;
    invoker.execute(std::make_unique<LightOnCommand>(&light));
    EXPECT_TRUE(light.is_on());
    invoker.undo_last();
    EXPECT_FALSE(light.is_on());
}
