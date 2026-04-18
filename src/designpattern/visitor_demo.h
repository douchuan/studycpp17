#ifndef STUDYCPP_PATTERN_VISITOR_H
#define STUDYCPP_PATTERN_VISITOR_H

// === Visitor (访问者模式) ===
// 使用场景：AST 遍历（类型检查/代码生成/格式化）、报表生成、
// 在不修改元素类的前提下为其添加新操作。
#include <memory>
#include <string>
#include <vector>

// 前向声明
class Element;
class Visitor;

class Visitor {
   public:
    virtual ~Visitor() = default;
    virtual void visit_concrete_element_a(class ConcreteElementA& e) = 0;
    virtual void visit_concrete_element_b(class ConcreteElementB& e) = 0;
};

class Element {
   public:
    virtual ~Element() = default;
    virtual void accept(Visitor& v) = 0;
};

class ConcreteElementA : public Element {
   public:
    explicit ConcreteElementA(std::string d) : data_(std::move(d)) {}
    void accept(Visitor& v) override { v.visit_concrete_element_a(*this); }
    const std::string& data() const { return data_; }

   private:
    std::string data_;
};

class ConcreteElementB : public Element {
   public:
    explicit ConcreteElementB(int v) : value_(v) {}
    void accept(Visitor& v) override { v.visit_concrete_element_b(*this); }
    int value() const { return value_; }

   private:
    int value_;
};

// 具体访问者：收集所有元素描述
class PrintVisitor : public Visitor {
   public:
    void visit_concrete_element_a(ConcreteElementA& e) override {
        result_ += "A(" + e.data() + ") ";
    }
    void visit_concrete_element_b(ConcreteElementB& e) override {
        result_ += "B(" + std::to_string(e.value()) + ") ";
    }
    std::string result() const { return result_; }

   private:
    std::string result_;
};

#endif  // STUDYCPP_PATTERN_VISITOR_H
