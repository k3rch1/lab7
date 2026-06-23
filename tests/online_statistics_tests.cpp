#include <gtest/gtest.h>
#include "online_statistics.hpp"
#include "lazy_sequence_stream.hpp"
#include "test_helpers.hpp"

TEST(online_statistics, empty) {
    online_statistics<int> stats;

    ASSERT_TRUE(stats.empty());
}

TEST(online_statistics, add_first) {
    online_statistics<int> stats;

    stats.add(5);

    ASSERT_FALSE(stats.empty());

    ASSERT_EQ(stats.count(), 1);
    ASSERT_EQ(stats.sum(), 5);

    ASSERT_EQ(stats.min(), 5);
    ASSERT_EQ(stats.max(), 5);

    ASSERT_EQ(stats.last(), 5);
}

TEST(online_statistics, count) {
    online_statistics<int> stats;

    stats.add(1);
    stats.add(2);
    stats.add(3);

    ASSERT_EQ(stats.count(), 3);
}

TEST(online_statistics, sum) {
    online_statistics<int> stats;

    stats.add(1);
    stats.add(2);
    stats.add(3);

    ASSERT_EQ(stats.sum(), 6);
}

TEST(online_statistics, min) {
    online_statistics<int> stats;

    stats.add(5);
    stats.add(2);
    stats.add(7);

    ASSERT_EQ(stats.min(), 2);
}

TEST(online_statistics, max) {
    online_statistics<int> stats;

    stats.add(5);
    stats.add(2);
    stats.add(7);

    ASSERT_EQ(stats.max(), 7);
}

TEST(online_statistics, last) {
    online_statistics<int> stats;

    stats.add(5);
    stats.add(2);
    stats.add(7);

    ASSERT_EQ(stats.last(), 7);
}

TEST(online_statistics, mean) {
    online_statistics<int> stats;

    stats.add(1);
    stats.add(2);
    stats.add(3);

    ASSERT_DOUBLE_EQ(stats.mean(), 2.0);
}

TEST(online_statistics, range) {
    online_statistics<int> stats;

    stats.add(5);
    stats.add(2);
    stats.add(9);

    ASSERT_EQ(stats.range(), 7);
}

TEST(online_statistics, variance) {
    online_statistics<int> stats;

    stats.add(1);
    stats.add(2);
    stats.add(3);

    ASSERT_NEAR(stats.variance(), 2.0 / 3.0, 1e-6);
}

TEST(online_statistics, clear) {
    online_statistics<int> stats;

    stats.add(1);
    stats.add(2);

    stats.clear();

    ASSERT_TRUE(stats.empty());
    ASSERT_EQ(stats.count(), 0);
}

TEST(online_statistics, empty_access) {
    online_statistics<int> stats;

    ASSERT_THROW(stats.min(), std::logic_error);
    ASSERT_THROW(stats.max(), std::logic_error);
    ASSERT_THROW(stats.last(), std::logic_error);
    ASSERT_THROW(stats.mean(), std::logic_error);
    ASSERT_THROW(stats.variance(), std::logic_error);
    ASSERT_THROW(stats.range(), std::logic_error);
}

TEST(online_statistics, stream) {
    auto fib = fibonacci_seq();
    lazy_sequence_stream<int> stream(&fib);

    online_statistics<int> stats;

    for (size_t i = 0; i < 10; ++i) stats.add(stream.read());

    ASSERT_EQ(stats.count(), 10);
    ASSERT_EQ(stats.min(), 1);
    ASSERT_EQ(stats.max(), 55);
}