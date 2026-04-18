#ifndef STUDYCPP_CPP17_FOLD_EXPRESSIONS_DEMO_H
#define STUDYCPP_CPP17_FOLD_EXPRESSIONS_DEMO_H

// --- 一元右折叠：所有参数之和 ---
template <typename... Args>
inline auto sum(Args... args) {
    return (args + ...);
}

// --- 一元左折叠：所有参数之积 ---
template <typename... Args>
inline auto product(Args... args) {
    return (args * ...);
}

// --- 带初始值的二元折叠：和 + 初始偏移 ---
template <typename... Args>
inline auto sum_with_offset(int offset, Args... args) {
    return (offset + ... + args);
}

// --- 逻辑折叠：所有条件为真 ---
template <typename... Args>
inline bool all_true(Args... args) {
    return (args && ...);
}

#endif  // STUDYCPP_CPP17_FOLD_EXPRESSIONS_DEMO_H
