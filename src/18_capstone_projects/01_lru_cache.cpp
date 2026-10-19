// === Lesson: Combining containers ============================================
//
// No single standard container is fast at everything. Many data structures
// pair two containers so that each covers the other's slow operations:
//
//     std::vector         index O(1); insert or erase in the middle O(n)
//     std::list           insert, erase or move a node O(1), given an iterator
//                         to it; no indexing, and finding a value is O(n)
//     std::unordered_map  find, insert and erase by key, O(1) on average
//
// std::list is a doubly linked list. Its standout operation is splice, which
// relinks a node into a new position without copying or allocating anything:
//
//     std::list<std::string> tabs{"mail", "news", "docs"};
//     auto docs = std::prev(tabs.end());        // iterator to "docs"
//     tabs.splice(tabs.begin(), tabs, docs);    // move it to the front, O(1)
//     // tabs is now docs, mail, news, and `docs` still points at "docs"
//
// front(), back(), push_front(), pop_back() and erase(it) are O(1) as well.
//
// Iterator stability decides what you may store. An iterator is a bookmark into
// a container, and some operations invalidate (break) them:
//
//     std::vector         a push_back that reallocates invalidates every
//                         iterator; erase invalidates from that element on
//     std::list           erase invalidates only the erased element; insert
//                         and splice never invalidate anything
//     std::unordered_map  erase invalidates only that element; a rehash during
//                         insert invalidates iterators, but not references
//
// So an iterator into a std::list can be saved in another container and used
// later, for as long as its element lives. When you erase an element, also
// erase everything that refers to it.
//
// A structured binding names the parts of a pair: auto& [key, value] = *it;
//
// Read more: https://en.cppreference.com/w/cpp/container/list/splice
//            https://en.cppreference.com/w/cpp/container
//
// === Challenge: LRU cache ====================================================
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
// list iterator.
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
