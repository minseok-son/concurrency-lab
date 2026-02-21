#ifndef LOCK_LINKED_LIST
#define LOCK_LINKED_LIST
#include <mutex>

class LockLinkedList {
public:
    LockLinkedList() = default;
    ~LockLinkedList();

    void pushFront(int val);
    void popFront();
    int size();

private:
    struct Node {
        Node(int val) : value(val) {}
        Node* next = nullptr;
        int value;
    };
    Node* head_ = nullptr;
    int size_ = 0;
    std::mutex mtx_;
};

#endif