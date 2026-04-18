#ifndef STUDYCPP_PATTERN_STRATEGY_H
#define STUDYCPP_PATTERN_STRATEGY_H

// === Strategy (策略模式) ===
// 使用场景：排序算法选择（快速/归并/堆排序）、支付方式（支付宝/微信/银行卡）、
// 压缩算法切换（gzip/zip/brotli），定义算法族并使其可互换。
#include <numeric>
#include <string>
#include <vector>

class SortStrategy {
   public:
    virtual ~SortStrategy() = default;
    virtual std::string name() const = 0;
    virtual void sort(std::vector<int>& data) const = 0;
};

class BubbleSort : public SortStrategy {
   public:
    std::string name() const override { return "BubbleSort"; }
    void sort(std::vector<int>& data) const override {
        for (size_t i = 0; i < data.size(); ++i)
            for (size_t j = 0; j < data.size() - 1 - i; ++j)
                if (data[j] > data[j + 1]) std::swap(data[j], data[j + 1]);
    }
};

class QuickSortStrategy : public SortStrategy {
   public:
    std::string name() const override { return "QuickSort"; }
    void sort(std::vector<int>& data) const override {
        auto qs = [&](auto& self, int l, int r) {
            if (l >= r) return;
            int p = data[r], i = l;
            for (int j = l; j < r; ++j)
                if (data[j] < p) std::swap(data[i++], data[j]);
            std::swap(data[i], data[r]);
            self(self, l, i - 1);
            self(self, i + 1, r);
        };
        qs(qs, 0, static_cast<int>(data.size()) - 1);
    }
};

class SortContext {
   public:
    explicit SortContext(std::unique_ptr<SortStrategy> s) : strategy_(std::move(s)) {}
    void set_strategy(std::unique_ptr<SortStrategy> s) { strategy_ = std::move(s); }
    void sort(std::vector<int>& data) const { strategy_->sort(data); }
    std::string strategy_name() const { return strategy_->name(); }

   private:
    std::unique_ptr<SortStrategy> strategy_;
};

#endif  // STUDYCPP_PATTERN_STRATEGY_H
