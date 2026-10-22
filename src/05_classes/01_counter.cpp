// === Lesson: Classes =========================================================
//
// A class bundles data with the functions that work on it. In C++, struct and
// class are the same thing except for one default: struct members are public
// unless you say otherwise, class members are private. By convention, use a
// struct for plain data and a class when the data has rules to protect.
//
//     class Rectangle {
//     public:
//         // A constructor: named after the class, with no return type.
//         Rectangle(double width, double height) {
//             if (width <= 0 || height <= 0) {
//                 throw std::invalid_argument("sides must be positive");
//             }
//             width_ = width;
//             height_ = height;
//         }
//
//         double area() const { return width_ * height_; }
//         void scale(double factor) { width_ *= factor; height_ *= factor; }
//
//     private:
//         double width_;    // the trailing _ marks a data member
//         double height_;
//     };
//
//     Rectangle r(2, 3);    // no `new`: r is a value, like an int
//     r.scale(2);           // r.area() is now 24
//     Rectangle copy = r;   // a separate object; in JS both names would share one
//
// Inside a member function, members are in scope by name (width_ is short for
// this->width_). Only the class's own functions can touch private members, so a
// rule the constructor checks stays true for the object's whole life. A
// constructor that throws (std::invalid_argument is in <stdexcept>) creates no
// object at all. A data member can have a default:  int hits_ = 0;
//
// const member functions: area() const promises not to change the object. Only
// const member functions can be called on a const object or through a const
// reference, so mark every member function that only reads:
//
//     void report(const Rectangle& r) {
//         r.area();         // fine
//         r.scale(2);       // compile error: scale() isn't const
//     }
//
// Default arguments let one constructor serve several call forms. A constructor
// that can be called with one argument also acts as a silent conversion, unless
// it's marked explicit:
//
//     class Percent {
//     public:
//         explicit Percent(int value = 0) { ... }
//     };
//     void set_volume(Percent volume);
//     set_volume(Percent(40));   // fine
//     set_volume(40);            // compile error, thanks to explicit
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-classes/
//            https://www.learncpp.com/cpp-tutorial/const-class-objects-and-const-member-functions/
//
// === Exercise: Your first class ==============================================
// Finish Counter: a tally that counts up by a fixed step and never drops below zero.
//
// ./grade 05_classes/01_counter

#include <stdexcept>

class Counter {
public:
    // Create a Counter that starts at `start` and counts in steps of `step`.
    // Throw std::invalid_argument if start < 0 or step <= 0.
    //
    // Example:
    //   Counter a;          // starts at 0, counts in steps of 1
    //   Counter b(10, 5);   // starts at 10, counts in steps of 5
    //   Counter(3, -1);     // throws std::invalid_argument
    //
    // `explicit` stops a plain int silently becoming a Counter.
    explicit Counter(int start = 0, int step = 1) {
        throw "TODO";
    }

    // Add one step to the value.
    //
    // Example:
    //   Counter c(10, 5);
    //   c.increment();   // c.value() is 15
    //   c.increment();   // c.value() is 20
    void increment() {
        throw "TODO";
    }

    // Subtract one step from the value, stopping at 0.
    // The value never goes below 0: a Counter at 2 with step 5 decrements to 0.
    //
    // Example:
    //   Counter c(4, 3);
    //   c.decrement();   // c.value() is 1
    //   c.decrement();   // c.value() is 0, not -2
    //   c.decrement();   // c.value() stays 0
    void decrement() {
        throw "TODO";
    }

    // Set the value back to the starting value.
    //
    // Example:
    //   Counter c(2, 2);
    //   c.increment();
    //   c.increment();   // c.value() is 6
    //   c.reset();       // c.value() is 2 again
    void reset() {
        throw "TODO";
    }

    int value() const {
        throw "TODO";
    }

private:
    // TODO: add the data members you need, e.g.  int value_ = 0;
};
