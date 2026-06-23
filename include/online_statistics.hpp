#pragma once
#include <cstddef>
#include <stdexcept>

template<class T>
class online_statistics {
private:
    size_t count_ = 0;
    T sum_ = T{};
    T sq_sum_ = T{};

    T min_;
    T max_;
    T last_;

    bool empty_ = true;

public:
    void add(const T& value);

    size_t count() const;

    T min() const;
    T max() const;

    T sum() const;
    T last() const;

    T range() const;

    double mean() const;
    double variance() const;

    bool empty() const;

    void clear();
};

template<class T>
void online_statistics<T>::add(const T& value) {
    if (empty_) {
        min_ = value;
        max_ = value;
        last_ = value;

        sum_ = value;
        sq_sum_ = value * value;

        count_ = 1;
        empty_ = false;

        return;
    }

    ++count_;

    sum_ += value;
    sq_sum_ += value * value;

    if (value < min_) min_ = value;
    if (value > max_) max_ = value;

    last_ = value;
}

template<class T>
size_t online_statistics<T>::count() const {
    return count_;
}

template<class T>
T online_statistics<T>::sum() const {
    return sum_;
}

template<class T>
T online_statistics<T>::min() const {
    if (empty_) throw std::logic_error("statistics is empty");
    return min_;
}

template<class T>
T online_statistics<T>::max() const {
    if (empty_) throw std::logic_error("statistics is empty");
    return max_;
}

template<class T>
T online_statistics<T>::last() const {
    if (empty_) throw std::logic_error("statistics is empty");
    return last_;
}

template<class T>
double online_statistics<T>::mean() const {
    if (empty_) throw std::logic_error("statistics is empty");
    return static_cast<double>(sum_) / count_;
}

template<class T>
double online_statistics<T>::variance() const {
    if (empty_) throw std::logic_error("statistics is empty");
    double avg = mean();

    return static_cast<double>(sq_sum_) / count_ - avg * avg;
}

template<class T>
T online_statistics<T>::range() const {
    if (empty_) throw std::logic_error("statistics is empty");
    return max_ - min_;
}

template<class T>
bool online_statistics<T>::empty() const {
    return empty_;
}

template<class T>
void online_statistics<T>::clear() {
    count_ = 0;
    sum_ = T{};
    sq_sum_ = T{};
    empty_ = true;
}