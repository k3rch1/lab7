#pragma once
#include "stream.hpp"
#include "sequence.hpp"

template<class T>
class sequence_stream : public stream<T> {
private:
    sequence<T>* source_;
    size_t position_ = 0;

public:
    sequence_stream(sequence<T>* source) : source_(source) {};

    bool is_end_of_stream() const override;

    T read() override;

    size_t position() const override;

    size_t seek(size_t index) override;
};

template<class T>
bool sequence_stream<T>::is_end_of_stream() const {
    return position_ >= source_->size();
}

template<class T>
T sequence_stream<T>::read() {
    if (is_end_of_stream()) throw std::out_of_range("end of stream");

    return source_->get(position_++);
}

template<class T>
size_t sequence_stream<T>::position() const {
    return position_;
}

template<class T>
size_t sequence_stream<T>::seek(size_t index) {
    position_ = index;
    return position_;
}