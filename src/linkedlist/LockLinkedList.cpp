#include "../include/linkedlist/LockLinkedList.h"
#include <mutex>

LockLinkedList::~LockLinkedList() {
    while (head_ != nullptr) {
        Node* nxt = head_->next;
        delete head_;
        head_ = nxt;
    }
};

void LockLinkedList::pushFront(int val) {
    std::unique_lock<std::mutex> lock(mtx_);
    Node* node = new Node(val);
    node->next = head_->next;
    head_->next = node;
    size_++;
};

void LockLinkedList::popFront() {
    std::unique_lock<std::mutex> lock(mtx_);
    if (head_ == nullptr) return;
    Node* toDelete = head_->next;
    head_->next = toDelete->next;
    delete(toDelete);
    size_--;
};

int LockLinkedList::size() {
    std::unique_lock<std::mutex> lock(mtx_);
    return size_;
}