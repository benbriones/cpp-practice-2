// === Lesson: Mutexes =========================================================
//
// ++count looks like one step but is three: read the value, add one, write it
// back. Two threads can both read the old value and both write old + 1, losing
// an increment. Unsynchronized access like that is a data race, which is
// undefined behavior.
//
// A std::mutex lets one thread at a time through. Don't call lock() and
// unlock() yourself (a return or an exception in between leaves it locked);
// use an RAII guard, which unlocks in its destructor:
//
//     class Guestbook {
//     public:
//         void sign(const std::string &name) {
//             std::lock_guard lock(mutex_);   // locked from here...
//             names_.push_back(name);
//         }                                   // ...to the end of the scope
//
//         std::size_t signatures() const {
//             std::lock_guard lock(mutex_);   // reads need the lock too
//             return names_.size();
//         }
//
//     private:
//         mutable std::mutex mutex_;          // mutable: lockable in const functions
//         std::vector<std::string> names_;    // guarded by mutex_
//     };
//
// Every access to guarded data, reads included, must hold the same mutex. Keep
// locked regions short.
//
// Check and act under one lock. Checking "is there stock left?" and then
// locking to take an item is still broken: another thread can take the last
// item between your check and your lock.
//
// Deadlock: thread 1 holds mutex a and waits for b, while thread 2 holds b and
// waits for a. Both wait forever. std::scoped_lock locks several mutexes at
// once, all or nothing, using a deadlock-avoidance algorithm:
//
//     std::scoped_lock lock(a, b);   // both locked until the end of the scope
//
// Locking a std::mutex the same thread already holds is undefined behavior; in
// practice the thread waits for itself forever.
//
// Read more: https://en.cppreference.com/w/cpp/thread/mutex
//            https://en.cppreference.com/w/cpp/thread/scoped_lock
//
// === Exercise: Mutexes =======================================================
// Make shared data safe to use from many threads at once.
//
// ./grade 17_concurrency/02_mutex

#include <mutex>

// A counter that many threads can update at the same time.
// It starts at 0. increment() adds 1, add(amount) adds amount, value() reads it.
//
// Example:
//   8 threads each call counter.increment() 20,000 times
//   after joining them all, counter.value() is 160,000
//
// No update may be lost, even when two threads change the count at once.
class SafeCounter {
public:
    void increment() {
        throw "TODO";
    }

    void add(int amount) {
        throw "TODO";
    }

    int value() const {
        throw "TODO";
    }

private:
    // TODO: a count and a mutex that guards it
};

// Given: an account guarded by its own mutex.
struct Account {
    long long balance = 0;
    std::mutex mutex{};
};

// Move `amount` from `from` to `to` and return true.
// Return false and change nothing when amount <= 0, `from` lacks the funds,
// or both arguments are the same account (locking one mutex twice would deadlock).
// Two threads may transfer in opposite directions at the same moment, so lock
// both accounts together.
//
// Example:
//   Account alice{100};
//   Account bob{20};
//   transfer(alice, bob, 30) returns true: alice now has 70, bob has 50
//   transfer(alice, bob, 71) returns false: alice has only 70
//   transfer(alice, bob, 0) and transfer(alice, alice, 10) return false
//
// Moving the whole balance is allowed: `from` may end at exactly 0.
bool transfer(Account &from, Account &to, long long amount) {
    throw "TODO";
}

// Return account's balance.
// Read it safely: other threads may be transferring at the same moment.
//
// Example:
//   Account alice{42};
//   read_balance(alice) is 42
//
// Reads need the lock too, or they race with a transfer's writes.
long long read_balance(Account &account) {
    throw "TODO";
}
