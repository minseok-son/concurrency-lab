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

# 1. Create a library for your data structures
# This compiles your .cpp files into a reusable "object"
add_library(counters_lib 
    src/counters/NaiveCounter.cpp
    src/counters/LockCounter.cpp
    src/counters/SloppyCounter.cpp
    # Add LockedCounter.cpp here later!
)

# 2. Define the executable for your benchmark
add_executable(counter_bench benchmarks/counter_bench.cpp)

# 3. Link the benchmark to the library and the thread library
target_link_libraries(counter_bench counters_lib)