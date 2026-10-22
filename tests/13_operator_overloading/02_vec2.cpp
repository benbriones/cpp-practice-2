#include "grader.hpp"
#include "13_operator_overloading/02_vec2.cpp"

// Formats the fields directly, so most tests don't depend on your operator<<.
std::string str(const Vec2 &v) {
    return std::format("({}, {})", v.x, v.y);
}

TEST("+= adds to the left side") {
    Vec2 v{1, 2};
    v += Vec2{3, 4};
    CHECK_EQ(str(v), "(4, 6)");
}

TEST("-= subtracts from the left side") {
    Vec2 v{5, 5};
    v -= Vec2{1, 2};
    CHECK_EQ(str(v), "(4, 3)");
}

TEST("+= returns the vector itself, so calls chain") {
    Vec2 v{1, 1};
    Vec2 &result = (v += Vec2{1, 0}) += Vec2{0, 1};
    CHECK(&result == &v, "v += w should return a reference to v");
    CHECK_EQ(str(v), "(2, 2)");
}

TEST("+ and - leave their operands alone") {
    const Vec2 a{1, 2};
    const Vec2 b{3, 4};
    CHECK_EQ(str(a + b), "(4, 6)");
    CHECK_EQ(str(a - b), "(-2, -2)");
    CHECK_EQ(str(a), "(1, 2)");
    CHECK_EQ(str(b), "(3, 4)");
}

TEST("unary minus") {
    CHECK_EQ(str(-Vec2{1, -2}), "(-1, 2)");
}

TEST("scaling on either side") {
    const Vec2 v{1.5, -2};
    CHECK_EQ(str(v * 2), "(3, -4)");
    CHECK_EQ(str(2 * v), "(3, -4)");
    CHECK_EQ(str(0.5 * Vec2{4, 8}), "(2, 4)");
}

TEST("operator[]: reading") {
    const Vec2 v{3, 4};
    CHECK_EQ(v[0], 3.0);
    CHECK_EQ(v[1], 4.0);
}

TEST("operator[]: writing") {
    Vec2 v;
    v[0] = 5;
    v[1] = -1;
    CHECK_EQ(str(v), "(5, -1)");
}

TEST("operator[]: bad indexes throw") {
    Vec2 v{1, 2};
    const Vec2 c{1, 2};
    CHECK_THROWS(std::out_of_range, v[2]);
    CHECK_THROWS(std::out_of_range, v[-1]);
    CHECK_THROWS(std::out_of_range, c[2]);
}

TEST("length") {
    CHECK_NEAR(Vec2{3, 4}.length(), 5.0);
    CHECK_NEAR(Vec2{0, 0}.length(), 0.0);
    CHECK_NEAR(Vec2{-1, 1}.length(), std::sqrt(2.0));
}

TEST("operator<<") {
    std::ostringstream out;
    out << Vec2{1, 2.5} << " " << Vec2{-3, 0};
    CHECK_EQ(out.str(), "(1, 2.5) (-3, 0)");
}
