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
