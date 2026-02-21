# Concurrency Lab: Systems Optimization in C++

This repository explores the iterative evolution of data structures to achieve thread safety and high performance, directly applying concepts from **OSTEP** (*Operating Systems: Three Easy Pieces*).

---

## 1. The Naive Counter (Atomicity Failure)
The simplest counter implementation lacks any synchronization. While it functions correctly in a serial environment, it collapses under concurrent workloads.

### Single-Threaded Baseline (The Control)
Establishing a baseline duration and ensuring logic correctness before introducing parallel overhead.

| Metric | Result |
| :--- | :--- |
| **Thread Count** | 1 |
| **Average Duration** | 0.00451s |
| **Expected Value** | 1,000,000 |
| **Actual Value** | 1,000,000 |
| **Integrity** | ✅ **PASS** |

### Multi-Threaded Performance (The Failure)
When scaled to two threads, the implementation suffers from two primary systems-level failures:

1. **Lost Updates:** The final count is non-deterministic and incorrect because the `read-modify-write` cycle is not **atomic**.
2. **Cache Line Contention:** Even without locks, performance degrades. Each core constantly invalidates the other's L1 cache line via the **MESI Protocol**, leading to "True Sharing" and memory bus saturation.



| Iteration | Duration (s) | Actual Value | Expected Value | Status |
| :--- | :--- | :--- | :--- | :--- |
| 1 | 0.01307s | 1,296,248 | 2,000,000 | ❌ **FAIL** |
| 2 | 0.01266s | 1,129,993 | 2,000,000 | ❌ **FAIL** |
| 3 | 0.00884s | 1,656,625 | 2,000,000 | ❌ **FAIL** |
| 4 | 0.01501s | 1,218,031 | 2,000,000 | ❌ **FAIL** |
| 5 | 0.01375s | 1,468,146 | 2,000,000 | ❌ **FAIL** |

---

## 2. The Locked Counter (Serialized Correctness)
To achieve correctness, we introduce **Mutual Exclusion** via `std::mutex`. This ensures that the **Critical Section** (the increment) is only accessed by one thread at a time.

### The Synchronization Tax
While correctness is achieved, we observe a **~35x performance penalty** compared to the single-threaded baseline. This is due to:
* **Lock Contention:** Threads spend thousands of CPU cycles waiting for the mutex or being context-switched by the OS scheduler.
* **Serialization:** The hardware is forced to execute parallel tasks sequentially, negating the benefits of multiple cores.



| Iteration | Duration (s) | Expected | Actual | Integrity |
| :--- | :--- | :--- | :--- | :--- |
| 1 | 0.1753s | 2,000,000 | 2,000,000 | ✅ **PASS** |
| 2 | 0.1514s | 2,000,000 | 2,000,000 | ✅ **PASS** |
| 3 | 0.1652s | 2,000,000 | 2,000,000 | ✅ **PASS** |
| 4 | 0.1666s | 2,000,000 | 2,000,000 | ✅ **PASS** |
| 5 | 0.1663s | 2,000,000 | 2,000,000 | ✅ **PASS** |

---

## 3. The Sloppy Counter (Scalable Approximation)

The Sloppy Counter addresses the **Synchronization Tax** by decentralizing the counting process. Instead of threads competing for a single global lock (and triggering constant cache invalidations), each thread maintains a **local counter**.

### The Mechanism
1. Each thread increments its local variable.
2. Once the local count hits a threshold ($S = 1024$), it acquires the global lock, updates the global counter, and resets the local count.
3. This significantly reduces **Cache Line Ping-Ponging**, as threads primarily write to their own local cache lines.

### Performance Comparison (N=8 Million)

By relaxing the requirement for "instant accuracy," we achieve **Eventual Consistency** and massive throughput gains.

| Implementation | Threads | Threshold ($S$) | Duration | Speedup |
| :--- | :--- | :--- | :--- | :--- |
| **Control (Baseline)** | 1 | N/A | 0.02776s | 1.0x |
| **Sloppy Counter** | 8 | 1024 | 0.00712s | **~3.9x** |

### Trade-off Analysis
* **Accuracy:** Mid-process reads of the global counter are "sloppy" (the count can be off by $Threads \times S$).
* **Scalability:** Unlike the Locked Counter, which gets slower as threads are added, the Sloppy Counter scales almost linearly with core count until the threshold updates saturate the global lock.
* **Hardware Optimization:** This approach minimizes **True Sharing**. 

> **Technical Note:** The implementation avoids False Sharing—a phenomenon where independent variables reside on the same 64-byte cache line, triggering unnecessary cache invalidations. By using stack-allocated local counters, each thread operates on memory addresses separated by the thread stack guard gap (typically megabytes apart), ensuring zero overlap within the CPU's cache hierarchy.