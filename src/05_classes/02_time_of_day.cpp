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
//         bool brighter_than(const Rgb &other) const {
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
    // Create the time hours:minutes.
    // Throw std::invalid_argument unless 0 <= hours <= 23 and 0 <= minutes <= 59.
    //
    // Example:
    //   Time t(9, 5);    // 09:05
    //   Time(23, 59);    // fine: the last minute of the day
    //   Time(24, 0);     // throws std::invalid_argument
    //   Time(12, 60);    // throws std::invalid_argument
    Time(int hours, int minutes) {
        throw "TODO";
    }

    int hours() const {
        throw "TODO";
    }

    int minutes() const {
        throw "TODO";
    }

    // Return how many minutes have passed since midnight (00:00).
    //
    // Example:
    //   Time(0, 0).minutes_since_midnight() is 0
    //   Time(1, 30).minutes_since_midnight() is 90
    //   Time(23, 59).minutes_since_midnight() is 1439
    int minutes_since_midnight() const {
        throw "TODO";
    }

    // Return a new Time `delta` minutes later (earlier if delta is negative).
    // The result wraps around midnight, so it is always a valid time.
    // delta can be more than a whole day in either direction.
    //
    // Example:
    //   Time(9, 0).add_minutes(90) is 10:30
    //   Time(23, 30).add_minutes(45) is 00:15
    //   Time(0, 10).add_minutes(-20) is 23:50
    //
    // The function is const: it builds a new Time and leaves the original unchanged.
    Time add_minutes(int delta) const {
        throw "TODO";
    }

    // Return the time as "HH:MM", with leading zeros.
    // Hours and minutes are always two digits each.
    //
    // Example:
    //   Time(9, 5).to_string() is "09:05"
    //   Time(0, 0).to_string() is "00:00"
    //   Time(23, 59).to_string() is "23:59"
    std::string to_string() const {
        throw "TODO";
    }

    // Return true if this time is earlier in the day than `other`.
    // Two equal times are not before each other, so that returns false.
    //
    // Example:
    //   Time(9, 59).is_before(Time(10, 0)) is true
    //   Time(10, 0).is_before(Time(9, 0)) is false
    //   Time(10, 0).is_before(Time(10, 0)) is false
    bool is_before(const Time &other) const {
        throw "TODO";
    }

    // Return the time `total` minutes after midnight, wrapped into a single day.
    // Negative values count back from midnight.
    // Values of a whole day or more wrap around too.
    //
    // Example:
    //   Time::from_minutes(90) is 01:30
    //   Time::from_minutes(1440) is 00:00
    //   Time::from_minutes(-1) is 23:59
    //
    // It's static, so it's called on the class name: Time::from_minutes(90).
    static Time from_minutes(int total) {
        throw "TODO";
    }

private:
    // TODO: data members
};
