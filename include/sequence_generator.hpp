#pragma once
#include "generator.hpp"

template<class T>
class sequence_generator : public generator<T> {
private:
    size_t current_;

public:
    sequence_generator(const sequence<T>* source) : generator<T>(source), current_(0) {};

    bool has_next() const override;

    T get_next() override;

    generator<T>* clone(const sequence<T>* cache) const override;
};

template<class T>
bool sequence_generator<T>::has_next() const {
    return current_ < this->cache_->size();
}

template<class T>
T sequence_generator<T>::get_next() {
    return this->cache_->get(current_++);
}

template<class T>
generator<T>* sequence_generator<T>::clone(const sequence<T>* cache) const {
    auto* copy = new sequence_generator(cache);
    copy->current_ = current_;
    return copy;
}