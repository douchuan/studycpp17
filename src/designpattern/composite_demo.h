#ifndef STUDYCPP_PATTERN_COMPOSITE_H
#define STUDYCPP_PATTERN_COMPOSITE_H

// === Composite (组合模式) ===
// 使用场景：文件系统（目录/文件统一接口）、GUI 组件树、组织架构树、
// 将对象组合成树形结构以表示"部分-整体"层次。
#include <memory>
#include <string>
#include <vector>

class FileSystemNode {
   public:
    virtual ~FileSystemNode() = default;
    virtual std::string display(int indent = 0) const = 0;
};

class FileNode : public FileSystemNode {
   public:
    explicit FileNode(std::string n) : name_(std::move(n)) {}
    std::string display(int indent = 0) const override {
        return std::string(indent, ' ') + "- " + name_;
    }

   private:
    std::string name_;
};

class DirectoryNode : public FileSystemNode {
   public:
    explicit DirectoryNode(std::string n) : name_(std::move(n)) {}
    void add(std::unique_ptr<FileSystemNode> child) { children_.push_back(std::move(child)); }
    std::string display(int indent = 0) const override {
        std::string s = std::string(indent, ' ') + "+ " + name_ + "/";
        for (const auto& c : children_) s += "\n" + c->display(indent + 2);
        return s;
    }

   private:
    std::string name_;
    std::vector<std::unique_ptr<FileSystemNode>> children_;
};

#endif  // STUDYCPP_PATTERN_COMPOSITE_H
