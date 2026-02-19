#ifndef LOCK_COUNTER_H
#define LOCK_COUNTER_H

#include <mutex>

class LockCounter {
public:
    LockCounter() = default;
    void increment();
    int get_count() const;

private:
    std::mutex lock;
    int count = 0;
};

#endif