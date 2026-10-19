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

// How many primes p satisfy from <= p < to.
int count_primes(int from, int to) {
    throw "TODO";
}

// Primes below `limit`, counted by `parts` std::async tasks that each handle
// one range of numbers. parts is at least 1.
int count_primes_async(int limit, int parts) {
    throw "TODO";
}

// Parse every text with std::stoi in its own async task and return the sum.
// If any text isn't a number, std::stoi throws std::invalid_argument; let it
// reach the caller (future.get() rethrows it).
int sum_parsed_async(const std::vector<std::string>& texts) {
    throw "TODO";
}
