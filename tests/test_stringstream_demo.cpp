#include <gtest/gtest.h>

#include "stringstream_demo.h"

TEST(StringStreamDemoTest, Join) {
    EXPECT_EQ(join({"a", "b", "c"}, ','), "a,b,c");
    EXPECT_EQ(join({"hello"}, 'x'), "hello");
    EXPECT_EQ(join({}, ','), "");
}

TEST(StringStreamDemoTest, ParseInt) {
    int n;
    EXPECT_TRUE(parse_int("42", n));
    EXPECT_EQ(n, 42);
    EXPECT_FALSE(parse_int("abc", n));
    EXPECT_FALSE(parse_int("12abc", n));
}

TEST(StringStreamDemoTest, ParseCsvLine) {
    auto values = parse_csv_line("1,2,3");
    EXPECT_EQ(values, (std::vector<int>{1, 2, 3}));
}

TEST(StringStreamDemoTest, FormatRecord) {
    auto result = format_record(1, "Alice", 95.5);
    EXPECT_EQ(result, "ID:1 | Name:Alice | Score:95.5");
}
