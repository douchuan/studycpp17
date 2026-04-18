#ifndef STUDYCPP_STD_TUPLE_DEMO_H
#define STUDYCPP_STD_TUPLE_DEMO_H

#include <string>
#include <tuple>

// --- 构造 tuple ---
inline std::tuple<int, std::string, double> make_record() { return {1, "Alice", 95.5}; }

// --- 解包：std::tie ---
inline void unpack_record(const std::tuple<int, std::string, double>& t, int& id, std::string& name,
                          double& score) {
    std::tie(id, name, score) = t;
}

// --- 用 get 访问 ---
inline int get_id(const std::tuple<int, std::string, double>& t) { return std::get<0>(t); }

// --- pair 辅助函数 ---
inline std::pair<int, int> divide_remainder(int dividend, int divisor) {
    return {dividend / divisor, dividend % divisor};
}

// --- std::make_from_tuple ---
struct Config {
    int timeout;
    const char* host;
    Config(int t, const char* h) : timeout(t), host(h) {}
};

inline Config build_config() { return std::make_from_tuple<Config>(std::tuple{30, "localhost"}); }

#endif  // STUDYCPP_STD_TUPLE_DEMO_H
