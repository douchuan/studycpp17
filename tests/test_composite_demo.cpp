#include <gtest/gtest.h>

#include "composite_demo.h"

TEST(CompositeDemoTest, FileDisplay) {
    FileNode f("hello.txt");
    EXPECT_EQ(f.display(), "- hello.txt");
}

TEST(CompositeDemoTest, DirectoryWithFiles) {
    auto dir = std::make_unique<DirectoryNode>("src");
    dir->add(std::make_unique<FileNode>("main.cpp"));
    dir->add(std::make_unique<FileNode>("util.cpp"));
    std::string s = dir->display();
    EXPECT_NE(s.find("main.cpp"), std::string::npos);
    EXPECT_NE(s.find("util.cpp"), std::string::npos);
}
