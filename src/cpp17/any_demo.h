#ifndef STUDYCPP_CPP17_ANY_DEMO_H
#define STUDYCPP_CPP17_ANY_DEMO_H

#include <any>
#include <string>
#include <typeinfo>
#include <vector>

// --- 存放任意类型 ---
inline std::any make_any_int(int v) { return {v}; }
inline std::any make_any_str(const std::string& v) { return {v}; }

// --- 类型信息 ---
inline std::string any_type_name(const std::any& a) { return a.type().name(); }

// --- 安全取值 ---
inline std::string safe_get_string(const std::any& a) {
    try {
        if (a.type() == typeid(std::string)) {
            return std::any_cast<std::string>(a);
        }
    } catch (const std::bad_any_cast&) {  // NOLINT(bugprone-empty-catch)
        // Type matched typeid but any_cast still failed — treat as non-string
    }
    return "(not a string)";
}

// --- 异构容器 ---
inline std::string describe_any(const std::any& a) {
    if (a.type() == typeid(int)) return "int: " + std::to_string(std::any_cast<int>(a));
    if (a.type() == typeid(double)) return "double: " + std::to_string(std::any_cast<double>(a));
    if (a.type() == typeid(std::string)) return "string: " + std::any_cast<std::string>(a);
    return "unknown";
}

#endif  // STUDYCPP_CPP17_ANY_DEMO_H
