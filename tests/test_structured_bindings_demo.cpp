#include <gtest/gtest.h>

#include "structured_bindings_demo.h"

TEST(StructuredBindingsTest, UnpackPoint) {
    Point p{1, 2, 3};
    auto [x, y, z] = unpack_point(p);
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, 2);
    EXPECT_EQ(z, 3);
}

TEST(StructuredBindingsTest, FirstKv) {
    std::map<std::string, int> m = {{"a", 1}, {"b", 2}};
    auto [k, v] = first_kv(m);
    EXPECT_EQ(k, "a");
    EXPECT_EQ(v, 1);
}

TEST(StructuredBindingsTest, MakePerson) {
    auto [name, age, active] = make_person();
    EXPECT_EQ(name, "Alice");
    EXPECT_EQ(age, 30);
    EXPECT_TRUE(active);
}
