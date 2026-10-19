// Function bodies for geometry.hpp. The instructions are in geometry.hpp.

#include "geometry.hpp"

double triangle_perimeter(Point a, Point b, Point c) {
    return distance(a, b) + distance(b, c) + distance(c, a);
}
