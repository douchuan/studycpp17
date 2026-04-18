#ifndef STUDYCPP_PATTERN_PROXY_H
#define STUDYCPP_PATTERN_PROXY_H

// === Proxy (代理模式) ===
// 使用场景：远程代理（RPC stub）、虚拟代理（延迟加载大对象）、
// 保护代理（访问权限控制）、缓存代理。
#include <string>

class RealSubject {
   public:
    std::string request() const { return "RealSubject response"; }
};

class Proxy {
   public:
    std::string request() const {
        if (!real_) real_ = std::make_unique<RealSubject>();
        return "[Proxy log] " + real_->request();
    }
    bool is_loaded() const { return real_ != nullptr; }

   private:
    mutable std::unique_ptr<RealSubject> real_;
};

#endif  // STUDYCPP_PATTERN_PROXY_H
