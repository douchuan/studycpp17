#ifndef STUDYCPP_PATTERN_FLYWEIGHT_H
#define STUDYCPP_PATTERN_FLYWEIGHT_H

// === Flyweight (享元模式) ===
// 使用场景：文字编辑器中的字符对象（共享字体/大小）、游戏中的树木/草丛实例、
// 大量细粒度对象通过共享内部状态来减少内存使用。
#include <memory>
#include <string>
#include <unordered_map>

struct CharacterState {
    char ch;
    std::string font;
    int size;
};

class FontFactory {
   public:
    std::shared_ptr<const std::string> get_font(const std::string& name) {
        auto it = fonts_.find(name);
        if (it == fonts_.end()) {
            fonts_[name] = std::make_shared<const std::string>(name);
        }
        return fonts_[name];
    }

   private:
    std::unordered_map<std::string, std::shared_ptr<const std::string>> fonts_;
};

#endif  // STUDYCPP_PATTERN_FLYWEIGHT_H
