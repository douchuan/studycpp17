#ifndef STUDYCPP_PATTERN_SINGLETON_H
#define STUDYCPP_PATTERN_SINGLETON_H

// === Singleton (单例模式) ===
// 使用场景：全局配置管理器、日志器、数据库连接池等需要唯一实例的场景。
#include <string>
#include <vector>

class Logger {
   public:
    static Logger& instance() {
        static Logger inst;
        return inst;
    }
    void log(const std::string& msg) { messages.push_back(msg); }
    const std::vector<std::string>& history() const { return messages; }

   private:
    Logger() = default;
    std::vector<std::string> messages;
};

#endif  // STUDYCPP_PATTERN_SINGLETON_H
