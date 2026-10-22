// === Lesson: Member operators, [] and the usual idioms =======================
//
// Compound assignment (+=, -=, *=) changes the object it's called on, so it's a
// member. It returns *this by reference, like the built-in += does, so that
// (a += b) += c keeps working on a:
//
//     struct Duration {
//         int seconds = 0;
//
//         Duration &operator+=(const Duration &other) {
//             seconds += other.seconds;
//             return *this;   // the object itself, not a copy
//         }
//     };
//
// Then write + as a free function in terms of +=. Taking the left side by value
// gives you a copy to change and return, and the caller's object is untouched:
//
//     Duration operator+(Duration a, const Duration &b) {
//         a += b;
//         return a;
//     }
//
// The parameter count picks the operator: operator-(x) with one parameter is
// unary minus (-d), and operator-(x, y) with two is subtraction (a - b). For
// 2.0 * v the left operand is a double, so only a free function
// operator*(double, const Vec2 &) can handle it; v * 2.0 is a separate overload.
//
// operator[] must be a member and, in C++20, takes exactly one argument. Write
// it twice: a non-const version returning a reference, so callers can assign
// through it, and a const version for const objects:
//
//     class Playlist {
//     public:
//         std::string &operator[](std::size_t i) { return songs_.at(i); }
//         const std::string &operator[](std::size_t i) const { return songs_.at(i); }
//     private:
//         std::vector<std::string> songs_;
//     };
//
//     playlist[0] = "Intro";   // non-const version: assigns into the vector
//     const Playlist &view = playlist;
//     view[0];                 // const version; assigning through it won't compile
//
// `bool operator==(const T &) const = default;` asks the compiler to write ==
// for you, comparing members in declaration order.
//
// Plain << prints a double with up to 6 significant digits and no trailing
// zeros: 1.0 prints as 1, and 2.5 as 2.5.
//
// Read more: https://en.cppreference.com/w/cpp/language/operators
//            https://www.learncpp.com/cpp-tutorial/overloading-the-subscript-operator/
//
// === Exercise: 2D vectors ====================================================
// Give Vec2 the operators a maths vector should have.
//
// ./grade 13_operator_overloading/02_vec2

#include <cmath>
#include <ostream>
#include <stdexcept>

struct Vec2 {
    double x = 0;
    double y = 0;

    // The compiler writes == for you, comparing member by member: x, then y.
    //
    // Example:
    //   Vec2{1, 2} == Vec2{1, 2} is true, Vec2{1, 2} == Vec2{2, 1} is false
    bool operator==(const Vec2 &) const = default;

    Vec2 &operator+=(const Vec2 &other) {
        throw "TODO";
    }

    Vec2 &operator-=(const Vec2 &other) {
        throw "TODO";
    }

    // Return a reference to one coordinate: v[0] is x and v[1] is y.
    // Any other index throws std::out_of_range.
    //
    // Example:
    //   Vec2 v;
    //   v[0] = 5;
    //   v[1] = -1;
    //   // v is now {5, -1}; v[2] and v[-1] throw std::out_of_range.
    //
    // This version returns a reference, so v[0] = 5 works.
    double &operator[](int index) {
        throw "TODO";
    }

    // The read-only version, used when the Vec2 is const.
    // Return a copy of the coordinate, with the same indexes: 0 is x, 1 is y.
    // Any other index throws std::out_of_range here too.
    //
    // Example:
    //   const Vec2 c{3, 4};
    //   c[0] is 3.0, c[1] is 4.0, c[2] throws std::out_of_range
    double operator[](int index) const {
        throw "TODO";
    }

    double length() const {
        throw "TODO";
    }
};

Vec2 operator+(Vec2 a, const Vec2 &b) {
    throw "TODO";
}

Vec2 operator-(Vec2 a, const Vec2 &b) {
    throw "TODO";
}

// Unary minus: return v with both coordinates negated.
//
// Example:
//   -Vec2{1, -2} is {-1, 2}
Vec2 operator-(const Vec2 &v) {
    throw "TODO";
}

Vec2 operator*(const Vec2 &v, double factor) {
    throw "TODO";
}

Vec2 operator*(double factor, const Vec2 &v) {
    throw "TODO";
}

// Print v as "(x, y)": both numbers with plain <<, a comma and a space between.
// Return the stream so calls chain.
//
// Example:
//   out << Vec2{1, 2.5} << " " << Vec2{-3, 0};
//   // prints "(1, 2.5) (-3, 0)"
std::ostream &operator<<(std::ostream &out, const Vec2 &v) {
    throw "TODO";
}
