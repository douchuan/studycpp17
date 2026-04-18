#ifndef STUDYCPP_PATTERN_DECORATOR_H
#define STUDYCPP_PATTERN_DECORATOR_H

// === Decorator (装饰器模式) ===
// 使用场景：HTTP 请求中间件（日志/认证/重试）、咖啡店配料叠加、文本流包装（压缩/加密），
// 动态地为对象添加职责而不修改原有类。
#include <memory>
#include <string>

class TextStream {
   public:
    virtual ~TextStream() = default;
    virtual std::string read() const = 0;
};

class PlainText : public TextStream {
   public:
    explicit PlainText(std::string d) : data_(std::move(d)) {}
    std::string read() const override { return data_; }

   private:
    std::string data_;
};

class StreamDecorator : public TextStream {
   public:
    explicit StreamDecorator(std::unique_ptr<TextStream> inner) : inner_(std::move(inner)) {}

   protected:
    TextStream* inner() const { return inner_.get(); }

   private:
    std::unique_ptr<TextStream> inner_;
};

class UpperDecorator : public StreamDecorator {
   public:
    explicit UpperDecorator(std::unique_ptr<TextStream> s) : StreamDecorator(std::move(s)) {}
    std::string read() const override {
        std::string s = inner()->read();
        for (auto& c : s) c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
        return s;
    }
};

#endif  // STUDYCPP_PATTERN_DECORATOR_H
