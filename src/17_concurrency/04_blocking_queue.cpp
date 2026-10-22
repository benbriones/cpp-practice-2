// === Lesson: Condition variables =============================================
//
// A mutex keeps threads from colliding; a std::condition_variable lets a thread
// sleep until another thread changes something it's waiting for:
//
//     std::mutex m;
//     std::condition_variable cv;
//     bool ready = false;                     // the condition, guarded by m
//
//     // Waiting thread:
//     std::unique_lock lock(m);
//     cv.wait(lock, [&] { return ready; });   // sleeps until ready is true
//     // here m is locked again, and ready is true
//
//     // Signalling thread:
//     {
//         std::lock_guard lock(m);
//         ready = true;                       // change the state under the lock...
//     }
//     cv.notify_one();                        // ...then wake a waiter
//
// cv.wait(lock, predicate) is a loop: while the predicate is false, it unlocks
// the mutex, sleeps, and locks it again when woken. That's why it takes a
// std::unique_lock (which can unlock and relock) rather than a lock_guard. And
// it's why you always pass a predicate: a thread can wake without being
// notified (a "spurious wakeup"), or wake to find another thread got there
// first.
//
// Notifications aren't stored: notifying when nobody waits does nothing, so a
// waiter checks the state rather than waiting for a signal. For the same
// reason, change the state while holding the mutex. Set ready without the
// lock, and a waiter could see false, fall asleep just after the notification,
// and never wake.
//
// notify_one() wakes one waiting thread; notify_all() wakes them all, which is
// what you want when every waiter cares about the change (a shutdown, say).
//
// front() on a container returns a reference to the element, so move from it
// before pop_front() destroys it.
//
// Read more: https://en.cppreference.com/w/cpp/thread/condition_variable
//
// === Challenge: Blocking queue ===============================================
// A thread-safe FIFO queue for handing work from producer threads to consumer
// threads, the classic building block of a thread pool.
//
// Keep the items in a std::deque<T> guarded by a std::mutex, and use a
// std::condition_variable so pop() can sleep until there's something to take.
// T may be move-only (e.g. std::unique_ptr), so move values in and out.
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
    // Add value to the back of the queue and wake one waiting pop().
    // Throw std::logic_error if the queue has been closed.
    //
    // Example:
    //   queue.push(1);
    //   queue.push(2);
    //   // size() is 2, and the next pop() gives 1.
    //   queue.close();
    //   queue.push(3);   // throws std::logic_error
    //
    // T may be move-only, so move value into the deque rather than copying it.
    void push(T value) {
        throw "TODO";
    }

    // Remove and return the front item, waiting while the queue is empty.
    // Return std::nullopt once the queue is both closed and empty.
    // Items pushed before close() are still handed out.
    //
    // Example:
    //   queue.push(7);
    //   queue.push(8);
    //   queue.close();
    //   queue.pop() gives 7, then 8, then std::nullopt
    //
    // On an empty, open queue, pop() sleeps until another thread pushes or closes.
    std::optional<T> pop() {
        throw "TODO";
    }

    // Remove and return the front item like pop(), but never wait.
    // Return std::nullopt if the queue is empty right now.
    //
    // Example:
    //   queue.push(1);
    //   queue.try_pop() gives 1
    //   queue.try_pop() gives std::nullopt straight away
    std::optional<T> try_pop() {
        throw "TODO";
    }

    // Close the queue: no more pushes are allowed after this.
    // Wake every waiting pop().
    //
    // Example:
    //   another thread is waiting in queue.pop() on an empty queue
    //   queue.close();
    //   // that pop() wakes up and returns std::nullopt.
    //
    // Items already in the queue stay, and pop() still hands them out.
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
