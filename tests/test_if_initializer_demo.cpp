#include <gtest/gtest.h>

#include "if_initializer_demo.h"

TEST(IfInitializerTest, MapLookupFound) {
    std::map<std::string, int> m = {{"x", 10}};
    EXPECT_EQ(map_lookup(m, "x"), "x = 10");
}

TEST(IfInitializerTest, MapLookupNotFound) {
    std::map<std::string, int> m = {{"x", 10}};
    EXPECT_EQ(map_lookup(m, "y"), "y not found");
}

TEST(IfInitializerTest, ClassifyStatus) {
    EXPECT_EQ(classify_status(200), "OK");
    EXPECT_EQ(classify_status(404), "Not Found");
    EXPECT_EQ(classify_status(500), "Server Error");
    EXPECT_EQ(classify_status(999), "Unknown (999)");
}

TEST(IfInitializerTest, SafeDivide) {
    EXPECT_EQ(safe_divide_str(10.0, 2.0), "5.000000");
    EXPECT_EQ(safe_divide_str(10.0, 0.0), "division by zero");
}
