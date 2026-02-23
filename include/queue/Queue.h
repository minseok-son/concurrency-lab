#ifndef QUEUE_H
#define QUEUE_H
#include <mutex>

class Queue {
public:
    Queue();
    ~Queue();

    // Industry standard: prevent copying for synchronization objects
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void enqueue(int val);
    int dequeue();

private:
    struct Node {
        int val = 0;
        Node* next = nullptr;
        Node(int v) : val(v) {}
    };
    Node* head_;
    std::mutex head_lock_;

    Node* tail_;
    std::mutex tail_lock_;
};

#endif