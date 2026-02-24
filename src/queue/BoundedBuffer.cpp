#include "../include/queue/BoundedBuffer.h"

void BoundedBuffer::produce(int val) {
    std::unique_lock<std::mutex> lock(mtx_);
    
    not_full_.wait(lock, [this]{ return size_ < CAPACITY ; });
    
    buffer_[zone_.tail_] = val;
    zone_.tail_ = (zone_.tail_ + 1) % CAPACITY;
    ++size_;
    not_empty_.notify_one();
};

int BoundedBuffer::consume() {
    std::unique_lock<std::mutex> lock(mtx_);
    
    not_empty_.wait(lock, [this]{ return size_ > 0; });
    
    int ret = buffer_[zone_.head_];
    zone_.head_ = (zone_.head_ + 1) % CAPACITY;
    --size_;
    not_full_.notify_one();
    return ret;
}

int BoundedBuffer::get_size() const {
    std::unique_lock<std::mutex> lock(mtx_);
    return size_;
}

void BoundedBuffer::print_address() const {
    std::cout << "Head address: " << &zone_.head_ << "\n";
    std::cout << "Tail address: " << &zone_.tail_ << "\n";
    std::cout << "Distance: " << (char*)&zone_.tail_ - (char*)&zone_.head_ << " bytes\n";
}