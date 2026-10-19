// Exercise: Your first class
// Finish Counter: a tally that counts up by a fixed step and never drops below zero.
//
// Data members go under private:, and only the class's own functions can touch them.
// A member function marked `const` promises not to change the object, so it can be
// called on a const Counter&. To reject bad arguments:
//     throw std::invalid_argument("step must be positive");   // from <stdexcept>
// (catching exceptions has its own module later).
//
// Grade: grade 05_classes/01_counter

#include <stdexcept>

class Counter {
public:
    // Start at `start` and count in steps of `step`. Throw std::invalid_argument if
    // start < 0 or step <= 0. `explicit` stops a plain int silently becoming a Counter.
    explicit Counter(int start = 0, int step = 1) {
        throw "TODO";
    }

    // Add one step.
    void increment() {
        throw "TODO";
    }

    // Subtract one step, stopping at 0: a Counter at 2 with step 5 decrements to 0.
    void decrement() {
        throw "TODO";
    }

    // Go back to the starting value.
    void reset() {
        throw "TODO";
    }

    int value() const {
        throw "TODO";
    }

private:
    // TODO: add the data members you need, e.g.  int value_ = 0;
};
