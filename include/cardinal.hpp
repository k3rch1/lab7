#pragma once
#include <cstddef>
#include <stdexcept>

class cardinal {
private:
    size_t value_ = 0;
    bool infinite_ = false;

public:
    cardinal() = default;
    explicit cardinal(size_t value) : value_(value) {};

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

cardinal cardinal::omega() {
    cardinal result;
    result.infinite_ = true;
    return result;
}

bool cardinal::is_finite() const {
    return !infinite_;
}

bool cardinal::is_infinite() const {
    return infinite_;
}

size_t cardinal::value() const {
    if (infinite_) throw std::logic_error("cardinal is infinite");
    return value_;
}

cardinal& cardinal::operator++() {
    if (!infinite_) ++value_;
    return *this;
}

cardinal cardinal::operator++(int) {
    cardinal copy(*this);
    ++(*this);
    return copy;
}

cardinal& cardinal::operator--() {
    if (infinite_) return *this;
    if (value_ == 0) throw std::out_of_range("cardinal underflow");
    --value_;

    return *this;
}

cardinal cardinal::operator--(int) {
    cardinal copy(*this);
    --(*this);
    return copy;
}

bool cardinal::operator==(const cardinal& other) const {
    if (infinite_ || other.infinite_) return infinite_ == other.infinite_;
    return value_ == other.value_;
}

bool cardinal::operator!=(const cardinal& other) const {
    return !(*this == other);
}

bool cardinal::operator<(const cardinal& other) const {
    if (infinite_) return false;
    if (other.infinite_) return true;

    return value_ < other.value_;
}

bool cardinal::operator>(const cardinal& other) const {
    return other < *this;
}

bool cardinal::operator<=(const cardinal& other) const {
    return !(*this > other);
}

bool cardinal::operator>=(const cardinal& other) const {
    return !(*this < other);
}