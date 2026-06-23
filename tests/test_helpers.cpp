#include "test_helpers.hpp"

lazy_sequence<int> fibonacci_seq() {
    array_sequence<int> seed = {1, 1};
    return lazy_sequence<int>(seed, [](const sequence<int>& seq) {return seq[seq.size() - 1] + seq[seq.size() - 2];});
}

lazy_sequence<int> geometric_sequence(int first, int ratio) {
    array_sequence<int> seed = {first};
    return lazy_sequence<int>(seed, [ratio](const sequence<int>& seq) {return seq[seq.size() - 1] * ratio;});
}