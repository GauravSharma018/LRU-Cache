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

## 📂 File Structure & Significance

Each file in this project serves a specific and crucial role, working together to create a complete and demonstrable solution.

### `LRUCache.h` (The Core Engine ⚙️)
* **What it is:** This file implements a high-performance LRU (Least Recently Used) Cache. Its primary goal is to perform both get and put operations in O(1), or constant average time.

Core Idea
To achieve O(1) performance for both lookups and reordering, this implementation uses two data structures working together: a hash map for instant lookups and a doubly linked list for instant reordering.

Imagine a VIP club line:

The doubly linked list (items_list) is the line of people. Anyone who just entered or was just spoken to moves to the front. The person who has been waiting the longest without being spoken to is at the back.

The hash map (items_map) is the bouncer's list. The bouncer can look up any person's name on the list and instantly find exactly where they are standing in line.

Data Structures Explained
std::list<std::pair<K, V>> items_list;

What it is: A C++ standard library doubly linked list.

Its Role: To maintain the order of usage.

The front of the list holds the Most Recently Used (MRU) item.

The back of the list holds the Least Recently Used (LRU) item.

Why a doubly linked list? It's the perfect choice because adding an item to the front (push_front) or removing one from the back (pop_back) are O(1) operations. Crucially, if you have a pointer (an iterator) to any element in the middle, you can move it or remove it in O(1) time.

std::unordered_map<K, typename std::list<...>::iterator> items_map;

What it is: A C++ standard library hash map.

Its Role: To provide instant (O(1)) lookups.

How it works: It stores the cache key and maps it directly to an iterator—essentially a pointer to that key's corresponding node within the items_list. This direct link is the key to the cache's efficiency.

Key Operations in Detail
put(key, value)
Check for Existing Key: It first checks the items_map to see if the key already exists.

Update/Remove: If the key exists, the old entry is removed from both the items_list (using its iterator) and the items_map.

Add New Item: The new (key, value) pair is added to the front of the items_list, marking it as the new MRU item.

Update Map: A new entry is created in items_map, mapping the key to the iterator of the newly added element at the front of the list.

Evict if Full: If the cache size now exceeds its capacity, the LRU item is evicted. This is done by removing the element from the back of items_list (pop_back) and deleting its key from items_map.

get(key)
Lookup: It uses the items_map to find the key in O(1) time. If it's not found, it's a cache miss, and it returns std::nullopt.

Cache Hit: If the key is found, it's a cache hit.

Reorder: This is the most important step. The accessed item must now become the MRU. The code uses items_list.splice(items_list.begin(), items_list, iterator). This is a highly efficient O(1) operation that moves the accessed node from its current position to the front of the list simply by rearranging pointers, without creating or destroying any elements.

Return Value: The value associated with the key is returned. 

* **Significance:** This file showcases the primary solution, using a hash map (`std::unordered_map`) and a doubly linked list (`std::list`) to achieve the target **O(1) time complexity** for both `get` and `put` operations. It is the main deliverable and demonstrates the core technical skill. This is the most important file and the heart of your project. Its purpose is to contain the actual implementation of the high-performance, optimized LRU Cache. This is the primary solution you built, showcasing your ability to use advanced data structures (std::unordered_map + std::list) to achieve O(1) efficiency.
      
In short, this file is the "product" itself.

### `NaiveCache.h` (The Benchmark 📊)
* **What it is:** This file implements a cache with the same functionality but with a simpler design. Its purpose is to serve as a benchmark to prove why the optimized LRUCache is superior.

Core Idea
This version also uses a hash map for fast lookups but uses a simple vector (a dynamic array) to keep track of the usage order. While easier to reason about, this choice creates a significant performance bottleneck.

Data Structures Explained
std::unordered_map<K, V> data;

What it is: A hash map.

Its Role: Provides O(1) lookups and stores the actual key-value data.

std::vector<K> usage_order;

What it is: A C++ standard library vector (dynamic array).

Its Role: To maintain the order of usage. The oldest item is at the front (index 0) and the newest item is at the back.

