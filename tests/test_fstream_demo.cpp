#include <gtest/gtest.h>

#include "fstream_demo.h"

class FstreamDemoTest : public ::testing::Test {
   protected:
    void SetUp() override {
        path = "/tmp/studycpp_test_";
        path += std::to_string(rand());
    }
    std::string path;
};

TEST_F(FstreamDemoTest, WriteAndRead) {
    ASSERT_TRUE(write_file(path, "hello"));
    EXPECT_EQ(read_file(path), "hello");
}

TEST_F(FstreamDemoTest, ReadLines) {
    write_file(path, "a\nb\nc");
    auto lines = read_lines(path);
    ASSERT_EQ(lines.size(), 3u);
    EXPECT_EQ(lines[0], "a");
    EXPECT_EQ(lines[2], "c");
}

TEST_F(FstreamDemoTest, Append) {
    write_file(path, "first\n");
    append_file(path, "second\n");
    auto lines = read_lines(path);
    ASSERT_EQ(lines.size(), 2u);
    EXPECT_EQ(lines[0], "first");
    EXPECT_EQ(lines[1], "second");
}

TEST_F(FstreamDemoTest, ReadNonexistent) {
    EXPECT_EQ(read_file("/tmp/nonexistent_file_12345"), "");
}
