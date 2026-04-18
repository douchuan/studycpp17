#ifndef STUDYCPP_PATTERN_OBSERVER_H
#define STUDYCPP_PATTERN_OBSERVER_H

// === Observer (观察者模式) ===
// 使用场景：事件订阅系统、MVC 视图更新、股票行情推送、
// 一个对象状态变化时通知多个依赖对象。
#include <memory>
#include <string>
#include <vector>

class Observer {
   public:
    virtual ~Observer() = default;
    virtual void update(const std::string& event) = 0;
};

class Subject {
   public:
    void attach(Observer* o) { observers_.push_back(o); }
    void detach(Observer* o) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), o), observers_.end());
    }
    void notify(const std::string& event) {
        for (auto* o : observers_) o->update(event);
    }

   private:
    std::vector<Observer*> observers_;
};

class LogObserver : public Observer {
   public:
    void update(const std::string& event) override { events_.push_back(event); }
    const std::vector<std::string>& events() const { return events_; }

   private:
    std::vector<std::string> events_;
};

#endif  // STUDYCPP_PATTERN_OBSERVER_H
