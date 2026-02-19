#ifndef NAIVE_COUNTER_H
#define NAIVE_COUNTER_H

class NaiveCounter {    
public:
    NaiveCounter() = default;
    void increment();
    int get_count() const;

private:
    int count = 0;
};

#endif