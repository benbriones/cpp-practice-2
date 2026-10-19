// === Lesson: Constructors and invariants =====================================
//
// An invariant is a rule that holds for every object of a class at all times:
// "a percentage is between 0 and 100", "a color channel fits in a byte". The
// constructor establishes it (or throws), private data stops outside code from
// breaking it, and every member function can then rely on it without checking.
//
// A constructor should set its members in a member initializer list, which runs
// before the constructor's body:
//
//     class Rgb {
//     public:
//         Rgb(int r, int g, int b) : r_(r), g_(g), b_(b) {
//             if (!in_range(r) || !in_range(g) || !in_range(b)) {
//                 throw std::invalid_argument("channels must be 0-255");
//             }
//         }
//
//         // Builds a new color and leaves this one alone, so it can be const.
//         Rgb inverted() const { return Rgb(255 - r_, 255 - g_, 255 - b_); }
//
//         // Access is per class, not per object: other's private members are visible.
//         bool brighter_than(const Rgb& other) const {
//             return r_ + g_ + b_ > other.r_ + other.g_ + other.b_;
//         }
//
//         // static: belongs to the class, not to an object, so there's no `this`.
//         static Rgb gray(int level) { return Rgb(level, level, level); }
//
//     private:
//         static bool in_range(int v) { return v >= 0 && v <= 255; }
//
//         int r_;
//         int g_;
//         int b_;
//     };
//
//     Rgb teal(0, 128, 128);
//     Rgb mid = Rgb::gray(128);     // a static function is called on the class name
//     Rgb bad(300, 0, 0);           // throws std::invalid_argument
//
// The initializer list is the only way to set const members, reference members,
// and members whose type has no default constructor; by the time the body runs,
// they've already been initialized. Members are initialized in the order they're
// declared in the class, not the order you list them, and clang warns when the
// two differ.
//
// Static member functions work well as named constructors like Rgb::gray. When
// they build their result through a constructor, its checks run there too.
//
// Wrapping a value around a range is a job for %, but remember from module 01
// that % keeps the sign of its left operand: -1 % 60 is -1. And std::to_string
// never pads: std::to_string(7) is "7".
//
// Read more: https://www.learncpp.com/cpp-tutorial/constructor-member-initializer-lists/
//            https://www.learncpp.com/cpp-tutorial/static-member-functions/
//
// === Exercise: Time of day ===================================================
// A Time always holds a valid clock time, 00:00 to 23:59. The constructor enforces that
// rule (an invariant), so every other member function can rely on it.
//
// ./grade 05_classes/02_time_of_day

#include <stdexcept>
#include <string>

class Time {
public:
    // Throw std::invalid_argument unless 0 <= hours <= 23 and 0 <= minutes <= 59.
    Time(int hours, int minutes) {
        throw "TODO";
    }

    int hours() const {
        throw "TODO";
    }

    int minutes() const {
        throw "TODO";
    }

    // Time(1, 30).minutes_since_midnight() == 90
    int minutes_since_midnight() const {
        throw "TODO";
    }

    // A new Time `delta` minutes later (earlier if negative), wrapping around midnight.
    // Time(23, 30).add_minutes(45) is 00:15, Time(0, 10).add_minutes(-20) is 23:50.
    Time add_minutes(int delta) const {
        throw "TODO";
    }

    // "HH:MM" with leading zeros: "09:05".
    std::string to_string() const {
        throw "TODO";
    }

    // True if this time is earlier in the day than `other`.
    bool is_before(const Time& other) const {
        throw "TODO";
    }

    // The time `total` minutes after midnight, wrapped into a single day (negative values
    // count back from midnight): from_minutes(90) is 01:30, from_minutes(-1) is 23:59.
    static Time from_minutes(int total) {
        throw "TODO";
    }

private:
    // TODO: data members
};
