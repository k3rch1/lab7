#pragma once
#include "online_statistics.hpp"

class menu {
public:
    void run();

private:
    void fibonacci_demo();
    void geometric_demo();

    template<class T>
    void print_statistics(const online_statistics<T>& stats);

    template<class T>
    T read_value();
};