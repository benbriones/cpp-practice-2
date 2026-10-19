#include "grader.hpp"
#include "18_capstone_projects/01_lru_cache.cpp"

TEST("constructor: capacity 0 is rejected") {
    CHECK_THROWS(std::invalid_argument, LRUCache(0));
}

TEST("put and get") {
    LRUCache cache(3);
    cache.put(1, 10);
    cache.put(2, 20);
    CHECK_EQ(cache.get(1), 10);
    CHECK_EQ(cache.get(2), 20);
    CHECK_EQ(cache.get(3), std::nullopt);
    CHECK_EQ(cache.size(), 2);
    CHECK_EQ(cache.capacity(), 3);
}

TEST("put: updating a key replaces its value without growing") {
    LRUCache cache(2);
    cache.put(1, 10);
    cache.put(1, 11);
    CHECK_EQ(cache.get(1), 11);
    CHECK_EQ(cache.size(), 1);
}

TEST("eviction: the least recently put key goes first") {
    LRUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    CHECK_EQ(cache.contains(1), false);
    CHECK_EQ(cache.get(2), 20);
    CHECK_EQ(cache.get(3), 30);
    CHECK_EQ(cache.size(), 2);
}

TEST("eviction: get makes a key recent again") {
    LRUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.get(1);
    cache.put(3, 30);
    CHECK_EQ(cache.contains(2), false);
    CHECK_EQ(cache.contains(1), true);
}

TEST("eviction: updating a key makes it recent again") {
    LRUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(1, 15);
    cache.put(3, 30);
    CHECK_EQ(cache.contains(2), false);
    CHECK_EQ(cache.get(1), 15);
}

TEST("contains: doesn't change recency") {
    LRUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    CHECK_EQ(cache.contains(1), true);
    cache.put(3, 30);
    CHECK_EQ(cache.contains(1), false);
}

TEST("a miss doesn't change anything") {
    LRUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    CHECK_EQ(cache.get(99), std::nullopt);
    CHECK_EQ(cache.keys_by_recency(), {2, 1});
}

TEST("keys_by_recency: most recent first") {
    LRUCache cache(3);
    CHECK_EQ(cache.keys_by_recency(), {});
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    CHECK_EQ(cache.keys_by_recency(), {3, 2, 1});
    cache.get(1);
    CHECK_EQ(cache.keys_by_recency(), {1, 3, 2});
    cache.put(4, 40);
    CHECK_EQ(cache.keys_by_recency(), {4, 1, 3});
}

TEST("capacity 1") {
    LRUCache cache(1);
    cache.put(1, 10);
    cache.put(2, 20);
    CHECK_EQ(cache.get(1), std::nullopt);
    CHECK_EQ(cache.get(2), 20);
    CHECK_EQ(cache.size(), 1);
}

TEST("fast: 140,000 operations on a 20,000-entry cache (needs O(1) get and put)") {
    LRUCache cache(20'000);
    for (int i = 0; i < 20'000; ++i) cache.put(i, i);
    long long total = 0;
    for (int round = 0; round < 5; ++round) {
        for (int i = 0; i < 20'000; ++i) total += cache.get(i).value_or(-1'000'000);
    }
    for (int i = 20'000; i < 40'000; ++i) cache.put(i, i);
    CHECK_EQ(total, 999'950'000);
    CHECK_EQ(cache.size(), 20'000);
    CHECK_EQ(cache.contains(0), false);
    CHECK_EQ(cache.contains(19'999), false);
    CHECK_EQ(cache.get(39'999), 39'999);
}
