#include "../include/counters/NaiveCounter.h"

void NaiveCounter::increment() {
    count++;
}

int NaiveCounter::get_count() const {
    return count;
}