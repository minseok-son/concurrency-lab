#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include "../include/counters/NaiveCounter.h"
#include "../include/counters/LockCounter.h"
#include "../include/counters/SloppyCounter.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_threads>" << std::endl;
        return 1;
    }

    int num_threads;
    try {
        num_threads = std::stoi(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << "Invalid number of threads: " << argv[1] << std::endl;
        return 1;
    }

    // NaiveCounter counter;
    // LockCounter counter;
    int threshold = 1024;
    SloppyCounter counter(threshold);
    const int increments_per_thread = 1'000'000;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;

    std::cout << "Starting " << num_threads << " threads..." << std::endl;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&counter, increments_per_thread, threshold]() {
            int local_count = 0;
            for (int j = 0; j < increments_per_thread; ++j) {
                local_count++;

                if (local_count >= threshold) {
                    counter.increment(local_count);
                    local_count = 0;
                }
            }
            counter.increment(local_count);
        });
    }

    // for (int i = 0; i < num_threads; ++i) {
    //     threads.emplace_back([&counter, increments_per_thread]() {
    //         for (int j = 0; j < increments_per_thread; ++j) {
    //             counter.increment();
    //         }
    //     });
    // }

    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Duration: " << elapsed.count() << "s" << std::endl;
    std::cout << "Expected Value: " << (num_threads * increments_per_thread) << std::endl;
    std::cout << "Actual Value: " << counter.get_count() << std::endl;

    return 0;
}