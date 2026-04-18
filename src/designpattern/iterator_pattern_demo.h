#ifndef STUDYCPP_PATTERN_ITERATOR_PATTERN_H
#define STUDYCPP_PATTERN_ITERATOR_PATTERN_H

// === Iterator (迭代器模式) ===
// 使用场景：自定义集合遍历（树/图的迭代器）、惰性序列生成、
// 在不暴露内部表示的情况下顺序访问聚合对象元素。
#include <string>
#include <vector>

template <typename T>
class Iterator {
   public:
    virtual ~Iterator() = default;
    virtual bool has_next() const = 0;
    virtual T next() = 0;
};

template <typename T>
class VectorIterator : public Iterator<T> {
   public:
    explicit VectorIterator(const std::vector<T>& v) : vec_(v) {}
    bool has_next() const override { return index_ < vec_.size(); }
    T next() override { return vec_[index_++]; }

   private:
    const std::vector<T>& vec_;
    size_t index_ = 0;
};

#endif  // STUDYCPP_PATTERN_ITERATOR_PATTERN_H
