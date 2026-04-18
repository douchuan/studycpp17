#include <gtest/gtest.h>

#include "singleton_demo.h"

TEST(SingletonDemoTest, InstanceIsUnique) {
    auto& s1 = Logger::instance();
    auto& s2 = Logger::instance();
    EXPECT_EQ(&s1, &s2);
}

TEST(SingletonDemoTest, LogHistory) {
    Logger::instance().log("hello");
    Logger::instance().log("world");
    const auto& h = Logger::instance().history();
    ASSERT_EQ(h.size(), 2);
    EXPECT_EQ(h[0], "hello");
    EXPECT_EQ(h[1], "world");
}
