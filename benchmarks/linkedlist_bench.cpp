#include <iostream>
#include <vector>
#include <thread>
#include "../include/linkedlist/NaiveLinkedList.h"
#include "../include/linkedlist/LockLinkedList.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <num_push_threads> <num_pop_threads>" << std::endl;
        return 1;
    }

    int num_push_threads;
    int num_pop_threads;
    try {
        num_push_threads = std::stoi(argv[1]);
        num_pop_threads = std::stoi(argv[2]);
    } catch (const std::exception& e) {
        std::cerr << "Invalid number of threads: " << argv[1] << std::endl;
        return 1;
    }

    const int ops_per_thread = 100'000;
    // LinkedList list;
    LockLinkedList list;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> push_threads;
    std::vector<std::thread> pop_threads;
    for (int i = 0; i < num_push_threads; ++i) {
        push_threads.emplace_back([&list, ops_per_thread]() {
            for (int j = 0; j < ops_per_thread; ++j) {
                list.pushFront(j);
            }
        });
    }

    for (int i = 0; i < num_pop_threads; ++i) {
        pop_threads.emplace_back([&list, ops_per_thread]() {
            for (int j = 0; j < ops_per_thread; ++j) {
                list.popFront();
            }
        });
    }

    for (auto& t : push_threads) {
        t.join();
    }

    for (auto& t : pop_threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Duration: " << elapsed.count() << "s" << std::endl;
    std::cout << "Expected Size: " << (num_push_threads * ops_per_thread) - (num_pop_threads * ops_per_thread) << std::endl;
    std::cout << "Actual Size:   " << list.size() << std::endl;


    return 0;
}