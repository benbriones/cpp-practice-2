// Exercise: enum class
// An enum class is a type with a fixed set of named values. Its values are
// scoped (Direction::North) and don't silently convert to int. A switch over
// an enum class should handle every value; the compiler warns if you miss one.
//
// Failure messages print enum values as numbers: Direction(0) is North,
// (1) East, (2) South, (3) West.
//
// Grade: grade 04_structs_enums/02_enums

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
