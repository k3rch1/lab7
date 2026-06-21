#include <gtest/gtest.h>
#include "sequence_stream.hpp"
#include "lazy_sequence_stream.hpp"
#include "test_helpers.hpp"

TEST(sequence_stream, ctor) {
    array_sequence<int> seq = {1, 2, 3};

    sequence_stream<int> stream(&seq);

    ASSERT_EQ(stream.position(), 0);
}

TEST(sequence_stream, read) {
    array_sequence<int> seq = {1, 2, 3};

    sequence_stream<int> stream(&seq);

    ASSERT_EQ(stream.read(), 1);
    ASSERT_EQ(stream.read(), 2);
    ASSERT_EQ(stream.read(), 3);
}

TEST(sequence_stream, position) {
    array_sequence<int> seq = {1, 2, 3};

    sequence_stream<int> stream(&seq);

    stream.read();
    stream.read();

    ASSERT_EQ(stream.position(), 2);
}

TEST(sequence_stream, seek_forward) {
    array_sequence<int> seq = {1, 2, 3};

    sequence_stream<int> stream(&seq);

    stream.seek(2);

    ASSERT_EQ(stream.read(), 3);
}

TEST(sequence_stream, seek_back) {
    array_sequence<int> seq = {1, 2, 3};

    sequence_stream<int> stream(&seq);

    stream.read();
    stream.read();

    stream.seek(0);

    ASSERT_EQ(stream.read(), 1);
}

TEST(sequence_stream, end_of_stream) {
    array_sequence<int> seq = {1};

    sequence_stream<int> stream(&seq);

    ASSERT_FALSE(stream.is_end_of_stream());

    stream.read();

    ASSERT_TRUE(stream.is_end_of_stream());
}

TEST(sequence_stream, read_past_end) {
    array_sequence<int> seq = {1};

    sequence_stream<int> stream(&seq);

    stream.read();

    ASSERT_THROW(stream.read(), std::out_of_range);
}

TEST(lazy_sequence_stream, read) {
    auto fib = fibonacci_seq();

    lazy_sequence_stream<int> stream(&fib);

    ASSERT_EQ(stream.read(), 1);
    ASSERT_EQ(stream.read(), 1);
    ASSERT_EQ(stream.read(), 2);
    ASSERT_EQ(stream.read(), 3);
}

TEST(lazy_sequence_stream, position) {
    auto fib = fibonacci_seq();

    lazy_sequence_stream<int> stream(&fib);

    stream.read();
    stream.read();

    ASSERT_EQ(stream.position(), 2);
}

TEST(lazy_sequence_stream, seek) {
    auto fib = fibonacci_seq();

    lazy_sequence_stream<int> stream(&fib);

    stream.seek(5);

    ASSERT_EQ(stream.read(), 8);
}

TEST(lazy_sequence_stream, never_end) {
    auto fib = fibonacci_seq();

    lazy_sequence_stream<int> stream(&fib);

    ASSERT_FALSE(stream.is_end_of_stream());
}