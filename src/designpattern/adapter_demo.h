#ifndef STUDYCPP_PATTERN_ADAPTER_H
#define STUDYCPP_PATTERN_ADAPTER_H

// === Adapter (适配器模式) ===
// 使用场景：将旧版日志接口适配到新系统、第三方库接口包装、
// 将不兼容接口转换为目标接口（如方形插头转圆孔插座）。
#include <string>

// 已有系统接口
class AudioPlayer {
   public:
    virtual ~AudioPlayer() = default;
    virtual void play_mp3(const std::string& file) = 0;
};

class Mp3Player : public AudioPlayer {
   public:
    void play_mp3(const std::string& file) override { played_ = file; }
    std::string played_file() const { return played_; }

   private:
    std::string played_;
};

// 新系统期望的接口
class MediaPlayable {
   public:
    virtual ~MediaPlayable() = default;
    virtual void play(const std::string& type, const std::string& file) = 0;
};

// 适配器
class MediaAdapter : public MediaPlayable {
   public:
    explicit MediaAdapter(AudioPlayer* p) : player_(p) {}
    void play(const std::string& type, const std::string& file) override {
        if (type == "mp3") player_->play_mp3(file);
    }

   private:
    AudioPlayer* player_;
};

#endif  // STUDYCPP_PATTERN_ADAPTER_H
