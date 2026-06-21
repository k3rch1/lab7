#pragma once
#include "stream.hpp"
#include "lazy_sequence.hpp"

template<class T>
class lazy_sequence_stream : public stream<T> {
private:
    lazy_sequence<T>* source_;
    size_t position_ = 0;

public:
    explicit lazy_sequence_stream(lazy_sequence<T>* source) : source_(source) {};

    bool is_end_of_stream() const override;

    T read() override;

    size_t position() const override;

    size_t seek(size_t index) override;
};

template<class T>
bool lazy_sequence_stream<T>::is_end_of_stream() const {
    return false;
}

template<class T>
T lazy_sequence_stream<T>::read() {
    return source_->get(position_++);
}

template<class T>
size_t lazy_sequence_stream<T>::position() const {
    return position_;
}

template<class T>
size_t lazy_sequence_stream<T>::seek(size_t index) {
    position_ = index;
    return position_;
}