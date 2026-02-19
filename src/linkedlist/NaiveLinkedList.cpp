#include "../include/linkedlist/NaiveLinkedList.h"
#include <iostream>

LinkedList::~LinkedList() {
    while (head != nullptr) {
        popFront();
    }
}

void LinkedList::pushFront(int val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    head = newNode;
    count++;
}

void LinkedList::popFront() {
    if (head == nullptr) return;
    
    Node* tmp = head;
    head = head->next;
    delete tmp;
    count--;
}

bool LinkedList::remove(int val) {
    if (head == nullptr) return false;

    if (head->value == val) {
        popFront();
        return true;
    }

    Node* cur = head;
    while (cur->next != nullptr && cur->next->value != val) {
        cur = cur->next;
    }

    if (cur->next == nullptr) {
        return false;
    }

    Node* target = cur->next;
    cur->next = target->next;
    delete target;
    count --;
    return true;
}

bool LinkedList::contains(int val) const {
    Node* cur = head;

    while (cur != nullptr) {
        if (cur->value == val) {
            return true;
        }
        cur = cur->next;
    }
    
    return false;
}

bool LinkedList::isEmpty() const {
    return count == 0;
}

void LinkedList::print() const {
    Node* cur = head;

    while (cur != nullptr) {
        std::cout << cur->value << std::endl;
        cur = cur->next;
    }
}

int LinkedList::size() const {
    return count;
}