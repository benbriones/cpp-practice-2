#include "grader.hpp"
#include "17_concurrency/04_blocking_queue.cpp"

#include <algorithm>
#include <chrono>
#include <exception>
#include <list>
#include <thread>
#include <vector>

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

TEST("push and try_pop: first in, first out") {
    BlockingQueue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    CHECK_EQ(queue.size(), 3);
    CHECK_EQ(queue.try_pop(), 1);
    CHECK_EQ(queue.try_pop(), 2);
    CHECK_EQ(queue.try_pop(), 3);
    CHECK_EQ(queue.size(), 0);
}

TEST("try_pop: empty queue gives nullopt without waiting") {
    BlockingQueue<int> queue;
    CHECK_EQ(queue.try_pop(), std::nullopt);
}

TEST("pop: returns an item that's already there") {
    BlockingQueue<std::string> queue;
    queue.push("job");
    CHECK_EQ(queue.pop(), "job");
}

TEST("close: remaining items still come out, then nullopt") {
    BlockingQueue<int> queue;
    queue.push(7);
    queue.push(8);
    queue.close();
    CHECK_EQ(queue.closed(), true);
    CHECK_EQ(queue.pop(), 7);
    CHECK_EQ(queue.pop(), 8);
    CHECK_EQ(queue.pop(), std::nullopt);
}

TEST("close: push afterwards throws std::logic_error") {
    BlockingQueue<int> queue;
    CHECK_EQ(queue.closed(), false);
    queue.close();
    CHECK_THROWS(std::logic_error, queue.push(1));
}

TEST("pop: waits for another thread's push") {
    BlockingQueue<int> queue;
    std::optional<int> received;
    Worker consumer([&] { received = queue.pop(); });
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    queue.push(42);
    consumer.join();
    CHECK_EQ(received, 42);
}

TEST("close: wakes a pop that is waiting on an empty queue") {
    BlockingQueue<int> queue;
    std::optional<int> received = -1;
    Worker consumer([&] { received = queue.pop(); });
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    queue.close();
    consumer.join();
    CHECK_EQ(received, std::nullopt);
}

TEST("works with move-only types") {
    BlockingQueue<std::unique_ptr<int>> queue;
    queue.push(std::make_unique<int>(5));
    std::optional<std::unique_ptr<int>> item = queue.pop();
    CHECK(item.has_value() && *item && **item == 5, "Expected to pop a unique_ptr holding 5");
}

TEST("4 producers and 4 consumers: every item arrives exactly once") {
    BlockingQueue<int> queue;
    std::vector<std::vector<int>> received(4);
    std::list<Worker> consumers;
    for (int c = 0; c < 4; ++c) {
        consumers.emplace_back([&queue, &received, c] {
            while (std::optional<int> item = queue.pop()) received[static_cast<std::size_t>(c)].push_back(*item);
        });
    }
    std::list<Worker> producers;
    for (int p = 0; p < 4; ++p) {
        producers.emplace_back([&queue, p] {
            for (int i = 0; i < 2'000; ++i) queue.push(p * 2'000 + i);
        });
    }
    for (auto &producer : producers) producer.join();
    queue.close();
    for (auto &consumer : consumers) consumer.join();

    std::vector<int> all;
    for (const auto &part : received) all.insert(all.end(), part.begin(), part.end());
    std::sort(all.begin(), all.end());
    std::vector<int> expected(8'000);
    for (int i = 0; i < 8'000; ++i) expected[static_cast<std::size_t>(i)] = i;
    CHECK_EQ(all.size(), 8'000);
    CHECK(all == expected, "Some items were lost or delivered twice");
}
