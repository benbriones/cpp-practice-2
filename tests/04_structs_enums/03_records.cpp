#include "grader.hpp"
#include "04_structs_enums/03_records.cpp"

std::vector<Employee> sample_staff() {
    return {
        {"Ada", "Engineering", 120000},
        {"Grace", "Engineering", 135000},
        {"Linus", "Operations", 90000},
        {"Barbara", "Research", 135000},
        {"Ken", "Operations", 85000},
    };
}

TEST("total_payroll") {
    CHECK_NEAR(total_payroll(sample_staff()), 565000.0);
    CHECK_NEAR(total_payroll({}), 0.0);
}

TEST("names_in: keeps the original order") {
    const auto staff = sample_staff();
    CHECK_EQ(names_in(staff, "Engineering"), {"Ada", "Grace"});
    CHECK_EQ(names_in(staff, "Operations"), {"Linus", "Ken"});
    CHECK_EQ(names_in(staff, "Research"), {"Barbara"});
}

TEST("names_in: unknown department") {
    CHECK_EQ(names_in(sample_staff(), "Marketing"), {});
}

TEST("highest_paid: the first of two equal salaries") {
    const auto staff = sample_staff();
    const Employee *best = highest_paid(staff);
    CHECK(best != nullptr, "highest_paid returned nullptr for a non-empty list");
    CHECK_EQ(best->name, "Grace");
}

TEST("highest_paid: points into the vector") {
    const auto staff = sample_staff();
    CHECK(highest_paid(staff) == &staff[1], "should point at staff[1] itself, not at a copy");
}

TEST("highest_paid: empty list") {
    CHECK_EQ(highest_paid({}), nullptr);
}

TEST("give_raise: only the chosen department") {
    auto staff = sample_staff();
    give_raise(staff, "Engineering", 10);
    CHECK_NEAR(staff[0].salary, 132000.0);
    CHECK_NEAR(staff[1].salary, 148500.0);
    CHECK_NEAR(staff[2].salary, 90000.0);
    CHECK_NEAR(staff[3].salary, 135000.0);
}

TEST("give_raise: unknown department changes nothing") {
    auto staff = sample_staff();
    give_raise(staff, "Marketing", 50);
    const auto original = sample_staff();
    for (std::size_t i = 0; i < staff.size(); ++i) {
        CHECK_NEAR(staff[i].salary, original[i].salary);
    }
}

TEST("salary_range") {
    auto [low, high] = salary_range(sample_staff());
    CHECK_NEAR(low, 85000.0);
    CHECK_NEAR(high, 135000.0);
}

TEST("salary_range: a single employee") {
    auto [low, high] = salary_range({{"Solo", "Research", 70000}});
    CHECK_NEAR(low, 70000.0);
    CHECK_NEAR(high, 70000.0);
}
