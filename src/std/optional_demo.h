#ifndef STUDYCPP_STD_OPTIONAL_DEMO_H
#define STUDYCPP_STD_OPTIONAL_DEMO_H

#include <optional>
#include <string>
#include <unordered_map>

// --- 模拟字典查找 ---
inline std::optional<int> dict_lookup(const std::unordered_map<std::string, int>& dict,
                                      const std::string& key) {
    auto it = dict.find(key);
    if (it != dict.end()) return it->second;
    return std::nullopt;
}

// --- 安全除法 ---
inline std::optional<double> safe_divide(double a, double b) {
    if (b == 0.0) return std::nullopt;
    return a / b;
}

// --- 链式操作：两个 optional 相加 ---
inline std::optional<int> add_optionals(std::optional<int> a, std::optional<int> b) {
    if (a && b) return *a + *b;
    return std::nullopt;
}

#endif  // STUDYCPP_STD_OPTIONAL_DEMO_H
