#include <gtest/gtest.h>

#include "prototype_demo.h"

TEST(PrototypeDemoTest, CloneCircle) {
    Circle original(5.0, "red");
    auto cloned = original.clone();
    EXPECT_EQ(original.desc(), cloned->desc());
    EXPECT_NE(&original, cloned.get());
}
