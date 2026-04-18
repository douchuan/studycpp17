#ifndef STUDYCPP_PATTERN_STATE_H
#define STUDYCPP_PATTERN_STATE_H

// === State (状态模式) ===
// 使用场景：订单状态流转（创建→支付→发货→完成）、TCP 连接状态机、
// 游戏角色状态（正常/受伤/死亡），将状态相关行为封装到独立类中。
#include <memory>
#include <string>

class VendingMachine;

class State {
   public:
    virtual ~State() = default;
    virtual std::string insert_coin(VendingMachine& ctx) = 0;
    virtual std::string dispense(VendingMachine& ctx) = 0;
    virtual std::string name() const = 0;
};

class VendingMachine {
   public:
    explicit VendingMachine(std::unique_ptr<State> initial) : state_(std::move(initial)) {}
    void set_state(std::unique_ptr<State> s) { state_ = std::move(s); }
    std::string insert_coin() { return state_->insert_coin(*this); }
    std::string dispense() { return state_->dispense(*this); }
    std::string current_state() const { return state_->name(); }

   private:
    std::unique_ptr<State> state_;
};

class IdleState : public State {
   public:
    std::string insert_coin(VendingMachine& ctx) override;
    std::string dispense(VendingMachine&) override { return "insert coin first"; }
    std::string name() const override { return "Idle"; }
};

class HasCoinState : public State {
   public:
    std::string insert_coin(VendingMachine&) override { return "already has coin"; }
    std::string dispense(VendingMachine& ctx) override;
    std::string name() const override { return "HasCoin"; }
};

inline std::string IdleState::insert_coin(VendingMachine& ctx) {
    ctx.set_state(std::make_unique<HasCoinState>());
    return "coin inserted";
}

inline std::string HasCoinState::dispense(VendingMachine& ctx) {
    ctx.set_state(std::make_unique<IdleState>());
    return "dispensed!";
}

#endif  // STUDYCPP_PATTERN_STATE_H
