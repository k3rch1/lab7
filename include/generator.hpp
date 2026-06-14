#pragma once
#include "sequence.hpp"

template<class T>
class generator {
protected:
    const sequence<T>* cache_;

public:
    generator(const sequence<T>* seq = nullptr) : cache_(seq) {}

    virtual bool has_next() const = 0;

    virtual T get_next() = 0;

    virtual generator<T>* clone(const sequence<T>* cache) const = 0;

    virtual ~generator() = default;
};