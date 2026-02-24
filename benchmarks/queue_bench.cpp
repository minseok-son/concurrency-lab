#include <iostream>
#include <vector>
#include <thread>
#include "../include/queue/Queue.h"
#include "../include/queue/BoundedBuffer.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <num_threads>" << std::endl;
        return 1;
    }

    int num_threads = std::stoi(argv[1]);
    const int NUM_OPS = 1'000'000;
    // Queue queue;
    BoundedBuffer queue;
    queue.print_address();
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> producer;
    std::vector<std::thread> consumer;

    for (int i = 0; i < num_threads; ++i) {
        producer.emplace_back([&queue, NUM_OPS]() {
            for (int j = 0; j < NUM_OPS; ++j) {
                queue.produce(j);
            }
        });
    }

    for (int i = 0; i < num_threads; ++i) {
        consumer.emplace_back([&queue, NUM_OPS]() {
            for (int j = 0; j < NUM_OPS; ++j) {
                queue.consume();
            }
        });
    }

    for (auto& t : producer) {
        t.join();
    }

    for (auto& t : consumer) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Duration: " << elapsed.count() << "s" << std::endl;
    std::cout << "Size: " << queue.get_size() << std::endl;
    return 0;
}