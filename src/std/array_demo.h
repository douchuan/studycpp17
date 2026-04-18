#ifndef STUDYCPP_STD_ARRAY_DEMO_H
#define STUDYCPP_STD_ARRAY_DEMO_H

#include <algorithm>
#include <array>
#include <numeric>

// --- 固定大小数组，编译期已知 ---
inline std::array<int, 5> make_array() { return {3, 1, 4, 1, 5}; }

// --- 求和 ---
inline int array_sum(const std::array<int, 5>& a) { return std::accumulate(a.begin(), a.end(), 0); }

// --- 最大值 ---
inline int array_max(const std::array<int, 5>& a) { return *std::max_element(a.begin(), a.end()); }

// --- 原地排序 ---
inline void array_sort(std::array<int, 5>& a) { std::sort(a.begin(), a.end()); }

// --- 填充 ---
inline std::array<int, 5> filled_array(int value) {
    std::array<int, 5> a;
    a.fill(value);
    return a;
}

#endif  // STUDYCPP_STD_ARRAY_DEMO_H
