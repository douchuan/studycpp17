#ifndef STUDYCPP_STD_EXCEPTION_DEMO_H
#define STUDYCPP_STD_EXCEPTION_DEMO_H

#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// --- 自定义异常 ---
class ValidationError : public std::runtime_error {
   public:
    explicit ValidationError(const std::string& msg) : std::runtime_error(msg) {}
};

// --- 可能抛出的函数 ---
inline double checked_divide(double a, double b) {
    if (b == 0.0) throw std::invalid_argument("division by zero");
    return a / b;
}

// --- 范围校验 ---
inline int clamp_range(int value, int min_val, int max_val) {
    if (value < min_val || value > max_val) {
        std::ostringstream oss;
        oss << "value " << value << " out of range [" << min_val << ", " << max_val << "]";
        throw std::out_of_range(oss.str());
    }
    return value;
}

// --- 业务校验 ---
inline void validate_positive(int value) {
    if (value <= 0) {
        throw ValidationError("expected positive value, got " + std::to_string(value));
    }
}

// --- 不抛异常的版本（返回错误码） ---
inline bool try_parse_int(const std::string& str, int& result) noexcept {
    try {
        size_t pos = 0;
        result = std::stoi(str, &pos);
        return pos == str.size();
    } catch (...) {
        return false;
    }
}

#endif  // STUDYCPP_STD_EXCEPTION_DEMO_H
