#ifndef QUEUE_H
#define QUEUE_H
#include <mutex>
#include <atomic>

class Queue {
public:
    Queue();
    ~Queue();

    // Industry standard: prevent copying for synchronization objects
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void enqueue(int val);
    int dequeue();
    int get_size() const;

private:
    struct Node {
        int val = 0;
        Node* next = nullptr;
        Node(int v) : val(v) {}
    };
    alignas(64) Node* head_;
    std::mutex head_lock_;

    alignas(64) Node* tail_;
    std::mutex tail_lock_;
    
    alignas(64) std::atomic<int> size_{0};
};

#endif