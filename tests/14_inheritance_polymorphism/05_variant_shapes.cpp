#include "grader.hpp"
#include "14_inheritance_polymorphism/05_variant_shapes.cpp"

constexpr double pi = std::numbers::pi;

TEST("area: each kind") {
    CHECK_NEAR(area(Circle{2}), 4 * pi);
    CHECK_NEAR(area(Rectangle{3, 4}), 12.0);
    CHECK_NEAR(area(Triangle{3, 4, 5}), 6.0);
}

TEST("perimeter: each kind") {
    CHECK_NEAR(perimeter(Circle{1}), 2 * pi);
    CHECK_NEAR(perimeter(Rectangle{3, 4}), 14.0);
    CHECK_NEAR(perimeter(Triangle{3, 4, 5}), 12.0);
}

TEST("name: each kind") {
    CHECK_EQ(name(Circle{1}), "circle");
    CHECK_EQ(name(Rectangle{1, 1}), "rectangle");
    CHECK_EQ(name(Triangle{1, 1, 1}), "triangle");
}

TEST("scaled: keeps the kind and scales every length") {
    const Shape circle = scaled(Circle{2}, 1.5);
    CHECK(std::holds_alternative<Circle>(circle), "scaling a Circle should give a Circle");
    CHECK_NEAR(std::get<Circle>(circle).radius, 3.0);

    const Shape rect = scaled(Rectangle{1, 2}, 2);
    CHECK(std::holds_alternative<Rectangle>(rect), "scaling a Rectangle should give a Rectangle");
    CHECK_NEAR(std::get<Rectangle>(rect).width, 2.0);
    CHECK_NEAR(std::get<Rectangle>(rect).height, 4.0);

    const Shape tri = scaled(Triangle{3, 4, 5}, 0.5);
    CHECK(std::holds_alternative<Triangle>(tri), "scaling a Triangle should give a Triangle");
    CHECK_NEAR(perimeter(tri), 6.0);
}

TEST("scaled: area grows with the square of the factor") {
    CHECK_NEAR(area(scaled(Rectangle{3, 4}, 3)), 108.0);
}

TEST("count_kinds") {
    const std::vector<Shape> shapes{Circle{1}, Triangle{3, 4, 5}, Circle{2}, Rectangle{1, 1},
                                    Circle{3}};
    CHECK_EQ(count_kinds(shapes), {3, 1, 1});
    CHECK_EQ(count_kinds({}), {0, 0, 0});
}

TEST("total_circle_area") {
    const std::vector<Shape> shapes{Circle{1}, Rectangle{10, 10}, Circle{2}};
    CHECK_NEAR(total_circle_area(shapes), 5 * pi);
    CHECK_NEAR(total_circle_area({Rectangle{1, 2}, Triangle{3, 4, 5}}), 0.0);
}

TEST("a mixed collection, all through the same functions") {
    const std::vector<Shape> shapes{Rectangle{2, 2}, Triangle{3, 4, 5}, Circle{1}};
    double total = 0;
    std::string names;
    for (const Shape &shape : shapes) {
        total += area(shape);
        names += name(shape) + " ";
    }
    CHECK_NEAR(total, 10 + pi);
    CHECK_EQ(names, "rectangle triangle circle ");
}
