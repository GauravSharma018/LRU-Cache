#include <iostream>
#include <chrono>
#include <random>
#include "LRUCache.h"
#include "NaiveCache.h"

void demo_lru_cache() {
    std::cout << "--- LRU Cache Demonstration ---" << std::endl;
    LRUCache<int, std::string> cache(3);

    cache.put(1, "one");
    cache.display();
    cache.put(2, "two");
    cache.display();
    cache.put(3, "three");
    cache.display();

    std::cout << "\nAccessing key 1..." << std::endl;
    cache.get(1);
    cache.display();

    std::cout << "\nAdding key 4 (should evict key 2)..." << std::endl;
    cache.put(4, "four");
    cache.display();

    std::cout << "\nAccessing non-existent key 5..." << std::endl;
    auto val = cache.get(5);
    if (!val) {
        std::cout << "Key 5 not found in cache." << std::endl;
    }
    std::cout << "-----------------------------\n" << std::endl;
}

void run_benchmark() {
    const int num_operations = 100000;
    const int cache_capacity = 1000;
    const int key_range = 2000;

    LRUCache<int, int> lru_cache(cache_capacity);
    NaiveCache<int, int> naive_cache(cache_capacity);

    // Generate a sequence of operations to ensure both caches perform the same work
    std::vector<std::pair<int, int>> operations;
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> op_dist(0, 1); // 0 for put, 1 for get
    std::uniform_int_distribution<int> key_dist(0, key_range - 1);

    for (int i = 0; i < num_operations; ++i) {
        operations.push_back({op_dist(rng), key_dist(rng)});
    }

    // --- Benchmark LRUCache ---
    auto start_lru = std::chrono::high_resolution_clock::now();
    for (const auto& op : operations) {
        if (op.first == 0) { // put
            lru_cache.put(op.second, op.second);
        } else { // get
            lru_cache.get(op.second);
        }
    }
    auto end_lru = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> lru_duration = end_lru - start_lru;

    // --- Benchmark NaiveCache ---
    auto start_naive = std::chrono::high_resolution_clock::now();
    for (const auto& op : operations) {
        if (op.first == 0) { // put
            naive_cache.put(op.second, op.second);
        } else { // get
            naive_cache.get(op.second);
        }
    }
    auto end_naive = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> naive_duration = end_naive - start_naive;


    std::cout << "--- Performance Benchmark ---" << std::endl;
    std::cout << "Cache Capacity: " << cache_capacity << ", Operations: " << num_operations << std::endl;
    std::cout << "Optimized LRU Cache (HashMap + Doubly Linked List) took: " << lru_duration.count() << " ms" << std::endl;
    std::cout << "Naive Cache (HashMap + Vector) took: " << naive_duration.count() << " ms" << std::endl;
    std::cout << "---------------------------\n" << std::endl;
}

int main() {
    demo_lru_cache();
    run_benchmark();
    return 0;
}
