#ifndef STUDYCPP_PATTERN_FACTORY_METHOD_H
#define STUDYCPP_PATTERN_FACTORY_METHOD_H

// === Factory Method (工厂方法模式) ===
// 使用场景：创建不同文档类型（Word/PDF/Excel）、不同通知渠道（邮件/短信/推送）等，
// 将对象的创建延迟到子类。
#include <memory>
#include <string>

class Product {
   public:
    virtual ~Product() = default;
    virtual std::string name() const = 0;
};

class ConcreteProductA : public Product {
   public:
    std::string name() const override { return "ProductA"; }
};

class ConcreteProductB : public Product {
   public:
    std::string name() const override { return "ProductB"; }
};

class Factory {
   public:
    virtual ~Factory() = default;
    virtual std::unique_ptr<Product> create() const = 0;
};

class FactoryA : public Factory {
   public:
    std::unique_ptr<Product> create() const override {
        return std::make_unique<ConcreteProductA>();
    }
};

class FactoryB : public Factory {
   public:
    std::unique_ptr<Product> create() const override {
        return std::make_unique<ConcreteProductB>();
    }
};

#endif  // STUDYCPP_PATTERN_FACTORY_METHOD_H
