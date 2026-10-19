// Challenge: Blocking queue
// A thread-safe FIFO queue for handing work from producer threads to consumer
// threads, the classic building block of a thread pool.
//
// Guard a std::deque<T> with a std::mutex. A std::condition_variable lets pop()
// sleep until there's something to take: cv.wait(lock, [&] { return ...; })
// waits until the condition holds, and cv.notify_one()/notify_all() wake
// waiters after a change. T may be move-only (e.g. std::unique_ptr), so move
// values in and out.
//
// ./grade 17_concurrency/04_blocking_queue

#include <condition_variable>
#include <cstddef>
#include <deque>
#include <mutex>
#include <optional>
#include <stdexcept>

template <typename T>
class BlockingQueue {
public:
    // Add to the back and wake one waiting pop(). Throws std::logic_error if
    // the queue has been closed.
    void push(T value) {
        throw "TODO";
    }

    // Remove from the front, waiting while the queue is empty. Returns
    // std::nullopt once the queue is closed AND empty; items pushed before
    // close() are still handed out.
    std::optional<T> pop() {
        throw "TODO";
    }

    // Like pop(), but never waits: std::nullopt if the queue is empty right now.
    std::optional<T> try_pop() {
        throw "TODO";
    }

    // No more pushes. Wakes every waiting pop().
    void close() {
        throw "TODO";
    }

    std::size_t size() const {
        throw "TODO";
    }

    bool closed() const {
        throw "TODO";
    }

private:
    // TODO: a deque, a mutex, a condition variable, and a closed flag
};
