#ifndef STUDYCPP_ALGORITHM_BIT_MANIPULATION_DEMO_H
#define STUDYCPP_ALGORITHM_BIT_MANIPULATION_DEMO_H

#include <algorithm>
#include <string>
#include <vector>

// --- 判断 2 的幂 ---
inline bool is_power_of_two(int n) { return n > 0 && (n & (n - 1)) == 0; }

// --- 计算二进制中 1 的个数（Brian Kernighan 算法） ---
inline int count_bits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}

// --- 只出现一次的数字（其余出现两次） ---
inline int single_number(const std::vector<int>& nums) {
    int result = 0;
    for (int x : nums) result ^= x;
    return result;
}

// --- 交换两个整数（不用临时变量） ---
inline void swap_xor(int& a, int& b) {
    a ^= b;
    b ^= a;
    a ^= b;
}

// --- 反转二进制位（32位） ---
inline uint32_t reverse_bits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; ++i) {
        result = (result << 1) | (n & 1);
        n >>= 1;
    }
    return result;
}

#endif  // STUDYCPP_ALGORITHM_BIT_MANIPULATION_DEMO_H
