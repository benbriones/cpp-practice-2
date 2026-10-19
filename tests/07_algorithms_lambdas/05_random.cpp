#include "grader.hpp"
#include "07_algorithms_lambdas/05_random.cpp"

TEST("shuffled_deck: contains each card exactly once") {
    std::vector<int> deck = shuffled_deck(42);
    CHECK_EQ(deck.size(), 52);
    std::sort(deck.begin(), deck.end());
    std::vector<int> in_order(52);
    std::iota(in_order.begin(), in_order.end(), 0);
    CHECK_EQ(deck, in_order);
}

TEST("shuffled_deck: actually shuffled") {
    std::vector<int> in_order(52);
    std::iota(in_order.begin(), in_order.end(), 0);
    CHECK(shuffled_deck(42) != in_order, "the deck came back in its original order");
}

TEST("shuffled_deck: same seed, same order") {
    CHECK(shuffled_deck(7) == shuffled_deck(7), "two decks shuffled with seed 7 came out different");
    CHECK(shuffled_deck(123) == shuffled_deck(123), "two decks shuffled with seed 123 came out different");
}

TEST("shuffled_deck: different seeds, different orders") {
    CHECK(shuffled_deck(1) != shuffled_deck(2), "seeds 1 and 2 gave the same order");
}

TEST("roll_die: always between 1 and 6") {
    std::mt19937 rng(2024);
    for (int i = 0; i < 6000; ++i) {
        int roll = roll_die(rng);
        CHECK(roll >= 1 && roll <= 6, "roll_die returned " + std::to_string(roll));
    }
}

TEST("roll_die: every face comes up about equally often") {
    std::mt19937 rng(99);
    std::vector<int> counts(7, 0);
    for (int i = 0; i < 6000; ++i) {
        int roll = roll_die(rng);
        if (roll >= 1 && roll <= 6) ++counts[static_cast<std::size_t>(roll)];
    }
    for (int face = 1; face <= 6; ++face) {
        int count = counts[static_cast<std::size_t>(face)];
        CHECK(count > 850 && count < 1150,
              "face " + std::to_string(face) + " came up " + std::to_string(count) +
                  " times in 6000 rolls (expected about 1000)");
    }
}

TEST("dice_histogram: shape") {
    std::vector<int> counts = dice_histogram(36'000, 5);
    CHECK_EQ(counts.size(), 13);
    CHECK_EQ(counts[0], 0);
    CHECK_EQ(counts[1], 0);
    CHECK_EQ(std::accumulate(counts.begin(), counts.end(), 0), 36'000);
}

TEST("dice_histogram: 7 is most common, 2 and 12 are rare") {
    std::vector<int> counts = dice_histogram(36'000, 5);
    CHECK_EQ(counts.size(), 13);
    CHECK_EQ(std::max_element(counts.begin(), counts.end()) - counts.begin(), 7);
    CHECK(counts[7] > 5'500 && counts[7] < 6'500, "a total of 7 should come up about 6000 times");
    CHECK(counts[2] > 800 && counts[2] < 1'200, "a total of 2 should come up about 1000 times");
    CHECK(counts[12] > 800 && counts[12] < 1'200, "a total of 12 should come up about 1000 times");
}

TEST("dice_histogram: same seed, same counts") {
    CHECK(dice_histogram(1'000, 11) == dice_histogram(1'000, 11),
          "two histograms made with seed 11 came out different");
}

TEST("estimate_pi: close to 3.14159") {
    CHECK_NEAR(estimate_pi(100'000, 3), 3.14159, 0.03);
}

TEST("estimate_pi: same seed, same estimate") {
    CHECK(estimate_pi(1'000, 8) == estimate_pi(1'000, 8), "two estimates made with seed 8 differ");
}
