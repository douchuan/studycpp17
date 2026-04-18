#include <gtest/gtest.h>

#include "chain_of_responsibility_demo.h"

TEST(ChainOfResponsibilityDemoTest, AuthHandled) {
    auto auth = std::make_unique<AuthHandler>();
    EXPECT_EQ(auth->handle("auth"), "authenticated");
}

TEST(ChainOfResponsibilityDemoTest, ChainAuthThenLog) {
    auto auth = std::make_unique<AuthHandler>();
    auto log = std::make_unique<LogHandler>();
    auth->set_next(std::move(log));
    EXPECT_EQ(auth->handle("auth"), "authenticated");
    EXPECT_EQ(auth->handle("log"), "logged");
    EXPECT_EQ(auth->handle("unknown"), "unhandled");
}
