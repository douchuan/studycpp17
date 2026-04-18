#ifndef STUDYCPP_PATTERN_ABSTRACT_FACTORY_H
#define STUDYCPP_PATTERN_ABSTRACT_FACTORY_H

// === Abstract Factory (抽象工厂模式) ===
// 使用场景：UI 主题系统（macOS/Windows/Linux 风格的按钮+复选框）、跨平台 GUI 组件库、
// 不同数据库族的 DAO 创建。
#include <memory>
#include <string>

class Button {
   public:
    virtual ~Button() = default;
    virtual std::string render() const = 0;
};

class Checkbox {
   public:
    virtual ~Checkbox() = default;
    virtual std::string render() const = 0;
};

class LightButton : public Button {
   public:
    std::string render() const override { return "[LightButton]"; }
};

class LightCheckbox : public Checkbox {
   public:
    std::string render() const override { return "[LightCheckbox]"; }
};

class DarkButton : public Button {
   public:
    std::string render() const override { return "[DarkButton]"; }
};

class DarkCheckbox : public Checkbox {
   public:
    std::string render() const override { return "[DarkCheckbox]"; }
};

class GuiFactory {
   public:
    virtual ~GuiFactory() = default;
    virtual std::unique_ptr<Button> create_button() const = 0;
    virtual std::unique_ptr<Checkbox> create_checkbox() const = 0;
};

class LightFactory : public GuiFactory {
   public:
    std::unique_ptr<Button> create_button() const override {
        return std::make_unique<LightButton>();
    }
    std::unique_ptr<Checkbox> create_checkbox() const override {
        return std::make_unique<LightCheckbox>();
    }
};

class DarkFactory : public GuiFactory {
   public:
    std::unique_ptr<Button> create_button() const override {
        return std::make_unique<DarkButton>();
    }
    std::unique_ptr<Checkbox> create_checkbox() const override {
        return std::make_unique<DarkCheckbox>();
    }
};

#endif  // STUDYCPP_PATTERN_ABSTRACT_FACTORY_H
