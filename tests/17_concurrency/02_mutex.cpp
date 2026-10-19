#include "grader.hpp"
#include "17_concurrency/02_mutex.cpp"

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

    Worker(Worker&&) = delete;

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

TEST("SafeCounter: single thread") {
    SafeCounter counter;
    counter.increment();
    counter.increment();
    counter.add(5);
    const SafeCounter& view = counter;
    CHECK_EQ(view.value(), 7);
}

TEST("SafeCounter: starts at zero") {
    SafeCounter counter;
    CHECK_EQ(counter.value(), 0);
}

TEST("SafeCounter: 8 threads incrementing at once") {
    SafeCounter counter;
    std::list<Worker> threads;
    for (int t = 0; t < 8; ++t) {
        threads.emplace_back([&counter] {
            for (int i = 0; i < 20'000; ++i) counter.increment();
        });
    }
    for (auto& thread : threads) thread.join();
    CHECK_EQ(counter.value(), 160'000);
}

TEST("SafeCounter: add and increment mixed across threads") {
    SafeCounter counter;
    std::list<Worker> threads;
    for (int t = 0; t < 4; ++t) {
        threads.emplace_back([&counter] {
            for (int i = 0; i < 10'000; ++i) {
                counter.add(3);
                counter.increment();
            }
        });
    }
    for (auto& thread : threads) thread.join();
    CHECK_EQ(counter.value(), 160'000);
}

TEST("transfer: moves money") {
    Account alice{100};
    Account bob{20};
    CHECK_EQ(transfer(alice, bob, 30), true);
    CHECK_EQ(alice.balance, 70);
    CHECK_EQ(bob.balance, 50);
}

TEST("transfer: refuses bad amounts and overdrafts") {
    Account alice{100};
    Account bob{20};
    CHECK_EQ(transfer(alice, bob, 0), false);
    CHECK_EQ(transfer(alice, bob, -5), false);
    CHECK_EQ(transfer(alice, bob, 101), false);
    CHECK_EQ(alice.balance, 100);
    CHECK_EQ(bob.balance, 20);
}

TEST("transfer: whole balance is allowed") {
    Account alice{100};
    Account bob{0};
    CHECK_EQ(transfer(alice, bob, 100), true);
    CHECK_EQ(alice.balance, 0);
    CHECK_EQ(bob.balance, 100);
}

TEST("transfer: same account is refused without deadlocking") {
    Account alice{100};
    CHECK_EQ(transfer(alice, alice, 10), false);
    CHECK_EQ(alice.balance, 100);
}

TEST("read_balance") {
    Account alice{42};
    CHECK_EQ(read_balance(alice), 42);
}

TEST("transfer: opposite directions at once, no deadlock, money conserved") {
    Account a{1'000'000};
    Account b{1'000'000};
    std::list<Worker> threads;
    for (int t = 0; t < 4; ++t) {
        threads.emplace_back([&a, &b, t] {
            for (int i = 0; i < 5'000; ++i) {
                if (t % 2 == 0) {
                    transfer(a, b, 3);
                } else {
                    transfer(b, a, 2);
                }
            }
        });
    }
    threads.emplace_back([&a, &b] {
        for (int i = 0; i < 2'000; ++i) {
            long long total = read_balance(a) + read_balance(b);
            (void)total;
        }
    });
    for (auto& thread : threads) thread.join();
    CHECK_EQ(a.balance + b.balance, 2'000'000);
    CHECK_EQ(a.balance, 1'000'000 - 2 * 5'000 * 3 + 2 * 5'000 * 2);
}
