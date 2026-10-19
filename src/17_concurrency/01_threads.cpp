// Exercise: Threads
// Split work into chunks and hand each chunk to its own std::thread.
//
// std::thread t(callable, args...) starts running at once; t.join() waits for it.
// Every thread must be joined before its std::thread object is destroyed.
// Give each thread its own output slot (e.g. partial[i]) so no two threads
// write the same memory. std::jthread joins itself in its destructor.
//
// ./grade 17_concurrency/01_threads

#include <thread>
#include <vector>

// Boundaries that split `size` items into `parts` contiguous chunks whose sizes
// differ by at most 1, bigger chunks first. Returns parts + 1 indices:
// chunk_bounds(10, 3) == {0, 4, 7, 10}, chunk_bounds(2, 4) == {0, 1, 2, 2, 2}.
// parts is at least 1.
std::vector<int> chunk_bounds(int size, int parts) {
    throw "TODO";
}

// Sum of values, with `thread_count` threads each summing one chunk.
// thread_count is at least 1 and may exceed values.size().
long long parallel_sum(const std::vector<int>& values, int thread_count) {
    throw "TODO";
}

// Square every element in place, using `thread_count` threads.
void parallel_square(std::vector<long long>& values, int thread_count) {
    throw "TODO";
}
