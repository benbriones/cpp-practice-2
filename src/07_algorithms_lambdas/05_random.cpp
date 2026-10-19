// Exercise: Random numbers
// <random> separates the engine (the source of randomness) from the
// distribution (the shape of numbers you want). Seed the engine and you get the
// same sequence every run, which is what makes random code testable:
//
//     std::mt19937 rng(seed);
//     std::uniform_int_distribution<int> die(1, 6);
//     int roll = die(rng);
//
// Grade: grade 07_algorithms_lambdas/05_random

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

// The numbers 0..51 in an order shuffled by std::shuffle with a std::mt19937 seeded
// with seed. The same seed always gives the same order.
// (std::iota from <numeric> fills a range with 0, 1, 2, ...)
std::vector<int> shuffled_deck(unsigned seed) {
    throw "TODO";
}

// One roll of a six-sided die using the given engine. The engine is passed by
// reference so that every call advances the same sequence.
int roll_die(std::mt19937& rng) {
    throw "TODO";
}

// Roll two dice `rolls` times with an engine seeded with seed, and count how often
// each total came up. Return 13 counts: index 2..12 holds the count for that total,
// indexes 0 and 1 stay 0.
std::vector<int> dice_histogram(int rolls, unsigned seed) {
    throw "TODO";
}

// Estimate pi: take `samples` random points (x, y) with x and y between 0.0 and 1.0
// (std::uniform_real_distribution<double>), count those with x*x + y*y <= 1,
// and return 4 * inside / samples. Use an engine seeded with seed.
double estimate_pi(int samples, unsigned seed) {
    throw "TODO";
}
