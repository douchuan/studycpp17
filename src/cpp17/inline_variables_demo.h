#ifndef STUDYCPP_CPP17_INLINE_VARIABLES_DEMO_H
#define STUDYCPP_CPP17_INLINE_VARIABLES_DEMO_H

// --- inline 变量：C++17 允许在头文件中定义全局变量 ---
inline constexpr double PI = 3.14159265358979323846;
inline constexpr double E = 2.71828182845904523536;

// --- 全局计数器，避免 ODR 冲突 ---
inline int global_counter = 0;
inline void increment_counter() { ++global_counter; }
inline int get_counter() { return global_counter; }

// --- 模板变量（C++14 引入，C++17 可 inline） ---
template <typename T>
inline constexpr bool is_special_v = false;

template <>
inline constexpr bool is_special_v<int> = true;

template <>
inline constexpr bool is_special_v<double> = true;

#endif  // STUDYCPP_CPP17_INLINE_VARIABLES_DEMO_H
