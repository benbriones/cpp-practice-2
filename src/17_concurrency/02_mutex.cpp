// Exercise: Mutexes
// Make shared data safe to use from many threads at once.
//
// std::mutex guards data; std::lock_guard lock(m); locks it until the end of
// the scope. A const member function that locks needs a `mutable std::mutex`.
// std::scoped_lock lock(a, b); locks two mutexes together without deadlocking.
//
// Grade: grade 17_concurrency/02_mutex

#include <mutex>

// A counter that many threads can update at the same time.
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

// Move `amount` from one account to the other and return true, or return false
// and change nothing when amount <= 0, `from` lacks the funds, or both
// arguments are the same account (locking one mutex twice would deadlock).
// Two threads may transfer in opposite directions at the same moment, so lock
// both accounts together.
bool transfer(Account& from, Account& to, long long amount) {
    throw "TODO";
}

// Read an account's balance safely while other threads may be transferring.
long long read_balance(Account& account) {
    throw "TODO";
}
