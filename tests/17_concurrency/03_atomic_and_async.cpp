#include "grader.hpp"
#include "17_concurrency/03_atomic_and_async.cpp"

#include <exception>
#include <list>
#include <thread>

// A thread whose exceptions (including a TODO stub) are rethrown on the test thread by join().
class Worker {
public:
    template <class F>
    explicit Worker(F body)
        : thread_([this, body] {
              try {
                  body();
              } catch (...) {
                  error_ = std::current_exception();
              }
          }) {}

    Worker(Worker &&) = delete;

    ~Worker() {
        if (!thread_.joinable()) return;
        if (std::uncaught_exceptions() > 0) {
            thread_.detach();  // the test already failed; don't wait on a thread that may be stuck
        } else {
            thread_.join();
        }
    }

    void join() {
        thread_.join();
        if (error_) std::rethrow_exception(error_);
    }

private:
    std::exception_ptr error_;
    std::thread thread_;
};

TEST("AtomicCounter: single thread") {
    AtomicCounter counter;
    CHECK_EQ(counter.value(), 0);
    counter.increment();
    counter.increment();
    const AtomicCounter &view = counter;
    CHECK_EQ(view.value(), 2);
}

TEST("AtomicCounter: 8 threads incrementing at once") {
    AtomicCounter counter;
    std::list<Worker> threads;
    for (int t = 0; t < 8; ++t) {
        threads.emplace_back([&counter] {
            for (int i = 0; i < 20'000; ++i) counter.increment();
        });
    }
    for (auto &thread : threads) thread.join();
    CHECK_EQ(counter.value(), 160'000);
}

TEST("count_primes: half-open ranges") {
    CHECK_EQ(count_primes(0, 10), 4);
    CHECK_EQ(count_primes(2, 3), 1);
    CHECK_EQ(count_primes(10, 20), 4);
    CHECK_EQ(count_primes(20, 20), 0);
}

TEST("count_primes_async: matches known counts") {
    CHECK_EQ(count_primes_async(10, 1), 4);
    CHECK_EQ(count_primes_async(100, 3), 25);
    CHECK_EQ(count_primes_async(100'000, 4), 9'592);
}

TEST("count_primes_async: any number of parts") {
    for (int parts : {1, 2, 5, 13}) {
        CHECK_EQ(count_primes_async(10'000, parts), 1'229);
    }
}

TEST("count_primes_async: more parts than numbers") {
    CHECK_EQ(count_primes_async(5, 10), 2);
    CHECK_EQ(count_primes_async(0, 4), 0);
}

TEST("sum_parsed_async: adds the numbers") {
    CHECK_EQ(sum_parsed_async({"1", "20", "-3", "300"}), 318);
    CHECK_EQ(sum_parsed_async({}), 0);
}

TEST("sum_parsed_async: an exception in a task reaches the caller") {
    CHECK_THROWS(std::invalid_argument, sum_parsed_async({"1", "two", "3"}));
}
