#include "menu.hpp"
#include <iostream>
#include "lazy_sequence_stream.hpp"
#include "test_helpers.hpp"
#include "online_statistics.hpp"
#include <limits>

void menu::run() {
    bool running = true;
    while(running) {
        int choice;

        std::cout << "1. Fibonacci\n";
        std::cout << "2. Geometric progression\n";
        std::cout << "0. Exit\n";

        choice = read_value<int>();

        switch (choice) {
            case 0:
                running = false;
                break;
            
            case 1:
                fibonacci_demo();
                break;

            case 2:
                geometric_demo();
                break;

            default:
                break;
        }
    }
}

void menu::fibonacci_demo() {
    size_t count;

    std::cout << "Elements count: ";
    count = read_value<int>();

    auto fib = fibonacci_seq();
    lazy_sequence_stream<int> stream(&fib);
    online_statistics<int> stats;

    for (size_t i = 0; i < count; ++i) stats.add(stream.read());

    print_statistics(stats);
}

void menu::geometric_demo() {
    int first;
    int ratio;
    size_t count;

    std::cout << "First element: ";
    first = read_value<int>();

    std::cout << "Ratio: ";
    ratio = read_value<int>();

    std::cout << "Elements count: ";
    count = read_value<int>();

    auto seq = geometric_sequence(first, ratio);

    lazy_sequence_stream<int> stream(&seq);

    online_statistics<int> stats;

    for (size_t i = 0; i < count; ++i) {
        stats.add(stream.read());
    }

    print_statistics(stats);
}

template<class T>
void menu::print_statistics(const online_statistics<T>& stats) {
    std::cout << "\nStatistics\n";

    std::cout << "Count: " << stats.count() << '\n';
    std::cout << "Sum: " << stats.sum() << '\n';
    std::cout << "Min: " << stats.min() << '\n';
    std::cout << "Max: " << stats.max() << '\n';
    std::cout << "Last: " << stats.last() << '\n';

    std::cout << "Mean: " << stats.mean() << '\n';
    std::cout << "Variance: " << stats.variance() << '\n';
    std::cout << "Range: " << stats.range() << '\n';
}

template<class T>
T menu::read_value() {
    T value;

    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input. Try again: ";
    }

    return value;
}