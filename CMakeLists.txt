cmake_minimum_required(VERSION 3.16)
project(concurrency_lab LANGUAGES CXX)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Thread Sanitizer and useful warnings
# Note: Remove "-fsanitize=thread" if you are doing pure performance 
# benchmarks, as the sanitizer adds overhead.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")

# Tell CMake where to find your header files
include_directories(include)

# 1. The Counters Library
add_library(counters_lib 
    src/counters/NaiveCounter.cpp
    src/counters/LockCounter.cpp
    src/counters/SloppyCounter.cpp
)

# 2. The LinkedList Library
add_library(ll_lib 
    src/linkedlist/NaiveLinkedList.cpp
    src/linkedlist/LockLinkedList.cpp
)

add_library(q_lib
    src/queue/Queue.cpp
    src/queue/BoundedBuffer.cpp
)

# 3. Link only what you need
add_executable(counter_bench benchmarks/counter_bench.cpp)
target_link_libraries(counter_bench counters_lib pthread)

add_executable(ll_bench benchmarks/linkedlist_bench.cpp)
target_link_libraries(ll_bench ll_lib pthread)

add_executable(q_bench benchmarks/queue_bench.cpp)
target_link_libraries(q_bench q_lib pthread)