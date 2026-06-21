#pragma once
#include <cstddef>
#include <stdexcept>

class cardinal {
private:
    size_t value_ = 0;
    bool infinite_ = false;

public:
    cardinal() = default;
    cardinal(size_t value);

    static cardinal omega();

    bool is_finite() const;
    bool is_infinite() const;

    size_t value() const;

    cardinal& operator++();
    cardinal operator++(int);

    cardinal& operator--();
    cardinal operator--(int);

    bool operator==(const cardinal& other) const;
    bool operator!=(const cardinal& other) const;

    bool operator<(const cardinal& other) const;
    bool operator>(const cardinal& other) const;

    bool operator<=(const cardinal& other) const;
    bool operator>=(const cardinal& other) const;
};