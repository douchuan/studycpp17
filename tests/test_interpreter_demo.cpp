#include <gtest/gtest.h>

#include "interpreter_demo.h"

TEST(InterpreterDemoTest, TerminalMatch) {
    TerminalExpression expr("hello");
    EXPECT_TRUE(expr.interpret("say hello world"));
    EXPECT_FALSE(expr.interpret("say hi"));
}

TEST(InterpreterDemoTest, OrExpression) {
    auto e = std::make_unique<OrExpression>(std::make_unique<TerminalExpression>("hello"),
                                            std::make_unique<TerminalExpression>("world"));
    EXPECT_TRUE(e->interpret("hello"));
    EXPECT_TRUE(e->interpret("world"));
    EXPECT_FALSE(e->interpret("bye"));
}

TEST(InterpreterDemoTest, AndExpression) {
    auto e = std::make_unique<AndExpression>(std::make_unique<TerminalExpression>("hello"),
                                             std::make_unique<TerminalExpression>("world"));
    EXPECT_TRUE(e->interpret("hello world"));
    EXPECT_FALSE(e->interpret("hello"));
}
