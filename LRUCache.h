#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <iostream>
#include <list>
#include <unordered_map>
#include <optional>

template<typename K, typename V>
class LRUCache {
private:
    size_t capacity;
    // The list stores pairs of (key, value) to maintain usage order.
    // The front of the list is the most recently used item.
    std::list<std::pair<K, V>> items_list;

    // The map provides O(1) lookup for items in the list.
    // It maps a key to an iterator pointing to the element in the list.
    std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> items_map;

public:
    // Constructor to initialize the cache with a given capacity.
    LRUCache(size_t cap) : capacity(cap) {
        if (capacity == 0) {
            throw std::invalid_argument("Cache capacity must be positive.");
        }
    }

    // Stores a key-value pair in the cache.
    void put(const K& key, const V& value) {
        // If the key already exists, remove the old entry first.
        auto it = items_map.find(key);
        if (it != items_map.end()) {
            items_list.erase(it->second);
            items_map.erase(it);
        }

        // Add the new item to the front of the list (most recently used).
        items_list.push_front({key, value});
        items_map[key] = items_list.begin();

        // If the cache is over capacity, evict the least recently used item.
        if (items_map.size() > capacity) {
            // The LRU item is at the back of the list.
            auto lru_item = items_list.back();
            items_map.erase(lru_item.first);
            items_list.pop_back();
        }
    }

    // Retrieves a value by its key. Returns std::nullopt if not found.
    std::optional<V> get(const K& key) {
        auto it = items_map.find(key);

        // Key not found (cache miss).
        if (it == items_map.end()) {
            return std::nullopt;
        }

        // Key found (cache hit). Move the accessed item to the front of the list.
        // std::list::splice is highly efficient as it just rearranges pointers.
        items_list.splice(items_list.begin(), items_list, it->second);
        
        return it->second->second;
    }

    // A helper function to display the cache's current state.
    void display() const {
        std::cout << "Cache content (MRU -> LRU): ";
        for (const auto& pair : items_list) {
            std::cout << "[" << pair.first << ":" << pair.second << "] ";
        }
        std::cout << std::endl;
    }
};

#endif // LRU_CACHE_H
