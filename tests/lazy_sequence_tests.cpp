#include <gtest/gtest.h>
#include "lazy_sequence.hpp"

lazy_sequence<int> fibonacci_seq() {
    array_sequence<int> seed = {1, 1};
    return lazy_sequence<int>(seed, [](const sequence<int>& seq) {return seq[seq.size() - 1] + seq[seq.size() - 2];});
}

TEST(lazy_sequence, finite_ctor) {
    array_sequence<int> source = {1, 2, 3};
    lazy_sequence<int> seq(source);

    ASSERT_EQ(seq.cardinality(), cardinal(3));

    for (size_t i = 0; i < source.size(); ++i) ASSERT_EQ(seq.get(i), source[i]);
}

TEST(lazy_sequence, infinite_ctor) {
    auto fib = fibonacci_seq();
    ASSERT_EQ(fib.cardinality(), cardinal::omega());
    array_sequence<int> expected = {1, 1, 2, 3, 5, 8, 13, 21};

    for (size_t i = 0; i < expected.size(); ++i) ASSERT_EQ(fib.get(i), expected[i]);
}

TEST(lazy_sequence, copy_ctor) {
    auto fib = fibonacci_seq();
    fib.get(10);
    lazy_sequence<int> copy(fib);
    copy.set(0, 100);

    ASSERT_EQ(fib.get(0), 1);
    ASSERT_EQ(copy.get(0), 100);
}

TEST(lazy_sequence, move_ctor) {
    auto fib = fibonacci_seq();
    fib.get(10);
    lazy_sequence<int> moved(std::move(fib));

    ASSERT_EQ(moved.get(0), 1);
    ASSERT_EQ(moved.get(1), 1);
    ASSERT_EQ(moved.get(10), 89);
}

TEST(lazy_sequence, copy_operator) {
    auto fib = fibonacci_seq();
    fib.get(10);
    lazy_sequence<int> copy;
    copy = fib;
    copy.set(0, 100);

    ASSERT_EQ(fib.get(0), 1);
    ASSERT_EQ(copy.get(0), 100);
}

TEST(lazy_sequence, move_operator) {
    auto fib = fibonacci_seq();
    fib.get(10);
    lazy_sequence<int> moved;
    moved = std::move(fib);

    ASSERT_EQ(moved.get(0), 1);
    ASSERT_EQ(moved.get(10), 89);
}

TEST(lazy_sequence, size) {
    auto fib = fibonacci_seq();
    ASSERT_EQ(fib.size(), 2);

    fib.get(10);

    ASSERT_EQ(fib.size(), 11);
}

TEST(lazy_sequence, cardinality_finite) {
    array_sequence<int> arr = {1, 2, 3};
    lazy_sequence<int> seq(arr);

    ASSERT_TRUE(seq.cardinality().is_finite());
}

TEST(lazy_sequence, cardinality_infinite) {
    auto fib = fibonacci_seq();

    ASSERT_TRUE(fib.cardinality().is_infinite());
}

TEST(lazy_sequence, empty) {
    array_sequence<int> arr;
    lazy_sequence<int> seq(arr);

    ASSERT_TRUE(seq.empty());
}

TEST(lazy_sequence, not_empty) {
    auto fib = fibonacci_seq();

    ASSERT_FALSE(fib.empty());
}

TEST(lazy_sequence, front) {
    auto fib = fibonacci_seq();
    
    ASSERT_EQ(fib.front(), 1);
}

TEST(lazy_sequence, back) {
    auto fib = fibonacci_seq();

    ASSERT_THROW(fib.back(), std::logic_error);
}

TEST(lazy_sequence, set) {
    auto fib = fibonacci_seq();

    fib.set(5, 100);

    ASSERT_EQ(fib.get(5), 100);
}

TEST(lazy_sequence, append) {
    array_sequence<int> arr = {1, 2, 3};

    lazy_sequence<int> seq(arr);

    seq.append(4);

    ASSERT_EQ(seq.get(3), 4);
}

TEST(lazy_sequence, prepend) {
    array_sequence<int> arr = {2, 3};

    lazy_sequence<int> seq(arr);

    seq.prepend(1);

    ASSERT_EQ(seq.get(0), 1);
    ASSERT_EQ(seq.get(1), 2);
    ASSERT_EQ(seq.get(2), 3);
}

TEST(lazy_sequence, insert) {
    array_sequence<int> arr = {1, 3};

    lazy_sequence<int> seq(arr);

    seq.insert(1, 2);

    ASSERT_EQ(seq.get(0), 1);
    ASSERT_EQ(seq.get(1), 2);
    ASSERT_EQ(seq.get(2), 3);
}

TEST(lazy_sequence, remove) {
    array_sequence<int> arr = {1, 2, 3};

    lazy_sequence<int> seq(arr);

    seq.remove(1);

    ASSERT_EQ(seq.get(0), 1);
    ASSERT_EQ(seq.get(1), 3);
}

TEST(lazy_sequence, clear) {
    auto fib = fibonacci_seq();

    fib.get(10);

    fib.clear();

    ASSERT_TRUE(fib.empty());
}

TEST(lazy_sequence, insert_back) {
    array_sequence<int> arr = {1, 2, 3};
    lazy_sequence<int> seq(arr);
    seq.insert(3, 4);

    ASSERT_EQ(seq.get(3), 4);
}

TEST(lazy_sequence, remove_last) {
    array_sequence<int> arr = {1, 2, 3};
    lazy_sequence<int> seq(arr);
    seq.remove(2);

    ASSERT_EQ(seq.size(), 2);
    ASSERT_EQ(seq.get(0), 1);
    ASSERT_EQ(seq.get(1), 2);
}