#ifndef STUDYCPP_PATTERN_CHAIN_OF_RESPONSIBILITY_H
#define STUDYCPP_PATTERN_CHAIN_OF_RESPONSIBILITY_H

// === Chain of Responsibility (责任链模式) ===
// 使用场景：HTTP 中间件链（认证→日志→路由）、审批流程（主管→经理→总监）、
// 事件冒泡处理、日志级别过滤。
#include <memory>
#include <string>

class Handler {
   public:
    virtual ~Handler() = default;
    void set_next(std::unique_ptr<Handler> next) { next_ = std::move(next); }
    virtual std::string handle(const std::string& request) = 0;

   protected:
    Handler* next() const { return next_.get(); }

   private:
    std::unique_ptr<Handler> next_;
};

class AuthHandler : public Handler {
   public:
    std::string handle(const std::string& request) override {
        if (request == "auth") return "authenticated";
        if (auto n = next()) return n->handle(request);
        return "unhandled";
    }
};

class LogHandler : public Handler {
   public:
    std::string handle(const std::string& request) override {
        if (request == "log") return "logged";
        if (auto n = next()) return n->handle(request);
        return "unhandled";
    }
};

#endif  // STUDYCPP_PATTERN_CHAIN_OF_RESPONSIBILITY_H
