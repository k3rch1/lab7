#pragma once
#include "generator.hpp"

template<class T>
class sequence_generator : public generator<T> {
private:
    const sequence<T>* source_;

    size_t current_;

public:
    sequence_generator(const sequence<T>* source) : source_(source), current_(0) {};

    bool has_next() const override;

    T get_next() override;

    generator<T>* clone() const override;
};

template<class T>
bool sequence_generator<T>::has_next() const {
    return current_ < source_->size();
}

template<class T>
T sequence_generator<T>::get_next() {
    return source_->get(current_++);
}

template<class T>
generator<T>* sequence_generator<T>::clone() const {
    return new sequence_generator(*this);
}