The Performance Bottleneck
The problem with using a vector to maintain order is that reordering is very slow.

When you get or put an existing item, you need to mark it as the most recently used. In this implementation, that means finding the key inside the usage_order vector, removing it, and adding it to the end.

Finding an item in a vector requires a linear scan, which is an O(n) operation.

The line std::remove(usage_order.begin(), usage_order.end(), key) performs this slow linear scan every time there is a cache hit. As the number of items in the cache grows, this operation becomes prohibitively expensive.

* **Significance:** This file's purpose is to provide a **baseline for comparison**. By benchmarking the optimized cache against this naive version, the project offers concrete proof of the performance gains achieved through a better choice of data structures. The purpose of this file is to provide a baseline for comparison. It implements a simpler, less efficient cache that is easy to understand but performs poorly (O(n) operations).

You need this file to prove that your optimized LRUCache is actually better. By running the same tasks on both caches and comparing their execution times, you provide concrete evidence of the performance gains your design achieves. It directly addresses the goal: "Benchmarked performance... to highlight optimization."

In short, this file is the "control group" for your experiment.

### `main.cpp` (The Driver 🚀)
* **What it is:** The entry point of the application.
* **Significance:** A class definition is just a blueprint; this file brings it to life. It **demonstrates how to use the `LRUCache`**, runs the performance benchmark on both cache types, and prints the results to the console. It turns the library into a tangible, executable program. A class definition like LRUCache.h is just a blueprint; it doesn't run on its own. The main.cpp file is the entry point that brings your project to life.

Its jobs are to:

Demonstrate how to create and use your LRUCache.

Execute the benchmark by running a series of operations on both caches.

Measure the performance using a timer.

Print the final results to the console for the user to see.

In short, this file is the "test track" where you run the engine and show its results.

---
## 🛠️ How to Compile and Run

You will need a C++ compiler that supports the C++17 standard (for `std::optional`).

1.  **Clone the repository**:
    ```bash
    git clone https://github.com/GauravSharma018/LRU-Cache/
    cd C:\Users\gaura\Desktop\Coding\LRU-Cache
    ```

2.  **Compile the project**:
    Use a C++ compiler like g++ to compile the `main.cpp` file.
    ```bash
    g++ main.cpp -o lru_benchmark -std=c++17
    ```
    * `-std=c++17`: Enables C++17 features.
    * `-O2`: Enables compiler optimizations for a more realistic benchmark.

3.  **Run the benchmark**:
    ```bash
    .\lru_benchmark.exe
    ```
### 📊 Summary of Differences
```
  Aspect	            LRUCache.h (Optimized)	      NaiveCache.h (Simple)	                             Why it Matters
Order Tracking	              std::list 	            std::vector 	               The list allows for O(1) reordering, while the vector is O(n).
                           (Doubly Linked List)       (Dynamic Array)
get() Complexity	           O(1)	                       O(n)	                        The optimized cache is consistently fast, regardless of size.
put() (update)          	   O(1)	                       O(n)	                        The naive cache slows down dramatically with frequent updates.
  Complexity
Overall Efficiency	           High                        Low	                         For any real-world caching scenario, the O(1) performance of the                                                                                                                                             LRUCache is essential.
```

### Example Output
```
--- LRU Cache Demonstration ---
Cache content (MRU -> LRU): [1:one]
Cache content (MRU -> LRU): [2:two] [1:one]
Cache content (MRU -> LRU): [3:three] [2:two] [1:one]  

Accessing key 1...
Cache content (MRU -> LRU): [1:one] [3:three] [2:two]  

Adding key 4 (should evict key 2)...
Cache content (MRU -> LRU): [4:four] [1:one] [3:three] 

Accessing non-existent key 5...
Key 5 not found in cache.
-----------------------------

--- Performance Benchmark ---
Cache Capacity: 1000, Operations: 100000
Optimized LRU Cache (HashMap + Doubly Linked List) took: 139.614 ms
Naive Cache (HashMap + Vector) took: 397.197 ms
---------------------------
```

## 📄 License
This project is open-source and available under the **MIT License**. See the `LICENSE` file for more details.
