#include "../include/queue/Queue.h"
#include <mutex>

Queue::Queue() {
    Node* tmp = new Node(0);
    tmp->next = nullptr;
    head_ = tail_ = tmp;
};

Queue::~Queue() {
    Node* cur = head_;
    while (cur != nullptr) {
        Node* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
};

void Queue::enqueue(int val) {
    Node* tmp = new Node(val);
    std::unique_lock<std::mutex> lock(tail_lock_);
    tail_->next = tmp;
    tail_ = tmp;
    size_.fetch_add(1, std::memory_order_relaxed);
};

int Queue::dequeue() {
    std::unique_lock<std::mutex> lock(head_lock_);
    Node* old_head = head_;
    Node* new_head = head_->next;

    if (new_head == nullptr) {
        return -1;
    }

    int res = new_head->val;
    head_ = new_head;
    delete old_head;
    size_.fetch_sub(1, std::memory_order_relaxed);
    return res;
};

int Queue::get_size() const {
    return size_.load(std::memory_order_relaxed);
}