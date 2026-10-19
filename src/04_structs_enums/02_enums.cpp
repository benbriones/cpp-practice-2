// === Lesson: enum class ======================================================
//
// An enumeration is a type whose values are a fixed list of names. Use the
// scoped kind, enum class:
//
//     enum class Suit { Clubs, Diamonds, Hearts, Spades };
//
//     Suit trump = Suit::Hearts;           // names are scoped: Suit::Hearts
//     if (trump == Suit::Hearts) { ... }
//
// Each name is an integer underneath, counting up from 0 (Clubs is 0, Spades is
// 3), but an enum class never converts to or from int on its own. That catches
// mistakes like comparing a Suit with a number. When you do want the number,
// ask for it with static_cast:
//
//     int n = static_cast<int>(Suit::Hearts);    // 2
//     Suit s = static_cast<Suit>(1);             // Suit::Diamonds
//
// The older plain `enum` (no class) spills its names into the surrounding scope
// and converts to int silently. You'll meet it in older code; prefer enum class.
//
// A switch is the natural way to act on each value. Every case needs a return
// or a break, or it falls through into the next one. Inside a switch, C++20's
// `using enum` saves repeating the type name:
//
//     bool is_red(Suit s) {
//         switch (s) {
//             using enum Suit;
//             case Diamonds:
//             case Hearts:              // two labels can share one body
//                 return true;
//             case Clubs:
//             case Spades:
//                 return false;
//         }
//     }
//
// Leave out a default: label and the compiler warns when a case is missing,
// including one you add to the enum later. (clang accepts is_red as it is. GCC
// also wants a return after the switch, since static_cast can produce a value
// that has no name.)
//
// std::cout << trump doesn't compile: an enum class has no built-in printing
// and no way to get a value's name as text.
//
// Read more: https://www.learncpp.com/cpp-tutorial/scoped-enumerations-enum-classes/
//            https://www.learncpp.com/cpp-tutorial/switch-statement-basics/
//
// === Exercise: enum class ====================================================
// Implement the six functions below.
//
// Failure messages print enum values as numbers: Direction(0) is North,
// (1) East, (2) South, (3) West.
//
// ./grade 04_structs_enums/02_enums

#include <ostream>
#include <string>
#include <string_view>

enum class Direction { North, East, South, West };

struct Position {
    int x{};
    int y{};
    // Lets you compare positions with ==. Operator overloading comes in module 13.
    bool operator==(const Position&) const = default;
};

// Prints a Position as (x, y), so test failures read nicely.
inline std::ostream& operator<<(std::ostream& out, Position p) {
    return out << "(" << p.x << ", " << p.y << ")";
}

// A quarter turn clockwise: North → East → South → West → North.
Direction turn_right(Direction d) {
    throw "TODO";
}

// A quarter turn counter-clockwise.
Direction turn_left(Direction d) {
    throw "TODO";
}

Direction opposite(Direction d) {
    throw "TODO";
}

// "North", "East", "South" or "West".
std::string to_string(Direction d) {
    throw "TODO";
}

// Move `steps` squares from `from`. North is +y, East is +x, South is -y, West is -x.
Position walk(Position from, Direction d, int steps) {
    throw "TODO";
}

// Start at (0, 0) facing North and follow the commands: 'F' moves forward one
// square, 'L' and 'R' turn. Ignore any other character.
// follow("FFRFF") == Position{2, 2}
Position follow(std::string_view commands) {
    throw "TODO";
}
