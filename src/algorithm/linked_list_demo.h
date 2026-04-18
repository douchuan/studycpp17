#ifndef STUDYCPP_ALGORITHM_LINKED_LIST_DEMO_H
#define STUDYCPP_ALGORITHM_LINKED_LIST_DEMO_H

#include <memory>
#include <utility>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v = 0, ListNode* n = nullptr) : val(v), next(n) {}
};

// --- 反转链表 ---
inline ListNode* reverse_list(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// --- 检测环（Floyd 快慢指针） ---
inline bool has_cycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// --- 合并两个有序链表 ---
inline ListNode* merge_two_lists(ListNode* l1, ListNode* l2) {
    ListNode dummy;
    ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// --- 找中点（快慢指针） ---
inline ListNode* find_middle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// --- 删除第 N 个节点 ---
inline ListNode* remove_nth_from_end(ListNode* head, int n) {
    ListNode dummy(0, head);
    ListNode* fast = &dummy;
    ListNode* slow = &dummy;
    for (int i = 0; i < n; ++i) fast = fast->next;
    while (fast->next) {
        slow = slow->next;
        fast = fast->next;
    }
    ListNode* to_delete = slow->next;
    if (to_delete) {
        slow->next = to_delete->next;
        delete to_delete;
    }
    return dummy.next;
}

// 辅助：从 vector 构建链表
inline ListNode* build_list(const std::vector<int>& vals) {
    if (vals.empty()) return nullptr;
    auto* head = new ListNode(vals[0]);
    ListNode* cur = head;
    for (size_t i = 1; i < vals.size(); ++i) {
        cur->next = new ListNode(vals[i]);
        cur = cur->next;
    }
    return head;
}

// 辅助：链表转 vector
inline std::vector<int> to_vec(ListNode* head) {
    std::vector<int> result;
    for (auto* cur = head; cur; cur = cur->next) result.push_back(cur->val);
    return result;
}

// 辅助：删除链表
inline void free_list(ListNode* head) {
    while (head) {
        auto* next = head->next;
        delete head;
        head = next;
    }
}

#endif  // STUDYCPP_ALGORITHM_LINKED_LIST_DEMO_H
