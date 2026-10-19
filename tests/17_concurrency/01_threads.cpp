#include "grader.hpp"
#include "17_concurrency/01_threads.cpp"

#include <numeric>

TEST("chunk_bounds: even split") {
    CHECK_EQ(chunk_bounds(9, 3), {0, 3, 6, 9});
    CHECK_EQ(chunk_bounds(4, 1), {0, 4});
}

TEST("chunk_bounds: bigger chunks first") {
    CHECK_EQ(chunk_bounds(10, 3), {0, 4, 7, 10});
    CHECK_EQ(chunk_bounds(11, 4), {0, 3, 6, 9, 11});
}

TEST("chunk_bounds: more parts than items") {
    CHECK_EQ(chunk_bounds(2, 4), {0, 1, 2, 2, 2});
    CHECK_EQ(chunk_bounds(0, 3), {0, 0, 0, 0});
}

TEST("parallel_sum: small inputs") {
    CHECK_EQ(parallel_sum({1, 2, 3, 4, 5}, 2), 15);
    CHECK_EQ(parallel_sum({7}, 1), 7);
    CHECK_EQ(parallel_sum({}, 3), 0);
}

TEST("parallel_sum: more threads than values") {
    CHECK_EQ(parallel_sum({10, -4, 6}, 8), 12);
}

TEST("parallel_sum: large input, any thread count") {
    std::vector<int> values(200'000);
    std::iota(values.begin(), values.end(), 1);
    for (int threads : {1, 2, 3, 7, 16}) {
        CHECK_EQ(parallel_sum(values, threads), 20'000'100'000LL);
    }
}

TEST("parallel_sum: result needs a long long") {
    std::vector<int> values(100'000, 2'000'000'000);
    CHECK_EQ(parallel_sum(values, 4), 200'000'000'000'000LL);
}

TEST("parallel_square: squares every element") {
    std::vector<long long> values{1, -2, 3, 4, 100'000};
    parallel_square(values, 2);
    CHECK_EQ(values, {1, 4, 9, 16, 10'000'000'000LL});
}

TEST("parallel_square: many elements, many threads") {
    std::vector<long long> values(50'000);
    std::iota(values.begin(), values.end(), 0LL);
    parallel_square(values, 6);
    bool all_squared = true;
    for (long long i = 0; i < 50'000; ++i) {
        if (values[static_cast<std::size_t>(i)] != i * i) all_squared = false;
    }
    CHECK(all_squared, "Some elements weren't squared exactly once");
}

TEST("parallel_square: empty vector and extra threads") {
    std::vector<long long> empty;
    parallel_square(empty, 4);
    CHECK_EQ(empty, {});
    std::vector<long long> one{9};
    parallel_square(one, 4);
    CHECK_EQ(one, {81});
}
