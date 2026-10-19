// Challenge: LRU cache
// A fixed-size cache that, when full, evicts the Least Recently Used entry.
// "Using" an entry means put() or get() on its key; contains() doesn't count.
//
//     LRUCache cache(2);
//     cache.put(1, 10);   cache.put(2, 20);
//     cache.get(1);       // 10, and key 1 is now the most recent
//     cache.put(3, 30);   // full: evicts key 2, the least recently used
//
// get and put must be O(1). The classic design: a std::list of (key, value)
// pairs ordered by recency, plus a std::unordered_map from key to that pair's
// list iterator. list.splice(list.begin(), list, it) moves a node to the front
// in O(1) without invalidating iterators.
//
// ./grade 18_capstone_projects/01_lru_cache

#include <cstddef>
#include <list>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

class LRUCache {
public:
    // Throws std::invalid_argument if capacity is 0.
    explicit LRUCache(std::size_t capacity) {
        throw "TODO";
    }

    // The value for key, or std::nullopt. A hit makes the key most recent.
    std::optional<int> get(int key) {
        throw "TODO";
    }

    // Insert or update key, making it most recent. Inserting into a full cache
    // first evicts the least recently used key.
    void put(int key, int value) {
        throw "TODO";
    }

    // Whether key is cached. Doesn't change recency.
    bool contains(int key) const {
        throw "TODO";
    }

    std::size_t size() const {
        throw "TODO";
    }

    std::size_t capacity() const {
        throw "TODO";
    }

    // Every cached key, most recently used first.
    std::vector<int> keys_by_recency() const {
        throw "TODO";
    }

private:
    // TODO: your data members
};
