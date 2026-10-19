// Exercise: 2D vectors
// Give Vec2 the operators a maths vector should have.
//
// Compound assignment (+=) is a member that changes *this and returns *this by
// reference. Then + is easy as a free function: copy the left side, += the right.
// 2.0 * v needs a free function, because the left operand isn't a Vec2.
//
// ./grade 13_operator_overloading/02_vec2

#include <cmath>
#include <ostream>
#include <stdexcept>

struct Vec2 {
    double x = 0;
    double y = 0;

    // The compiler writes == for you, comparing member by member.
    bool operator==(const Vec2&) const = default;

    Vec2& operator+=(const Vec2& other) {
        throw "TODO";
    }

    Vec2& operator-=(const Vec2& other) {
        throw "TODO";
    }

    // v[0] is x and v[1] is y; any other index throws std::out_of_range.
    // This version returns a reference, so v[0] = 5 works.
    double& operator[](int index) {
        throw "TODO";
    }

    // The read-only version, used when the Vec2 is const.
    double operator[](int index) const {
        throw "TODO";
    }

    double length() const {
        throw "TODO";
    }
};

Vec2 operator+(Vec2 a, const Vec2& b) {
    throw "TODO";
}

Vec2 operator-(Vec2 a, const Vec2& b) {
    throw "TODO";
}

// Unary minus: -Vec2{1, -2} is {-1, 2}.
Vec2 operator-(const Vec2& v) {
    throw "TODO";
}

Vec2 operator*(const Vec2& v, double factor) {
    throw "TODO";
}

Vec2 operator*(double factor, const Vec2& v) {
    throw "TODO";
}

// Prints "(1, 2.5)": both numbers with plain <<, a comma and a space between.
std::ostream& operator<<(std::ostream& out, const Vec2& v) {
    throw "TODO";
}
