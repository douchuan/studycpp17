#ifndef STUDYCPP_CPP17_IF_INITIALIZER_DEMO_H
#define STUDYCPP_CPP17_IF_INITIALIZER_DEMO_H

#include <map>
#include <optional>
#include <string>

// --- map 查找：在 if 条件中声明迭代器 ---
inline std::string map_lookup(const std::map<std::string, int>& m, const std::string& key) {
    if (auto it = m.find(key); it != m.end()) {
        return key + " = " + std::to_string(it->second);
    }
    return key + " not found";
}

// --- switch with initializer ---
inline std::string classify_status(int code) {
    switch (auto status = code; status) {
        case 200:
            return "OK";
        case 404:
            return "Not Found";
        case 500:
            return "Server Error";
        default:
            return "Unknown (" + std::to_string(status) + ")";
    }
}

// --- optional 配合 if initializer ---
inline std::string safe_divide_str(double a, double b) {
    if (auto result = (b == 0.0 ? std::optional<double>{} : std::optional<double>{a / b}); result) {
        return std::to_string(*result);
    }
    return "division by zero";
}

#endif  // STUDYCPP_CPP17_IF_INITIALIZER_DEMO_H
