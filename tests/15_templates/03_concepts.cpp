#include "grader.hpp"
#include "15_templates/03_concepts.cpp"

#include <string>
#include <vector>

// Ask "would this call compile?" without breaking the build when it wouldn't.
template <class T>
constexpr bool accepts_gcd = requires(T a) { gcd(a, a); };

template <class T>
constexpr bool accepts_clamp = requires(T a) { clamp_to(a, a, a); };

template <class T>
constexpr bool accepts_total_area = requires(std::vector<T> shapes) { total_area(shapes); };

struct Square {
    double side;
    double area() const { return side * side; }
};

struct Triangle {
    double base;
    double height;
    double area() const { return base * height / 2; }
};

struct Label {
    std::string text;
};

struct Fancy {
    std::string area() const { return "huge"; }
};

struct Unordered {
    int value;
};

TEST("gcd: common cases") {
    CHECK_EQ(gcd(12, 18), 6);
    CHECK_EQ(gcd(17, 5), 1);
    CHECK_EQ(gcd(0, 5), 5);
}

TEST("gcd: negative inputs give a positive result") {
    CHECK_EQ(gcd(-12, 18), 6);
    CHECK_EQ(gcd(12, -18), 6);
}

TEST("gcd: works for every integer type") {
    CHECK_EQ(gcd(48u, 36u), 12u);
    CHECK_EQ(gcd(1'000'000'000'000LL, 750'000'000'000LL), 250'000'000'000LL);
    CHECK_EQ(gcd(short{21}, short{14}), short{7});
}

TEST("gcd: rejects non-integer types") {
    CHECK_EQ(gcd(10L, 4L), 2L);
    CHECK(!accepts_gcd<double>, "gcd(double, double) compiles: constrain T with std::integral");
    CHECK(!accepts_gcd<Unordered>, "gcd(Unordered, Unordered) compiles: constrain T");
}

TEST("clamp_to: numbers") {
    CHECK_EQ(clamp_to(5, 0, 10), 5);
    CHECK_EQ(clamp_to(-3, 0, 10), 0);
    CHECK_EQ(clamp_to(42, 0, 10), 10);
    CHECK_NEAR(clamp_to(1.5, 0.0, 1.0), 1.0);
}

TEST("clamp_to: strings") {
    CHECK_EQ(clamp_to(std::string("melon"), std::string("b"), std::string("k")), "k");
    CHECK_EQ(clamp_to(std::string("cherry"), std::string("b"), std::string("k")), "cherry");
}

TEST("clamp_to: rejects types without <") {
    CHECK_EQ(clamp_to(7, 1, 5), 5);
    CHECK(!accepts_clamp<Unordered>, "clamp_to(Unordered...) compiles: constrain T with std::totally_ordered");
}

TEST("total_area: adds up area()") {
    CHECK_NEAR(total_area(std::vector<Square>{{2}, {3}}), 13.0);
    CHECK_NEAR(total_area(std::vector<Triangle>{{4, 3}}), 6.0);
    CHECK_NEAR(total_area(std::vector<Square>{}), 0.0);
}

TEST("HasArea: matches only types with a numeric area()") {
    CHECK_NEAR(total_area(std::vector<Square>{{1}}), 1.0);
    CHECK(HasArea<Square>);
    CHECK(HasArea<Triangle>);
    CHECK(!HasArea<Label>, "HasArea<Label> is true, but Label has no area()");
    CHECK(!HasArea<int>, "HasArea<int> is true, but int has no area()");
    CHECK(!HasArea<Fancy>, "HasArea<Fancy> is true, but Fancy::area() returns a string");
    CHECK(!accepts_total_area<Label>, "total_area(std::vector<Label>) should not compile");
}

TEST("type_category: integers and booleans") {
    CHECK_EQ(type_category<int>(), "integer");
    CHECK_EQ(type_category<unsigned long long>(), "integer");
    CHECK_EQ(type_category<char>(), "integer");
    CHECK_EQ(type_category<bool>(), "boolean");
}

TEST("type_category: decimals") {
    CHECK_EQ(type_category<double>(), "decimal");
    CHECK_EQ(type_category<float>(), "decimal");
}

TEST("type_category: text") {
    CHECK_EQ(type_category<std::string>(), "text");
    CHECK_EQ(type_category<std::string_view>(), "text");
    CHECK_EQ(type_category<const char*>(), "text");
}

TEST("type_category: everything else") {
    CHECK_EQ(type_category<std::vector<int>>(), "other");
    CHECK_EQ(type_category<Square>(), "other");
    CHECK_EQ(type_category<int*>(), "other");
}
