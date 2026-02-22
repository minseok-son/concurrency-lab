#ifndef SLOPPY_COUNTER_H
#define SLOPPY_COUNTER_H

#include <mutex>

class SloppyCounter {
public:
    SloppyCounter(int t) : threshold(t) {};
    void increment();
    void update_global();
    void flush();
    int get_count();

private:
    std::mutex mtx_;
    int g_count = 0;
    int threshold;
    static thread_local int local_val;
};

#endif