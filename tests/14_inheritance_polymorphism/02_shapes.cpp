#include "grader.hpp"
#include "14_inheritance_polymorphism/02_shapes.cpp"

constexpr double pi = std::numbers::pi;

TEST("Circle") {
    const Circle c(2);
    CHECK_NEAR(c.area(), 4 * pi);
    CHECK_NEAR(c.perimeter(), 4 * pi);
    CHECK_EQ(c.name(), "circle");
    CHECK_NEAR(Circle(1).area(), pi);
}

TEST("Rectangle") {
    const Rectangle r(3, 4);
    CHECK_NEAR(r.area(), 12.0);
    CHECK_NEAR(r.perimeter(), 14.0);
    CHECK_EQ(r.name(), "rectangle");
}

TEST("Triangle") {
    const Triangle t(3, 4, 5);
    CHECK_NEAR(t.area(), 6.0);
    CHECK_NEAR(t.perimeter(), 12.0);
    CHECK_EQ(t.name(), "triangle");
    CHECK_NEAR(Triangle(2, 2, 2).area(), std::sqrt(3.0));
}

TEST("constructors reject sizes that aren't positive") {
    CHECK_THROWS(std::invalid_argument, Circle(0));
    CHECK_THROWS(std::invalid_argument, Circle(-1));
    CHECK_THROWS(std::invalid_argument, Rectangle(0, 2));
    CHECK_THROWS(std::invalid_argument, Rectangle(2, -3));
    CHECK_THROWS(std::invalid_argument, Triangle(3, 0, 3));
}

TEST("Triangle rejects impossible sides") {
    CHECK_THROWS(std::invalid_argument, Triangle(1, 2, 3));
    CHECK_THROWS(std::invalid_argument, Triangle(1, 1, 5));
    CHECK_THROWS(std::invalid_argument, Triangle(10, 2, 3));
}

TEST("shapes work through a Shape reference") {
    const Rectangle rect(2, 5);
    const Shape &shape = rect;
    CHECK_NEAR(shape.area(), 10.0);
    CHECK_EQ(shape.name(), "rectangle");
    CHECK(std::is_abstract_v<Shape>, "Shape should stay abstract");
}

TEST("total_area") {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(1));
    shapes.push_back(std::make_unique<Rectangle>(2, 3));
    shapes.push_back(std::make_unique<Triangle>(3, 4, 5));
    CHECK_NEAR(total_area(shapes), pi + 12);
    CHECK_NEAR(total_area({}), 0.0);
}

TEST("largest") {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(1));
    shapes.push_back(std::make_unique<Rectangle>(2, 3));
    shapes.push_back(std::make_unique<Triangle>(3, 4, 5));
    CHECK(largest(shapes) == shapes[1].get(), "largest should point at the 2x3 rectangle");
    CHECK(largest({}) == nullptr, "largest of nothing should be nullptr");
}

TEST("largest: ties go to the first") {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(1, 6));
    shapes.push_back(std::make_unique<Rectangle>(2, 3));
    CHECK(largest(shapes) == shapes[0].get(), "two equal areas: expected the first shape");
}

TEST("make_shape: valid specs") {
    auto circle = make_shape("circle 2");
    CHECK(circle != nullptr, "make_shape(\"circle 2\") returned nullptr");
    CHECK_EQ(circle->name(), "circle");
    CHECK_NEAR(circle->area(), 4 * pi);

    auto rect = make_shape("rectangle 3 4");
    CHECK(rect != nullptr, "make_shape(\"rectangle 3 4\") returned nullptr");
    CHECK_NEAR(rect->area(), 12.0);

    auto triangle = make_shape("triangle 3 4 5");
    CHECK(triangle != nullptr, "make_shape(\"triangle 3 4 5\") returned nullptr");
    CHECK_EQ(triangle->name(), "triangle");
}

TEST("make_shape: extra spaces and decimals") {
    auto rect = make_shape("  rectangle   2.5  4 ");
    CHECK(rect != nullptr, "make_shape(\"  rectangle   2.5  4 \") returned nullptr");
    CHECK_NEAR(rect->area(), 10.0);
}

TEST("make_shape: bad specs give nullptr") {
    for (std::string_view spec : {"hexagon 2", "circle", "rectangle 3", "circle 2 3", "circle abc",
                                  "", "circle -1", "triangle 1 2 3"}) {
        CHECK(make_shape(spec) == nullptr,
              std::format("make_shape(\"{}\") should return nullptr", spec));
    }
}
