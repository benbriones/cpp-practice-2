// === Lesson: Atomics and async tasks =========================================
//
// std::atomic<T> makes each operation on one variable indivisible, without a
// mutex. It's the tool for counters, flags and running totals:
//
//     std::atomic<long> bytes_sent{0};
//     std::atomic<bool> cancelled{false};
//
//     bytes_sent += n;                // one indivisible read-modify-write
//     ++bytes_sent;                   // also indivisible, like fetch_add(1)
//     bytes_sent = bytes_sent + n;    // two steps, a load then a store: another
//                                     // thread's update in between is lost
//     if (cancelled.load()) return;   // safe to read from any thread
//
// An atomic protects one variable. When several values must change together,
// use a mutex. Atomics can't be copied or moved.
//
// std::async runs a function on another thread and returns a std::future, a
// handle to a result that will exist later:
//
//     std::future<std::size_t> pending =
//         std::async(std::launch::async, count_words, std::cref(book));
//     do_other_work();                     // count_words runs meanwhile
//     std::size_t words = pending.get();   // waits for it, then gives the result
//
// - Pass std::launch::async. Without it, the task may be deferred and run on
//   the calling thread, only when get() is called.
// - get() works once. If the task threw, get() rethrows that exception in the
//   caller, so errors travel back the way results do.
// - A future from std::async waits for its task when it's destroyed. Calling
//   std::async and then get() for each task in turn runs them one at a time; to
//   run several at once, start them all, keep the futures in a vector, then
//   get() each result.
// - Like std::thread, std::async copies its arguments; std::cref(x) passes a
//   const reference instead.
//
// Read more: https://en.cppreference.com/w/cpp/atomic/atomic
//            https://en.cppreference.com/w/cpp/thread/async
//
// === Exercise: Atomics and async tasks =======================================
// Two lighter-weight tools than a mutex.
//
// ./grade 17_concurrency/03_atomic_and_async

#include <atomic>
#include <future>
#include <string>
#include <vector>

// A thread-safe counter with no mutex.
// It starts at 0. increment() adds 1, and value() reads the count.
//
// Example:
//   8 threads each call counter.increment() 20,000 times
//   after joining them all, counter.value() is 160,000
class AtomicCounter {
public:
    void increment() {
        throw "TODO";
    }

    int value() const {
        throw "TODO";
    }

private:
    // TODO: an atomic count
};

// Given.
bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= n / i; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// Return how many primes p satisfy from <= p < to.
// The range includes from but not to, so from == to gives 0.
//
// Example:
//   count_primes(0, 10) == 4    // 2, 3, 5, 7
//   count_primes(10, 20) == 4   // 11, 13, 17, 19
//   count_primes(2, 3) == 1
//   count_primes(20, 20) == 0
int count_primes(int from, int to) {
    throw "TODO";
}

// Return how many primes are below `limit`.
// Count them with `parts` std::async tasks that each handle one range of numbers.
// parts is at least 1, and may be more than limit.
//
// Example:
//   count_primes_async(10, 1) == 4
//   count_primes_async(100, 3) == 25
//   count_primes_async(5, 10) == 2   // more parts than numbers
//   count_primes_async(0, 4) == 0
//
// Start every task before calling get() on any, so they run at the same time.
int count_primes_async(int limit, int parts) {
    throw "TODO";
}

// Parse every text with std::stoi in its own async task and return the sum.
// An empty vector gives 0.
// If any text isn't a number, std::stoi throws std::invalid_argument; let it
// reach the caller (future.get() rethrows it).
//
// Example:
//   sum_parsed_async({"1", "20", "-3", "300"}) == 318
//   sum_parsed_async({}) == 0
//   sum_parsed_async({"1", "two", "3"}) throws std::invalid_argument
//
// No catch is needed: get() carries the task's exception back to the caller.
int sum_parsed_async(const std::vector<std::string> &texts) {
    throw "TODO";
}
