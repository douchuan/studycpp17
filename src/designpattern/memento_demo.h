#ifndef STUDYCPP_PATTERN_MEMENTO_H
#define STUDYCPP_PATTERN_MEMENTO_H

// === Memento (备忘录模式) ===
// 使用场景：编辑器撤销/恢复（游戏存档）、事务回滚、
// 在不破坏封装性的前提下捕获和恢复对象内部状态。
#include <memory>
#include <string>
#include <vector>

class Memento {
   public:
    explicit Memento(std::string s) : state_(std::move(s)) {}
    const std::string& state() const { return state_; }

   private:
    std::string state_;
};

class TextEditor {
   public:
    explicit TextEditor(std::string content = "") : content_(std::move(content)) {}
    void set_content(const std::string& c) { content_ = c; }
    const std::string& content() const { return content_; }
    std::unique_ptr<Memento> save() const { return std::make_unique<Memento>(content_); }
    void restore(const Memento& m) { content_ = m.state(); }

   private:
    std::string content_;
};

class History {
   public:
    void push(std::unique_ptr<Memento> m) { stack_.push_back(std::move(m)); }
    std::unique_ptr<Memento> pop() {
        if (stack_.empty()) return nullptr;
        auto m = std::move(stack_.back());
        stack_.pop_back();
        return m;
    }

   private:
    std::vector<std::unique_ptr<Memento>> stack_;
};

#endif  // STUDYCPP_PATTERN_MEMENTO_H
