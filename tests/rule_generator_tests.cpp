#include <gtest/gtest.h>
#include "rule_generator.hpp"
#include "array_sequence.hpp"

TEST(rule_generator, fibonacci) {
    array_sequence<int> cache{1, 1};

    rule_generator<int> gen(&cache, [](const sequence<int>& seq) {
        return seq.get(seq.size() - 1) + seq.get(seq.size() - 2);
    });

    ASSERT_EQ(gen.get_next(), 2);

    cache.append(2);
    ASSERT_EQ(gen.get_next(), 3);

    cache.append(3);
    ASSERT_EQ(gen.get_next(), 5);
}