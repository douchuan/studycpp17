#ifndef STUDYCPP_PATTERN_MEDIATOR_H
#define STUDYCPP_PATTERN_MEDIATOR_H

// === Mediator (中介者模式) ===
// 使用场景：聊天室（用户通过中心节点通信）、航空塔台控制、
// GUI 对话框组件间通信、微服务间协调。
#include <string>
#include <vector>

class ChatRoom;

class User {
   public:
    User(std::string n, ChatRoom* room) : name_(std::move(n)), room_(room) {}
    const std::string& name() const { return name_; }
    void send(const std::string& message) const;
    void receive(const std::string& from, const std::string& message) {
        messages_.push_back(from + ": " + message);
    }
    const std::vector<std::string>& messages() const { return messages_; }

   private:
    std::string name_;
    ChatRoom* room_;
    std::vector<std::string> messages_;
};

class ChatRoom {
   public:
    void add_user(User* u) { users_.push_back(u); }
    void send_message(const User* sender, const std::string& message) {
        for (auto* u : users_)
            if (u != sender) u->receive(sender->name(), message);
    }

   private:
    std::vector<User*> users_;
};

inline void User::send(const std::string& message) const { room_->send_message(this, message); }

#endif  // STUDYCPP_PATTERN_MEDIATOR_H
