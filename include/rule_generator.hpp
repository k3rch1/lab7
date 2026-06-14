#pragma once
#include "generator.hpp"
#include <functional>

template<class T>
class rule_generator : public generator<T> {
private:
    std::function<T(const sequence<T>&)> rule_;

public:
    rule_generator(const sequence<T>* cache, std::function<T(const sequence<T>&)> rule) : generator<T>(cache), rule_(rule) {};

    bool has_next() const override;

    T get_next() override;

    generator<T>* clone(const sequence<T>* cache) const override;
};

template<class T>
bool rule_generator<T>::has_next() const {
    return true;
}

template<class T>
T rule_generator<T>::get_next() {
    return rule_(*this->cache_);
}

template<class T>
generator<T>* rule_generator<T>::clone(const sequence<T>* cache) const {
    return new rule_generator(cache, rule_);
}