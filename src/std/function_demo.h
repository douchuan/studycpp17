#ifndef STUDYCPP_STD_FUNCTION_DEMO_H
#define STUDYCPP_STD_FUNCTION_DEMO_H

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

// --- std::function：存储可调用对象 ---
inline std::function<int(int, int)> make_adder() {
    return [](int a, int b) { return a + b; };
}

// --- 存储不同策略，运行时选择 ---
inline std::function<int(const std::vector<int>&)> make_aggregator(const std::string& strategy) {
    if (strategy == "sum") {
        return [](const std::vector<int>& v) {
            int s = 0;
            for (int x : v) s += x;
            return s;
        };
    }
    if (strategy == "max") {
        return [](const std::vector<int>& v) {
            int m = v.empty() ? 0 : v[0];
            for (int x : v) m = std::max(m, x);
            return m;
        };
    }
    return [](const std::vector<int>&) { return 0; };
}

// --- 函数作为参数 ---
inline std::vector<int> map_vec(const std::vector<int>& v, std::function<int(int)> fn) {
    std::vector<int> result;
    std::transform(v.begin(), v.end(), std::back_inserter(result), std::move(fn));
    return result;
}

// --- lambda 替代 std::bind ---
inline int multiply(int a, int b) { return a * b; }

inline auto make_doubler() {
    return [](int x) { return multiply(x, 2); };
}

#endif  // STUDYCPP_STD_FUNCTION_DEMO_H
