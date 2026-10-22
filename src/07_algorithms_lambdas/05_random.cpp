// === Lesson: Random numbers ==================================================
//
// <random> splits the job in two:
//
//     engine        produces raw random bits. std::mt19937 (the Mersenne Twister)
//                   is the usual choice.
//     distribution  turns those bits into the numbers you want: a range of ints,
//                   decimals, a bell curve...
//
//     std::mt19937 rng(std::random_device{}());              // a new seed every run
//     std::uniform_int_distribution<int> percent(1, 100);    // 1 to 100, both ends
//     std::uniform_real_distribution<double> unit(0.0, 1.0); // [0.0, 1.0): never 1.0
//     int p = percent(rng);          // call a distribution with the engine
//     double u = unit(rng);
//
// Seeding: an engine built from the same seed produces the same sequence every
// time, like Python's random.seed(42) (JavaScript's Math.random can't be seeded).
// Tests and simulations you want to replay take a seed; std::random_device{}()
// gives a fresh one when you want different results each run.
//
// An engine is an object with state, and every call advances it. Two pitfalls
// follow from that:
//
//     int coin(std::mt19937 rng) { ... }   // a copy: the caller's engine never moves
//                                          // on, so every call gives the same result
//     int coin() {
//         std::mt19937 rng(7);             // a new engine per call, same seed:
//         ...                              // the same "random" number every time
//     }
//
// Make one engine, then pass it around by reference (std::mt19937&).
// Distributions are cheap to create; making one per call is fine.
//
// Algorithms that need randomness take the engine as an argument:
//
//     std::vector<std::string> players{"ana", "ben", "chi", "dev"};
//     std::shuffle(players.begin(), players.end(), rng);   // a random order
//
// std::iota(first, last, start), from <numeric>, fills a range with start,
// start + 1, start + 2, ...
//
// Old code uses std::rand() % n: one global, low-quality generator, and the %
// makes some results more likely than others. Prefer <random>.
//
// Read more: https://www.learncpp.com/cpp-tutorial/introduction-to-random-number-generation/
//            https://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/
//
// === Exercise: Random numbers ================================================
// Where a function gets a seed, seed a std::mt19937 with it, so the tests can
// repeat your results.
//
// ./grade 07_algorithms_lambdas/05_random

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

// Return the numbers 0 to 51 in a shuffled order.
// Shuffle them with std::shuffle and a std::mt19937 seeded with seed.
// The same seed always gives the same order.
// (std::iota from <numeric> fills a range with 0, 1, 2, ...)
//
// Example:
//   shuffled_deck(42) holds 52 numbers, each of 0 to 51 exactly once, not in order
//   shuffled_deck(7) == shuffled_deck(7)    // same seed, same order
//   shuffled_deck(1) != shuffled_deck(2)    // different seeds, different orders
std::vector<int> shuffled_deck(unsigned seed) {
    throw "TODO";
}

// Return one roll of a six-sided die, using the given engine.
// The result is always between 1 and 6, and each face is equally likely.
// The engine is passed by reference so that every call advances the same sequence.
//
// Example:
//   std::mt19937 rng(2024);
//   int a = roll_die(rng);   // somewhere from 1 to 6
//   int b = roll_die(rng);   // the next roll in rng's sequence, also 1 to 6
//
// Over 6000 rolls, each face should come up about 1000 times.
int roll_die(std::mt19937& rng) {
    throw "TODO";
}

// Roll two dice `rolls` times and count how often each total came up.
// Use an engine seeded with seed.
// Return 13 counts: index 2..12 holds the count for that total.
// Indexes 0 and 1 stay 0, since two dice can't total less than 2.
//
// Example:
//   std::vector<int> counts = dice_histogram(36'000, 5);
//   counts.size() is 13, and the counts add up to 36'000
//   counts[7] is the biggest, about 6000; counts[2] and counts[12] are about 1000
//
// The same seed always gives the same counts.
std::vector<int> dice_histogram(int rolls, unsigned seed) {
    throw "TODO";
}

// Return an estimate of pi made from `samples` random points.
// Take `samples` random points (x, y) with x and y between 0.0 and 1.0
// (std::uniform_real_distribution<double>), and count those with x*x + y*y <= 1.
// Return 4 * inside / samples. Use an engine seeded with seed.
//
// Example:
//   estimate_pi(100'000, 3) is close to 3.14159 (within about 0.03)
//   estimate_pi(1'000, 8) == estimate_pi(1'000, 8)   // same seed, same estimate
//
// About pi/4 of the points land inside the quarter circle of radius 1.
double estimate_pi(int samples, unsigned seed) {
    throw "TODO";
}
