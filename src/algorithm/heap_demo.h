#ifndef STUDYCPP_ALGORITHM_HEAP_DEMO_H
#define STUDYCPP_ALGORITHM_HEAP_DEMO_H

#include <functional>
#include <queue>
#include <vector>

// --- 手写大顶堆（上浮/下沉） ---
class MinHeap {
   public:
    void push(int val) {
        data.push_back(val);
        sift_up(static_cast<int>(data.size()) - 1);
    }
    int top() const { return data.front(); }
    void pop() {
        data.front() = data.back();
        data.pop_back();
        if (!data.empty()) sift_down(0);
    }
    bool empty() const { return data.empty(); }
    int size() const { return static_cast<int>(data.size()); }

   private:
    std::vector<int> data;
    void sift_up(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (data[i] < data[p]) {
                std::swap(data[i], data[p]);
                i = p;
            } else
                break;
        }
    }
    void sift_down(int i) {
        int n = static_cast<int>(data.size());
        while (true) {
            int smallest = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && data[l] < data[smallest]) smallest = l;
            if (r < n && data[r] < data[smallest]) smallest = r;
            if (smallest != i) {
                std::swap(data[i], data[smallest]);
                i = smallest;
            } else
                break;
        }
    }
};

// --- 用 priority_queue 求 Top K ---
inline std::vector<int> top_k_heap(const std::vector<int>& nums, int k) {
    std::priority_queue<int> pq;  // 大顶堆
    for (int x : nums) pq.push(x);
    std::vector<int> result;
    for (int i = 0; i < k && !pq.empty(); ++i) {
        result.push_back(pq.top());
        pq.pop();
    }
    return result;
}

#endif  // STUDYCPP_ALGORITHM_HEAP_DEMO_H
