#pragma once
#include <cstddef>

template<class T>
class stream {
public:
    virtual ~stream() = default;

    virtual bool is_end_of_stream() const = 0;

    virtual T read() = 0;

    virtual size_t position() const = 0;

    virtual size_t seek(size_t index) = 0;
};