#include "../include/counters/SloppyCounter.h"

thread_local int SloppyCounter::local_val = 0;

void SloppyCounter::increment() {
    local_val++;
    if (local_val >= threshold) {
        update_global();
        local_val = 0;
    }
}

void SloppyCounter::update_global() {
    std::unique_lock<std::mutex> lock(mtx_);
    g_count += local_val;
}

void SloppyCounter::flush() {
    std::unique_lock<std::mutex> lock(mtx_);
    g_count += local_val;
}

int SloppyCounter::get_count() {
    std::unique_lock<std::mutex> lock(mtx_);
    return g_count;
}