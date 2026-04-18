#ifndef STUDYCPP_CPP17_IF_CONSTEXPR_DEMO_H
#define STUDYCPP_CPP17_IF_CONSTEXPR_DEMO_H

#include <string>
#include <type_traits>

// --- constexpr if：编译期分支，替代模板特化 ---
template <typename T>
inline std::string describe(const T& value) {
    if constexpr (std::is_integral_v<T>) {
        return "integral: " + std::to_string(value);
    } else if constexpr (std::is_floating_point_v<T>) {
        return "floating-point: " + std::to_string(value);
    } else if constexpr (std::is_same_v<T, std::string>) {
        return "string: " + value;
    } else {
        return "other type";
    }
}

// --- 类型特征判断 + constexpr if ---
template <typename T>
inline bool is_container_like() {
    // 仅为演示：简单判断是否为基本容器类型
    if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double>) {
        return false;
    } else {
        return true;
    }
}

#endif  // STUDYCPP_CPP17_IF_CONSTEXPR_DEMO_H
