#pragma once
#include <functional>
#include "array_sequence.hpp"
#include "rule_generator.hpp"

enum class cardinal {
    finite,
    infinite
};

template<class T>
class lazy_sequence : public sequence<T> {
private:
    array_sequence<T> cache_;
    cardinal cardinality_ = cardinal::finite;
    generator<T>* generator_ = nullptr;

    void memoize(size_t index);
    bool exhausted_ = false;

public:
    lazy_sequence() = default;

    lazy_sequence(const sequence<T>& source);
    lazy_sequence(const sequence<T>& seed, std::function<T(const sequence<T>&)> rule);

    lazy_sequence(const lazy_sequence& other);
    lazy_sequence(lazy_sequence&& other) noexcept;
    lazy_sequence& operator=(const lazy_sequence& other);
    lazy_sequence& operator=(lazy_sequence&& other) noexcept;

    ~lazy_sequence() override;

    size_t size() const noexcept override;
    cardinal cardinality() const noexcept;
    bool empty() const noexcept override;

    T& front() override;
    const T& front() const override;

    T& back() override;
    const T& back() const override;

    T& operator[](size_t index) override;
    const T& operator[](size_t index) const override;

    T& get(size_t index) override;
    const T& get(size_t index) const override;

    void set(size_t index, const T& value) override;
    void set(size_t index, T&& value) override;

    void append(const T& value) override;
    void append(T&& value) override;

    void prepend(const T& value) override;
    void prepend(T&& value) override;

    void insert(size_t index, const T& value) override;
    void insert(size_t index, T&& value) override;

    void remove(size_t index) override;
    void clear() override;
};

template<class T>
void lazy_sequence<T>::memoize(size_t index) {
    while (cache_.size() <= index) {
        if (exhausted_) throw std::out_of_range("index out of range");
        if (!generator_->has_next()) {
            exhausted_ = true;
            throw std::out_of_range("index out of range");
        }

        cache_.append(generator_->get_next());
    }
}

template<class T>
lazy_sequence<T>::lazy_sequence(const sequence<T>& source) : cardinality_(cardinal::finite), exhausted_(true) {
    for (size_t i = 0; i < source.size(); ++i) cache_.append(source[i]);
}

template<class T>
lazy_sequence<T>::lazy_sequence(const sequence<T>& seed, std::function<T(const sequence<T>&)> rule) : cardinality_(cardinal::infinite) {
    for (size_t i = 0; i < seed.size(); ++i) cache_.append(seed[i]);
    generator_ = new rule_generator<T>(&cache_, std::move(rule));
}

template<class T>
lazy_sequence<T>::lazy_sequence(const lazy_sequence& other) : cache_(other.cache_), cardinality_(other.cardinality_), exhausted_(other.exhausted_) {
    generator_ = other.generator_ ? other.generator_->clone(&cache_) : nullptr;
}

template<class T>
lazy_sequence<T>::lazy_sequence(lazy_sequence&& other) noexcept : cache_(std::move(other.cache_)), cardinality_(other.cardinality_), exhausted_(other.exhausted_) {
    generator_ = other.generator_ ? other.generator_->clone(&cache_) : nullptr;
    delete other.generator_;
    other.generator_ = nullptr;
}

template<class T>
lazy_sequence<T>& lazy_sequence<T>::operator=(const lazy_sequence& other) {
    if (this == &other) return *this;
    delete generator_;

    cache_ = other.cache_;
    cardinality_ = other.cardinality_;
    exhausted_ = other.exhausted_;

    generator_ = other.generator_ ? other.generator_->clone(&cache_) : nullptr;
    return *this;
}

template<class T>
lazy_sequence<T>& lazy_sequence<T>::operator=(lazy_sequence&& other) noexcept {
    if (this == &other) return *this;
    delete generator_;

    cache_ = std::move(other.cache_);
    cardinality_ = other.cardinality_;
    exhausted_ = other.exhausted_;

    generator_ = other.generator_ ? other.generator_->clone(&cache_) : nullptr;
    delete other.generator_;
    other.generator_ = nullptr;
    return *this;
}

template<class T>
lazy_sequence<T>::~lazy_sequence() {
    delete generator_;
}

template<class T>
size_t lazy_sequence<T>::size() const noexcept {
    return cache_.size();
}

template<class T>
cardinal lazy_sequence<T>::cardinality() const noexcept {
    return cardinality_;
}

template<class T>
bool lazy_sequence<T>::empty() const noexcept {
    return cache_.empty();
}

template<class T>
T& lazy_sequence<T>::front() {
    return get(0);
}

template<class T>
const T& lazy_sequence<T>::front() const {
    return get(0);
}

template<class T>
T& lazy_sequence<T>::back() {
    throw std::logic_error("back() is not supported for lazy_sequence");
}

template<class T>
const T& lazy_sequence<T>::back() const {
    throw std::logic_error("back() is not supported for lazy_sequence");
}

template<class T>
T& lazy_sequence<T>::operator[](size_t index) {
    return get(index);
}

template<class T>
const T& lazy_sequence<T>::operator[](size_t index) const {
    return get(index);
}

template<class T>
T& lazy_sequence<T>::get(size_t index) {
    memoize(index);
    return cache_.get(index);
}

template<class T>
const T& lazy_sequence<T>::get(size_t index) const {
    const_cast<lazy_sequence*>(this)->memoize(index);
    return cache_.get(index);
}

template<class T>
void lazy_sequence<T>::set(size_t index, const T& value) {
    memoize(index);
    cache_.set(index, value);
}

template<class T>
void lazy_sequence<T>::set(size_t index, T&& value) {
    memoize(index);
    cache_.set(index, std::move(value));
}

template<class T>
void lazy_sequence<T>::append(const T& value) {
    cache_.append(value);
}

template<class T>
void lazy_sequence<T>::append(T&& value) {
    cache_.append(std::move(value));
}

template<class T>
void lazy_sequence<T>::prepend(const T& value) {
    cache_.prepend(value);
}

template<class T>
void lazy_sequence<T>::prepend(T&& value) {
    cache_.prepend(std::move(value));
}

template<class T>
void lazy_sequence<T>::insert(size_t index, const T& value) {
    if (index > cache_.size()) {
        if (exhausted_) throw std::out_of_range("index out of range");
        memoize(index - 1);
        if (index > cache_.size()) throw std::out_of_range("index out of range");
    }

    cache_.insert(index, value);
}

template<class T>
void lazy_sequence<T>::insert(size_t index, T&& value) {
    if (index > cache_.size()) {
        if (exhausted_) throw std::out_of_range("index out of range");
        memoize(index - 1);
        if (index > cache_.size()) throw std::out_of_range("index out of range");
    }

    cache_.insert(index, std::move(value));
}

template<class T>
void lazy_sequence<T>::remove(size_t index) {
    memoize(index);
    cache_.remove(index);
}

template<class T>
void lazy_sequence<T>::clear() {
    cache_.clear();
}