#include "cardinal.hpp"

cardinal::cardinal(size_t value) : value_(value) {};

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