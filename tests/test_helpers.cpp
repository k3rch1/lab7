#include "test_helpers.hpp"

lazy_sequence<int> fibonacci_seq() {
    array_sequence<int> seed = {1, 1};
    return lazy_sequence<int>(seed, [](const sequence<int>& seq) {return seq[seq.size() - 1] + seq[seq.size() - 2];});
}