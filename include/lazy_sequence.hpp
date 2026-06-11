#pragma once
#include <functional>
#include "array_sequence.hpp"
#include "generator.hpp"

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
    lazy_sequence(const sequence<T>& cache, std::function<T(const sequence<T>&)> rule);

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
        if (!generator_->has_next()) exhausted_ = true;
        
        cache_.append(generator_->get_next());
    }
}