#ifndef STUDYCPP_PATTERN_COMMAND_H
#define STUDYCPP_PATTERN_COMMAND_H

// === Command (命令模式) ===
// 使用场景：撤销/重做系统（编辑器）、任务队列、宏录制回放、
// 将请求封装为对象以实现参数化、排队和日志记录。
#include <memory>
#include <string>
#include <vector>

class Command {
   public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Light {
   public:
    void on() { is_on_ = true; }
    void off() { is_on_ = false; }
    bool is_on() const { return is_on_; }

   private:
    bool is_on_ = false;
};

class LightOnCommand : public Command {
   public:
    explicit LightOnCommand(Light* l) : light_(l) {}
    void execute() override { light_->on(); }
    void undo() override { light_->off(); }

   private:
    Light* light_;
};

class CommandInvoker {
   public:
    void execute(std::unique_ptr<Command> cmd) {
        cmd->execute();
        history_.push_back(std::move(cmd));
    }
    void undo_last() {
        if (!history_.empty()) {
            history_.back()->undo();
            history_.pop_back();
        }
    }

   private:
    std::vector<std::unique_ptr<Command>> history_;
};

#endif  // STUDYCPP_PATTERN_COMMAND_H
