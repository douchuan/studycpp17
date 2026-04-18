#ifndef STUDYCPP_PATTERN_BUILDER_H
#define STUDYCPP_PATTERN_BUILDER_H

// === Builder (建造者模式) ===
// 使用场景：复杂对象构建（SQL 语句构造器、HTTP 请求构造器、HTML 文档生成器），
// 将构建步骤与对象表示分离。
#include <string>

class HttpRequest {
   public:
    HttpRequest() = default;
    void set_method(const std::string& m) { method_ = m; }
    void set_url(const std::string& u) { url_ = u; }
    void set_body(const std::string& b) { body_ = b; }
    std::string build() const { return method_ + " " + url_ + "\n" + body_; }

   private:
    std::string method_, url_, body_;
};

class HttpRequestBuilder {
   public:
    HttpRequestBuilder& method(const std::string& m) {
        req_.set_method(m);
        return *this;
    }
    HttpRequestBuilder& url(const std::string& u) {
        req_.set_url(u);
        return *this;
    }
    HttpRequestBuilder& body(const std::string& b) {
        req_.set_body(b);
        return *this;
    }
    HttpRequest build() const { return req_; }

   private:
    HttpRequest req_;
};

#endif  // STUDYCPP_PATTERN_BUILDER_H
