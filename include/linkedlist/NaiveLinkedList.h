#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class LinkedList {
public:
    LinkedList() : head(nullptr) {}
    ~LinkedList();

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    void pushFront(int val);
    void popFront();
    bool remove(int val);
    bool contains(int val) const;
    bool isEmpty() const;
    void print() const;
    int size() const;
private:
    struct Node {
        int value;
        Node* next;

        Node(int val) : value(val), next(nullptr) {}
    };

    Node* head;
    int count = 0;
};

#endif