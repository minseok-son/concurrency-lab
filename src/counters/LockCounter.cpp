#include "../include/counters/LockCounter.h"

void LockCounter::increment() {
    lock.lock();
    count++;
    lock.unlock();
}

int LockCounter::get_count() const {
    return count;
}