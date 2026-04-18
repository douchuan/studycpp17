#ifndef STUDYCPP_CPP17_APPLY_DEMO_H
#define STUDYCPP_CPP17_APPLY_DEMO_H

#include <functional>
#include <string>
#include <tuple>

// --- std::apply：将 tuple 展开为函数参数 ---
inline int add3(int a, int b, int c) { return a + b + c; }

inline int apply_add(std::tuple<int, int, int> t) { return std::apply(add3, t); }

// --- 配合 lambda ---
inline std::string greet(const std::string& name, int age) {
    return name + " is " + std::to_string(age);
}

inline std::string apply_greet(std::tuple<std::string, int> t) { return std::apply(greet, t); }

// --- std::make_from_tuple：构造对象 ---
struct Point {
    int x, y;
    Point(int x_, int y_) : x(x_), y(y_) {}
    std::string label() const { return "(" + std::to_string(x) + "," + std::to_string(y) + ")"; }
};

inline std::string make_point_label(std::tuple<int, int> t) {
    auto p = std::make_from_tuple<Point>(t);
    return p.label();
}

#endif  // STUDYCPP_CPP17_APPLY_DEMO_H
