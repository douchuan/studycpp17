#include <gtest/gtest.h>

#include "bridge_demo.h"

TEST(BridgeDemoTest, CircleWithVectorRenderer) {
    CircleShape shape(std::make_unique<VectorRenderer>(), 5.0);
    EXPECT_EQ(shape.draw(), "Vector circle(r=5.000000)");
}

TEST(BridgeDemoTest, CircleWithRasterRenderer) {
    CircleShape shape(std::make_unique<RasterRenderer>(), 3.0);
    EXPECT_EQ(shape.draw(), "Raster circle(r=3.000000)");
}
