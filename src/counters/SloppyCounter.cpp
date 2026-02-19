#include "../include/counters/SloppyCounter.h"

void SloppyCounter::increment(int amount) {
    std::unique_lock<std::mutex> lock(mtx_);
    g_count += amount;
}

int SloppyCounter::get_count() {
    std::unique_lock<std::mutex> lock(mtx_);
    return g_count;
}