#ifndef STUDYCPP_CPP17_VARIANT_DEMO_H
#define STUDYCPP_CPP17_VARIANT_DEMO_H

#include <string>
#include <variant>
#include <vector>

// 用 variant 表示多种类型的联合
using JsonValue = std::variant<int, double, std::string, bool>;

// --- 构造 ---
inline JsonValue make_int(int v) { return v; }
inline JsonValue make_str(const std::string& v) { return v; }

// --- 类型检查 ---
inline bool is_string(const JsonValue& v) { return std::holds_alternative<std::string>(v); }

inline bool is_number(const JsonValue& v) {
    return std::holds_alternative<int>(v) || std::holds_alternative<double>(v);
}

// --- 安全取值 ---
inline double to_number(const JsonValue& v) {
    if (auto p = std::get_if<int>(&v)) return *p;
    if (auto p = std::get_if<double>(&v)) return *p;
    return 0.0;
}

// --- std::visit 多态访问 ---
struct TypeDescriber {
    std::string operator()(int v) const { return "int: " + std::to_string(v); }
    std::string operator()(double v) const { return "double: " + std::to_string(v); }
    std::string operator()(const std::string& v) const { return "string: " + v; }
    std::string operator()(bool v) const { return "bool: " + std::string(v ? "true" : "false"); }
};

inline std::string describe(const JsonValue& v) { return std::visit(TypeDescriber{}, v); }

#endif  // STUDYCPP_CPP17_VARIANT_DEMO_H
