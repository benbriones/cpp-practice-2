#include <cstdlib>
#include <new>

#include "grader.hpp"
#include "10_memory/05_dynamic_array.cpp"

// Every new[] / delete[] in this program goes through these, so tests can count blocks.
int live_arrays = 0;
int arrays_allocated = 0;

void* operator new[](std::size_t size) {
    if (void* block = std::malloc(size == 0 ? 1 : size)) {
        ++live_arrays;
        ++arrays_allocated;
        return block;
    }
    throw std::bad_alloc();
}

void operator delete[](void* block) noexcept {
    if (block == nullptr) return;
    --live_arrays;
    std::free(block);
}

void operator delete[](void* block, std::size_t) noexcept { operator delete[](block); }

TEST("starts empty without allocating") {
    IntArray empty;
    CHECK_EQ(empty.size(), 0);
    CHECK_EQ(empty.capacity(), 0);
    CHECK_EQ(arrays_allocated, 0);
}

TEST("push_back and at") {
    IntArray numbers;
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    CHECK_EQ(numbers.size(), 3);
    CHECK_EQ(numbers.at(0), 10);
    CHECK_EQ(numbers.at(1), 20);
    CHECK_EQ(numbers.at(2), 30);
}

TEST("capacity doubles: 1, 2, 4, 8") {
    IntArray numbers;
    numbers.push_back(1);
    CHECK_EQ(numbers.capacity(), 1);
    numbers.push_back(2);
    CHECK_EQ(numbers.capacity(), 2);
    numbers.push_back(3);
    CHECK_EQ(numbers.capacity(), 4);
    numbers.push_back(4);
    CHECK_EQ(numbers.capacity(), 4);
    numbers.push_back(5);
    CHECK_EQ(numbers.capacity(), 8);
}

TEST("values survive many reallocations") {
    IntArray squares;
    for (int i = 0; i < 1000; ++i) squares.push_back(i * i);
    CHECK_EQ(squares.size(), 1000);
    for (int i : {0, 1, 2, 511, 512, 513, 999}) {
        CHECK_EQ(squares.at(static_cast<std::size_t>(i)), i * i);
    }
}

TEST("growth allocates rarely and frees old blocks") {
    IntArray numbers;
    for (int i = 0; i < 1000; ++i) numbers.push_back(i);
    CHECK_EQ(numbers.capacity(), 1024);
    CHECK_EQ(arrays_allocated, 11);
    CHECK_EQ(live_arrays, 1);
}

TEST("the destructor frees the block") {
    {
        IntArray numbers;
        for (int i = 0; i < 20; ++i) numbers.push_back(i);
    }
    CHECK_EQ(live_arrays, 0);
}

TEST("at: out of range throws std::out_of_range") {
    IntArray numbers;
    CHECK_THROWS(std::out_of_range, numbers.at(0));
    numbers.push_back(7);
    CHECK_THROWS(std::out_of_range, numbers.at(1));
    CHECK_THROWS(std::out_of_range, numbers.at(1'000'000));
}

TEST("set: overwrites, with the same bounds check") {
    IntArray numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.set(1, 99);
    CHECK_EQ(numbers.at(1), 99);
    CHECK_EQ(numbers.at(0), 1);
    CHECK_THROWS(std::out_of_range, numbers.set(2, 5));
}

TEST("pop_back: shrinks size, keeps capacity") {
    IntArray numbers;
    for (int i = 1; i <= 3; ++i) numbers.push_back(i);
    numbers.pop_back();
    CHECK_EQ(numbers.size(), 2);
    CHECK_EQ(numbers.capacity(), 4);
    CHECK_EQ(numbers.at(1), 2);
    CHECK_THROWS(std::out_of_range, numbers.at(2));
}

TEST("pop_back: empty array throws, then push_back still works") {
    IntArray numbers;
    CHECK_THROWS(std::out_of_range, numbers.pop_back());
    numbers.push_back(1);
    numbers.pop_back();
    CHECK_THROWS(std::out_of_range, numbers.pop_back());
    numbers.push_back(5);
    CHECK_EQ(numbers.at(0), 5);
}

TEST("reserve: grows to exactly n, keeps elements") {
    IntArray numbers;
    numbers.push_back(4);
    numbers.push_back(5);
    numbers.reserve(10);
    CHECK_EQ(numbers.capacity(), 10);
    CHECK_EQ(numbers.size(), 2);
    CHECK_EQ(numbers.at(0), 4);
    CHECK_EQ(numbers.at(1), 5);
    CHECK_EQ(live_arrays, 1);
}

TEST("reserve: never shrinks, and avoids later reallocations") {
    IntArray numbers;
    numbers.reserve(8);
    numbers.reserve(3);
    CHECK_EQ(numbers.capacity(), 8);
    int allocated_after_reserve = arrays_allocated;
    for (int i = 0; i < 8; ++i) numbers.push_back(i);
    CHECK_EQ(arrays_allocated, allocated_after_reserve);
}
