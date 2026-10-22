// === Lesson: Starting threads ================================================
//
// A std::thread runs a function on a new thread, starting the moment it's
// constructed. join() waits for it to finish:
//
//     void greet(std::string name) { std::cout << "hi " + name + "\n"; }
//
//     std::thread t(greet, "Ada");    // greet("Ada") is already running...
//     do_something_else();            // ...while this runs here
//     t.join();                       // wait until greet returns
//
// A std::thread that's still joinable when it's destroyed calls std::terminate,
// which ends the program, so join every thread on every path. std::jthread
// (C++20) joins itself in its destructor. Threads can be moved but not copied:
// keep them in a std::vector<std::thread> and add them with emplace_back.
//
// The arguments are copied into the new thread, even when the function takes a
// reference. To share a variable, capture it by reference in a lambda (or pass
// std::ref(x)), and make sure it outlives the thread:
//
//     std::vector<std::string> pages = load_pages();
//     std::vector<int> words(pages.size());        // one result slot per thread
//     std::vector<std::thread> workers;
//     for (std::size_t i = 0; i < pages.size(); ++i) {
//         workers.emplace_back([&pages, &words, i] {
//             words[i] = count_words(pages[i]);
//         });
//     }
//     for (std::thread &w : workers) w.join();     // now words is safe to read
//
// Capture the loop index by value ([i]), never by reference: by the time the
// thread runs, the loop may have moved on.
//
// Data races: two threads touching the same memory without synchronization,
// at least one of them writing, is undefined behavior. Lost updates are the
// usual symptom. The simplest cure is not to share: give each thread its own
// slot, or its own range of a vector (different elements are different memory),
// and combine the results after join(). Reading data nobody writes is fine.
// The grader's sanitizers don't detect races, so a racy program can pass by luck.
//
// An exception that escapes a thread's function calls std::terminate; it never
// reaches the code that started the thread.
//
// Read more: https://en.cppreference.com/w/cpp/thread/thread
//            https://en.cppreference.com/w/cpp/thread/jthread
//
// === Exercise: Threads =======================================================
// Split work into chunks and hand each chunk to its own std::thread.
//
// ./grade 17_concurrency/01_threads

#include <thread>
#include <vector>

// Return the boundaries that split `size` items into `parts` contiguous chunks.
// Chunk sizes differ by at most 1, and the bigger chunks come first.
// The result has parts + 1 indices, from 0 up to size. parts is at least 1.
// With more parts than items, the extra chunks are empty.
//
// Example:
//   chunk_bounds(9, 3) == {0, 3, 6, 9}
//   chunk_bounds(10, 3) == {0, 4, 7, 10}     // chunk sizes 4, 3, 3
//   chunk_bounds(2, 4) == {0, 1, 2, 2, 2}    // chunk sizes 1, 1, 0, 0
//
// Chunk i covers the indices from bounds[i] up to, but not including, bounds[i + 1].
std::vector<int> chunk_bounds(int size, int parts) {
    throw "TODO";
}

// Return the sum of values, using `thread_count` threads that each sum one chunk.
// thread_count is at least 1 and may exceed values.size().
// The total can be too big for an int, so add up in long long.
//
// Example:
//   parallel_sum({1, 2, 3, 4, 5}, 2) == 15
//   parallel_sum({10, -4, 6}, 8) == 12   // more threads than values
//   parallel_sum({}, 3) == 0
//
// The answer must match a plain loop's for every thread_count.
long long parallel_sum(const std::vector<int> &values, int thread_count) {
    throw "TODO";
}

// Square every element in place, using `thread_count` threads.
// Each element must be squared exactly once.
// thread_count may exceed values.size(), and values may be empty.
//
// Example:
//   values = {1, -2, 3, 4, 100'000}
//   parallel_square(values, 2);
//   values is now {1, 4, 9, 16, 10'000'000'000}
//
// Different elements are different memory, so threads on separate chunks need no lock.
void parallel_square(std::vector<long long> &values, int thread_count) {
    throw "TODO";
}
