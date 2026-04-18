#include <gtest/gtest.h>

#include "bit_manipulation_demo.h"

TEST(BitManipulationDemoTest, IsPowerOfTwo) {
    EXPECT_TRUE(is_power_of_two(1));
    EXPECT_TRUE(is_power_of_two(16));
    EXPECT_FALSE(is_power_of_two(14));
}
TEST(BitManipulationDemoTest, CountBits) { EXPECT_EQ(count_bits(13), 3); }
TEST(BitManipulationDemoTest, SingleNumber) { EXPECT_EQ(single_number({4, 1, 2, 1, 2}), 4); }
TEST(BitManipulationDemoTest, SwapXor) {
    int a = 3, b = 5;
    swap_xor(a, b);
    EXPECT_EQ(a, 5);
    EXPECT_EQ(b, 3);
}
