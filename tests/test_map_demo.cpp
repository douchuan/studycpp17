#include <gtest/gtest.h>

#include "map_demo.h"

TEST(MapDemoTest, BuildMap) {
    auto m = build_map();
    ASSERT_EQ(m.size(), 3u);
    // map is ordered, so first key is alphabetically first
    EXPECT_EQ(m.begin()->first, "apple");
}

TEST(MapDemoTest, WordCount) {
    auto counts = word_count({"a", "b", "a", "a", "c"});
    EXPECT_EQ(counts["a"], 3);
    EXPECT_EQ(counts["b"], 1);
    EXPECT_EQ(counts["c"], 1);
}

TEST(MapDemoTest, GetOrDefaultFound) {
    std::unordered_map<std::string, int> m = {{"x", 10}};
    EXPECT_EQ(get_or_default(m, "x", 0), 10);
}

TEST(MapDemoTest, GetOrDefaultMissing) {
    std::unordered_map<std::string, int> m = {{"x", 10}};
    EXPECT_EQ(get_or_default(m, "y", 42), 42);
}
