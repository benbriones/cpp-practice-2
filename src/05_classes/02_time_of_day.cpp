// Exercise: Time of day
// A Time always holds a valid clock time, 00:00 to 23:59. The constructor enforces that
// rule (an invariant), so every other member function can rely on it.
//
// Initialize data members in the constructor's member initializer list:
//     Time(int hours, int minutes) : hours_(hours), minutes_(minutes) { /* checks */ }
// A `static` member function belongs to the class, not to an object: Time::from_minutes(90).
//
// Grade: grade 05_classes/02_time_of_day

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
