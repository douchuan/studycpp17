#include <gtest/gtest.h>

#include "facade_demo.h"

TEST(FacadeDemoTest, StartComputer) {
    ComputerFacade computer;
    std::string result = computer.start();
    EXPECT_NE(result.find("CPU booted"), std::string::npos);
    EXPECT_NE(result.find("Memory loaded"), std::string::npos);
    EXPECT_NE(result.find("OS read from disk"), std::string::npos);
}
