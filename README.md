# C++ LRU Cache Implementation

This project is a C++ implementation of a **Least Recently Used (LRU) Cache**, a common caching strategy that discards the least recently used items first when the cache reaches its limit. This implementation is built using a combination of a **Hash Map (`std::unordered_map`)** and a **Doubly Linked List (`std::list`)** to achieve O(1) time complexity for both `get` and `put` operations.

The repository also includes a benchmark that compares this optimized implementation against a naive cache design to highlight the significant performance improvements.

---
## ✨ Core Concepts

The O(1) performance is achieved by leveraging the strengths of two different data structures:

* **`std::unordered_map` (Hash Map)**: Provides average O(1) time complexity for insertions, deletions, and lookups. In this project, it stores the cache keys and a pointer (an iterator) to the corresponding node in the doubly linked list.

* **`std::list` (Doubly Linked List)**: Provides O(1) time complexity for adding elements to the front and removing elements from any position (given an iterator). It is used to maintain the usage order of the cache items. The **most recently used (MRU)** item is at the front, and the **least recently used (LRU)** item is at the back.

When an item is accessed (`get`) or added (`put`), it's moved to the front of the list. When the cache is full and a new item is added, the item at the back of the list is evicted.



---
## 🚀 Features

* **O(1) Get/Put Operations**: All core cache operations run in constant average time.
* **Template-based Design**: The `LRUCache` class is generic and can be used with any key and value types.
* **Fixed Capacity**: The cache respects a maximum capacity, automatically evicting the least recently used item when full.
* **Modern C++**: Uses modern C++ features like `std::optional` for safe return values from the `get` method.
* **Performance Benchmark**: Includes a `main.cpp` that demonstrates the cache's functionality and benchmarks its performance against a naive implementation (using a `std::vector` for usage tracking), which has O(n) eviction complexity.

---
## 📂 File Structure

* `LRUCache.h`: The header-only implementation of the optimized LRU Cache.
* `NaiveCache.h`: An implementation of a simple cache with O(n) complexity for comparison.
* `main.cpp`: The main driver file that includes a functional demonstration and the performance benchmark.
* `README.md`: This file.

---
## 🛠️ How to Compile and Run

You will need a C++ compiler that supports the C++17 standard (for `std::optional`).

1.  **Clone the repository**:
    ```bash
    git clone [https://github.com/your-username/lru-cache-cpp.git](https://github.com/your-username/lru-cache-cpp.git)
    cd lru-cache-cpp
    ```

2.  **Compile the project**:
    Use a C++ compiler like g++ to compile the `main.cpp` file.
    ```bash
    g++ main.cpp -o lru_benchmark -std=c++17 -O2
    ```
    * `-std=c++17`: Enables C++17 features.
    * `-O2`: Enables compiler optimizations for a more realistic benchmark.

3.  **Run the benchmark**:
    ```bash
    ./lru_benchmark
    ```

### Example Output
