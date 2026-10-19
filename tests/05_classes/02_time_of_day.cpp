#include "grader.hpp"
#include "05_classes/02_time_of_day.cpp"

// {hours, minutes}, so failures print as {0, 15}.
static std::pair<int, int> hm(const Time& t) { return {t.hours(), t.minutes()}; }

TEST("Time: stores hours and minutes") {
    Time t(9, 5);
    CHECK_EQ(t.hours(), 9);
    CHECK_EQ(t.minutes(), 5);
}

TEST("Time: accepts the first and last minute of the day") {
    CHECK_EQ(hm(Time(0, 0)), {0, 0});
    CHECK_EQ(hm(Time(23, 59)), {23, 59});
}

TEST("Time: rejects out-of-range values") {
    CHECK_THROWS(std::invalid_argument, Time(24, 0));
    CHECK_THROWS(std::invalid_argument, Time(-1, 30));
    CHECK_THROWS(std::invalid_argument, Time(12, 60));
    CHECK_THROWS(std::invalid_argument, Time(12, -1));
}

TEST("minutes_since_midnight") {
    CHECK_EQ(Time(0, 0).minutes_since_midnight(), 0);
    CHECK_EQ(Time(1, 30).minutes_since_midnight(), 90);
    CHECK_EQ(Time(23, 59).minutes_since_midnight(), 1439);
}

TEST("to_string: pads with leading zeros") {
    CHECK_EQ(Time(9, 5).to_string(), "09:05");
    CHECK_EQ(Time(0, 0).to_string(), "00:00");
    CHECK_EQ(Time(12, 30).to_string(), "12:30");
    CHECK_EQ(Time(23, 59).to_string(), "23:59");
}

TEST("add_minutes: within the same day") {
    CHECK_EQ(hm(Time(9, 0).add_minutes(90)), {10, 30});
    CHECK_EQ(hm(Time(9, 0).add_minutes(0)), {9, 0});
}

TEST("add_minutes: wraps past midnight") {
    CHECK_EQ(hm(Time(23, 30).add_minutes(45)), {0, 15});
    CHECK_EQ(hm(Time(10, 0).add_minutes(2 * 1440 + 1)), {10, 1});
}

TEST("add_minutes: negative values go back in time") {
    CHECK_EQ(hm(Time(10, 0).add_minutes(-30)), {9, 30});
    CHECK_EQ(hm(Time(0, 10).add_minutes(-20)), {23, 50});
    CHECK_EQ(hm(Time(6, 0).add_minutes(-3 * 1440)), {6, 0});
}

TEST("add_minutes: leaves the original unchanged") {
    const Time start(8, 0);
    Time later = start.add_minutes(30);
    CHECK_EQ(hm(start), {8, 0});
    CHECK_EQ(hm(later), {8, 30});
}

TEST("from_minutes: within one day") {
    CHECK_EQ(hm(Time::from_minutes(0)), {0, 0});
    CHECK_EQ(hm(Time::from_minutes(90)), {1, 30});
    CHECK_EQ(hm(Time::from_minutes(1439)), {23, 59});
}

TEST("from_minutes: wraps larger and negative values") {
    CHECK_EQ(hm(Time::from_minutes(1440)), {0, 0});
    CHECK_EQ(hm(Time::from_minutes(3000)), {2, 0});
    CHECK_EQ(hm(Time::from_minutes(-1)), {23, 59});
    CHECK_EQ(hm(Time::from_minutes(-1500)), {23, 0});
}

TEST("is_before") {
    CHECK_EQ(Time(9, 0).is_before(Time(10, 0)), true);
    CHECK_EQ(Time(9, 59).is_before(Time(10, 0)), true);
    CHECK_EQ(Time(10, 0).is_before(Time(9, 0)), false);
    CHECK_EQ(Time(10, 0).is_before(Time(10, 0)), false);
}
