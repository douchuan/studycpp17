#ifndef STUDYCPP_PATTERN_FACADE_H
#define STUDYCPP_PATTERN_FACADE_H

// === Facade (外观模式) ===
// 使用场景：一键启动系统（封装 CPU/内存/硬盘启动序列）、简化的 API 网关、
// 为复杂子系统提供统一的高层接口。
#include <string>

class Cpu {
   public:
    std::string boot() const { return "CPU booted"; }
};

class Memory {
   public:
    std::string load() const { return "Memory loaded"; }
};

class Disk {
   public:
    std::string read_os() const { return "OS read from disk"; }
};

// 外观类
class ComputerFacade {
   public:
    std::string start() const {
        return cpu_.boot() + ", " + memory_.load() + ", " + disk_.read_os();
    }

   private:
    Cpu cpu_;
    Memory memory_;
    Disk disk_;
};

#endif  // STUDYCPP_PATTERN_FACADE_H
