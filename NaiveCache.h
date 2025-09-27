#ifndef NAIVE_CACHE_H
#define NAIVE_CACHE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <optional>
#include <algorithm>

template<typename K, typename V>
class NaiveCache {
private:
    size_t capacity;
    std::unordered_map<K, V> data;
    std::vector<K> usage_order;

public:
    NaiveCache(size_t cap) : capacity(cap) {}

    void put(const K& key, const V& value) {
        // If key exists, update it and move to back (most recent)
        if (data.count(key)) {
            data[key] = value;
            // O(n) operation to find and move the key
            usage_order.erase(std::remove(usage_order.begin(), usage_order.end(), key), usage_order.end());
            usage_order.push_back(key);
            return;
        }

        // If cache is full, evict the oldest (at the front of the vector)
        if (data.size() >= capacity) {
            K lru_key = usage_order.front();
            data.erase(lru_key);
            usage_order.erase(usage_order.begin());
        }

        data[key] = value;
        usage_order.push_back(key);
    }

    std::optional<V> get(const K& key) {
        if (data.count(key)) {
            // Move accessed key to back to mark as most recently used
            usage_order.erase(std::remove(usage_order.begin(), usage_order.end(), key), usage_order.end());
            usage_order.push_back(key);
            return data[key];
        }
        return std::nullopt;
    }
};

#endif // NAIVE_CACHE_H
