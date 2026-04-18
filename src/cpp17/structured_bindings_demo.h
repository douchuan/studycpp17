#ifndef STUDYCPP_CPP17_STRUCTURED_BINDINGS_DEMO_H
#define STUDYCPP_CPP17_STRUCTURED_BINDINGS_DEMO_H

#include <map>
#include <string>
#include <tuple>
#include <utility>

struct Point {
    int x, y, z;
};

// --- 从结构体解包 ---
inline std::tuple<int, int, int> unpack_point(const Point& p) {
    auto [x, y, z] = p;
    return {x, y, z};
}

// --- 从 pair 解包（map 迭代典型用法） ---
inline std::pair<std::string, int> first_kv(const std::map<std::string, int>& m) {
    auto [key, value] = *m.begin();
    return {key, value};
}

// --- 从 tuple 解包 ---
inline std::tuple<std::string, int, bool> make_person() { return {"Alice", 30, true}; }

#endif  // STUDYCPP_CPP17_STRUCTURED_BINDINGS_DEMO_H
