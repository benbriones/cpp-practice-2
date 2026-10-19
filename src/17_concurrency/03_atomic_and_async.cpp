// Exercise: Atomics and async tasks
// Two lighter-weight tools than a mutex.
//
// std::atomic<int> n{0}; supports ++n, n += 5 and n.load() safely from any
// thread, with no lock. std::async(std::launch::async, f, args...) runs f on
// another thread and returns a std::future; future.get() waits for the result
// and rethrows any exception the task threw.
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
