#ifndef STUDYCPP_PATTERN_BRIDGE_H
#define STUDYCPP_PATTERN_BRIDGE_H

// === Bridge (桥接模式) ===
// 使用场景：跨平台 GUI（抽象控件 + 平台实现）、多种渲染引擎 + 多种图形类型、
// 将抽象与实现分离，使它们可以独立变化。
#include <memory>
#include <string>

// 实现接口
class Renderer {
   public:
    virtual ~Renderer() = default;
    virtual std::string render_circle(double r) const = 0;
};

class VectorRenderer : public Renderer {
   public:
    std::string render_circle(double r) const override {
        return "Vector circle(r=" + std::to_string(r) + ")";
    }
};

class RasterRenderer : public Renderer {
   public:
    std::string render_circle(double r) const override {
        return "Raster circle(r=" + std::to_string(r) + ")";
    }
};

// 抽象接口
class Shape {
   public:
    explicit Shape(std::unique_ptr<Renderer> r) : renderer_(std::move(r)) {}
    virtual ~Shape() = default;
    virtual std::string draw() const = 0;

   protected:
    Renderer* renderer() const { return renderer_.get(); }

   private:
    std::unique_ptr<Renderer> renderer_;
};

class CircleShape : public Shape {
   public:
    CircleShape(std::unique_ptr<Renderer> r, double radius)
        : Shape(std::move(r)), radius_(radius) {}
    std::string draw() const override { return renderer()->render_circle(radius_); }

   private:
    double radius_;
};

#endif  // STUDYCPP_PATTERN_BRIDGE_H
