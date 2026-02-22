#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <concepts>
#include "../include/counters/NaiveCounter.h"
#include "../include/counters/LockCounter.h"
#include "../include/counters/SloppyCounter.h"

template <typename T>
void try_flush(T& counter) {
    if constexpr (requires(T t) { t.flush(); }) {
        counter.flush();
    }
}

template <typename CounterType, typename... Args>
void run_benchmark(int num_threads, int increments, Args&&... args) {
    CounterType counter(std::forward<Args>(args)...);

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&counter, increments]() {
            for (int j = 0; j < increments; ++j) {
                counter.increment();
            }
            
            try_flush(counter); 
        });
    }

    for (auto& t : threads) t.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Duration: " << elapsed.count() << "s" << std::endl;
    std::cout << "Expected Value: " << (num_threads * increments) << std::endl;
    std::cout << "Actual Value: " << counter.get_count() << std::endl;
}



int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <counter_type> <num_threads>" << std::endl;
        std::cerr << "Types: naive, lock, sloppy" << std::endl;
        return 1;
    }

    std::string type = argv[1];
    int num_threads = std::stoi(argv[2]);
    const int TOTAL = 160'000'000;
    int increments = TOTAL / num_threads;
    const int threshold = 1024;

    std::cout << "Benchmarking " << type << " with " << num_threads << " threads..." << std::endl;

    if (type == "naive") {
        run_benchmark<NaiveCounter>(num_threads, increments);
    } else if (type == "lock") {
        run_benchmark<LockCounter>(num_threads, increments);
    } else if (type == "sloppy") {
        run_benchmark<SloppyCounter>(num_threads, increments, threshold);
    } else {
        std::cerr << "Unknown counter type!" << std::endl;
        return 1;
    }

    return 0;
}