#include "grader.hpp"
#include "14_inheritance_polymorphism/03_polymorphism_bugs.cpp"

TEST("describe() uses each animal's own sound") {
    CHECK_EQ(Dog("Rex").describe(), "Rex says Woof");
    CHECK_EQ(Cat("Tom").describe(), "Tom says Meow");
}

TEST("make_zoo: every animal keeps its real type") {
    const auto zoo = make_zoo();
    CHECK_EQ(chorus(zoo), {"Rex says Woof", "Tom says Meow"});
}

TEST("make_zoo: the zoo holds a live Dog until it's destroyed") {
    {
        const auto zoo = make_zoo();
        CHECK_EQ(live_dogs, 1);
    }
    CHECK_EQ(live_dogs, 0);
}

TEST("adopt_dog: destroying the pet runs ~Dog") {
    {
        const auto pet = adopt_dog("Fido");
        CHECK_EQ(pet->describe(), "Fido says Woof");
        CHECK_EQ(live_dogs, 1);
    }
    CHECK_EQ(live_dogs, 0);
}

TEST("travel: each animal moves its own way") {
    const Bird tweety("Tweety");
    const Dog rex("Rex");
    CHECK_EQ(travel(tweety), "Tweety flies");
    CHECK_EQ(travel(rex), "Rex walks");
}

TEST("count_dogs") {
    const Dog rex("Rex");
    const Cat tom("Tom");
    const Bird tweety("Tweety");
    const Dog fido("Fido");
    CHECK_EQ(count_dogs({&rex, &tom, &tweety, &fido}), 2);
    CHECK_EQ(count_dogs({&tom, &tweety}), 0);
    CHECK_EQ(count_dogs({}), 0);
}
