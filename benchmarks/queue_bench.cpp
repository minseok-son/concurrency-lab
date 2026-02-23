#include <iostream>
#include <vector>
#include <thread>
#include "../include/queue/Queue.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <num_threads>" << std::endl;
        return 1;
    }

    int num_threads = std::stoi(argv[1]);
    const int NUM_OPS = 1'000'000;
    Queue queue;
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> enqueue_threads;
    std::vector<std::thread> dequeue_threads;

    for (int i = 0; i < num_threads; ++i) {
        enqueue_threads.emplace_back([&queue, NUM_OPS]() {
            for (int j = 0; j < NUM_OPS; ++j) {
                queue.enqueue(j);
            }
        });
    }

    for (int i = 0; i < num_threads; ++i) {
        dequeue_threads.emplace_back([&queue, NUM_OPS]() {
            for (int j = 0; j < NUM_OPS; ++j) {
                queue.dequeue();
            }
        });
    }

    for (auto& t : enqueue_threads) {
        t.join();
    }

    for (auto& t : dequeue_threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Duration: " << elapsed.count() << "s" << std::endl;
    std::cout << "Size: " << queue.get_size() << std::endl;
    return 0;
}