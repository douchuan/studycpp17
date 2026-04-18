#ifndef STUDYCPP_PATTERN_INTERPRETER_H
#define STUDYCPP_PATTERN_INTERPRETER_H

// === Interpreter (解释器模式) ===
// 使用场景：正则表达式引擎、SQL 解析器、数学表达式求值、
// 定义语言的文法表示并解释执行。
#include <sstream>
#include <string>
#include <vector>

// 表达式接口
class Expression {
   public:
    virtual ~Expression() = default;
    virtual bool interpret(const std::string& context) const = 0;
};

// 终结符表达式
class TerminalExpression : public Expression {
   public:
    explicit TerminalExpression(std::string data) : data_(std::move(data)) {}
    bool interpret(const std::string& context) const override {
        return context.find(data_) != std::string::npos;
    }

   private:
    std::string data_;
};

// 非终结符表达式 (Or)
class OrExpression : public Expression {
   public:
    OrExpression(std::unique_ptr<Expression> e1, std::unique_ptr<Expression> e2)
        : e1_(std::move(e1)), e2_(std::move(e2)) {}
    bool interpret(const std::string& context) const override {
        return e1_->interpret(context) || e2_->interpret(context);
    }

   private:
    std::unique_ptr<Expression> e1_, e2_;
};

// 非终结符表达式 (And)
class AndExpression : public Expression {
   public:
    AndExpression(std::unique_ptr<Expression> e1, std::unique_ptr<Expression> e2)
        : e1_(std::move(e1)), e2_(std::move(e2)) {}
    bool interpret(const std::string& context) const override {
        return e1_->interpret(context) && e2_->interpret(context);
    }

   private:
    std::unique_ptr<Expression> e1_, e2_;
};

#endif  // STUDYCPP_PATTERN_INTERPRETER_H
