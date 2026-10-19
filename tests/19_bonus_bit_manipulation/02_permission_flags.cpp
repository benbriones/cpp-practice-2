#include "grader.hpp"
#include "19_bonus_bit_manipulation/02_permission_flags.cpp"

using P = Permission;

TEST("has: single flags") {
    CHECK_EQ(has(P::Read | P::Write, P::Read), true);
    CHECK_EQ(has(P::Read | P::Write, P::Write), true);
    CHECK_EQ(has(P::Read | P::Write, P::Execute), false);
    CHECK_EQ(has(P::None, P::Read), false);
}

TEST("has: every flag in a combination must be present") {
    CHECK_EQ(has(P::Read | P::Write | P::Execute, P::Read | P::Execute), true);
    CHECK_EQ(has(P::Read, P::Read | P::Write), false);
}

TEST("has: None is always present") {
    CHECK_EQ(has(P::None, P::None), true);
    CHECK_EQ(has(P::Write, P::None), true);
}

TEST("without") {
    CHECK_EQ(without(P::Read | P::Write, P::Write), P::Read);
    CHECK_EQ(without(P::Read | P::Write | P::Execute, P::Read | P::Execute), P::Write);
    CHECK_EQ(without(P::Read, P::Write), P::Read);
    CHECK_EQ(without(P::Execute, P::Execute), P::None);
}

TEST("to_string") {
    CHECK_EQ(to_string(P::Read | P::Write | P::Execute), "rwx");
    CHECK_EQ(to_string(P::Read | P::Execute), "r-x");
    CHECK_EQ(to_string(P::Write), "-w-");
    CHECK_EQ(to_string(P::None), "---");
}

TEST("parse_permissions") {
    CHECK_EQ(parse_permissions("rwx"), P::Read | P::Write | P::Execute);
    CHECK_EQ(parse_permissions("r--"), P::Read);
    CHECK_EQ(parse_permissions("-wx"), P::Write | P::Execute);
    CHECK_EQ(parse_permissions("---"), P::None);
}

TEST("parse_permissions: round-trips every combination") {
    for (int bits = 0; bits < 8; ++bits) {
        Permission p = static_cast<Permission>(bits);
        CHECK_EQ(parse_permissions(to_string(p)), p);
    }
}

TEST("parse_permissions: rejects bad text") {
    CHECK_THROWS(std::invalid_argument, parse_permissions(""));
    CHECK_THROWS(std::invalid_argument, parse_permissions("rw"));
    CHECK_THROWS(std::invalid_argument, parse_permissions("rwxr"));
    CHECK_THROWS(std::invalid_argument, parse_permissions("wrx"));
    CHECK_THROWS(std::invalid_argument, parse_permissions("RWX"));
    CHECK_THROWS(std::invalid_argument, parse_permissions("r?x"));
}
