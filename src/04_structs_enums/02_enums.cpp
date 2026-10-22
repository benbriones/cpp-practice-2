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
    bool operator==(const Position &) const = default;
};

// Prints a Position as (x, y), so test failures read nicely.
inline std::ostream &operator<<(std::ostream &out, Position p) {
    return out << "(" << p.x << ", " << p.y << ")";
}

// Return the direction a quarter turn clockwise from d.
// North → East → South → West → North.
//
// Example:
//   turn_right(Direction::North) is Direction::East
//   turn_right(Direction::West) is Direction::North
Direction turn_right(Direction d) {
    throw "TODO";
}

// Return the direction a quarter turn counter-clockwise from d.
// North → West → South → East → North.
//
// Example:
//   turn_left(Direction::North) is Direction::West
//   turn_left(Direction::East) is Direction::North
Direction turn_left(Direction d) {
    throw "TODO";
}

Direction opposite(Direction d) {
    throw "TODO";
}

// Return d's name as text: "North", "East", "South" or "West".
//
// Example:
//   to_string(Direction::South) is "South"
//
// An enum class can't print itself, so this gives each value a readable name.
std::string to_string(Direction d) {
    throw "TODO";
}

// Return the position reached by moving `steps` squares from `from` in direction d.
// North is +y, East is +x, South is -y, West is -x.
// Zero steps leaves you where you started.
//
// Example:
//   walk({0, 0}, Direction::North, 3) is {0, 3}
//   walk({0, 0}, Direction::West, 4) is {-4, 0}
//   walk({5, -2}, Direction::North, 2) is {5, 0}
//
// from is a copy, so the caller's Position doesn't change.
Position walk(Position from, Direction d, int steps) {
    throw "TODO";
}

// Return where you end up after following commands, one character at a time.
// Start at (0, 0) facing North.
// 'F' moves forward one square. 'L' and 'R' turn a quarter turn left or right.
// Ignore any other character.
//
// Example:
//   follow("FFRFF") == Position{2, 2}
//   // FF reaches (0, 2), R faces East, then FF reaches (2, 2)
//   follow("LF") == Position{-1, 0}
//   follow("F F x F!") == Position{0, 3}   // spaces, x and ! are ignored
Position follow(std::string_view commands) {
    throw "TODO";
}
