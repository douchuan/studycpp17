#ifndef STUDYCPP_PATTERN_PROTOTYPE_H
#define STUDYCPP_PATTERN_PROTOTYPE_H

// === Prototype (原型模式) ===
// 使用场景：对象克隆（游戏场景中大量相似 NPC 的创建）、复杂配置对象的副本、
// 当直接构造成本过高时通过复制已有实例来创建新对象。
#include <memory>
#include <string>

class Shape {
   public:
    virtual ~Shape() = default;
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual std::string desc() const = 0;
};

class Circle : public Shape {
   public:
    explicit Circle(double r, std::string c) : radius(r), color(std::move(c)) {}
    std::unique_ptr<Shape> clone() const override { return std::make_unique<Circle>(*this); }
    std::string desc() const override {
        return "Circle(r=" + std::to_string(radius) + ", " + color + ")";
    }

   private:
    double radius;
    std::string color;
};

#endif  // STUDYCPP_PATTERN_PROTOTYPE_H
