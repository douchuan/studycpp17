#include <gtest/gtest.h>

#include "visitor_demo.h"

TEST(VisitorDemoTest, PrintVisitor) {
    PrintVisitor visitor;
    ConcreteElementA a("test");
    ConcreteElementB b(42);
    a.accept(visitor);
    b.accept(visitor);
    EXPECT_EQ(visitor.result(), "A(test) B(42) ");
}
