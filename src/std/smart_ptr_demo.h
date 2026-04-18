#ifndef STUDYCPP_STD_SMART_PTR_DEMO_H
#define STUDYCPP_STD_SMART_PTR_DEMO_H

#include <functional>
#include <memory>
#include <string>
#include <vector>

// --- unique_ptr：独占所有权 ---
inline std::unique_ptr<std::string> make_unique_str(const std::string& s) {
    return std::make_unique<std::string>(s);
}

// --- shared_ptr：共享所有权 ---
inline std::shared_ptr<std::vector<int>> make_shared_vec() {
    return std::make_shared<std::vector<int>>(std::initializer_list<int>{1, 2, 3, 4});
}

// --- custom deleter ---
inline std::unique_ptr<int, std::function<void(int*)>> make_ptr_with_deleter(int value) {
    return {new int(value), [](int* p) { delete p; }};
}

// --- weak_ptr：不增加引用计数 ---
inline std::weak_ptr<int> observe(const std::shared_ptr<int>& sp) { return sp; }

inline bool is_alive(const std::weak_ptr<int>& wp) { return !wp.expired(); }

#endif  // STUDYCPP_STD_SMART_PTR_DEMO_H
