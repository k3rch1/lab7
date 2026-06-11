#include <gtest/gtest.h>
#include "sequence_generator.hpp"
#include "array_sequence.hpp"

TEST(sequence_generator, first)
{
    array_sequence<int> expected = {1, 2, 3};

    sequence_generator<int> gen(&expected);

    for (auto el : expected) {
        ASSERT_TRUE(gen.has_next());
        ASSERT_EQ(gen.get_next(), el);
    }

    ASSERT_FALSE(gen.has_next());
}

TEST(sequence_generator, empty)
{
    array_sequence<int> seq;

    sequence_generator<int> gen(&seq);

    ASSERT_FALSE(gen.has_next());
}