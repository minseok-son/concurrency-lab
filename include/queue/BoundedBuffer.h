#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <mutex>
#include <condition_variable>
#include <iostream>


class BoundedBuffer {
public:
    BoundedBuffer() = default;

    // Prevent accidental thread-safety disasters
    BoundedBuffer(const BoundedBuffer&) = delete;
    BoundedBuffer& operator=(const BoundedBuffer&) = delete;

    void produce(int val);
    int consume();
    int get_size() const;
    void print_address() const;
   

private:
    int buffer_[1024];
    // alignas(64) int head_ = 0;
    // alignas(64) int tail_ = 0;

     struct SlowGroup {
        int head_ = 0;
        int tail_ = 0;
    } zone_;

    
    static constexpr int CAPACITY = 1024;
    int size_ = 0;
    mutable std::mutex mtx_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
};

#endif