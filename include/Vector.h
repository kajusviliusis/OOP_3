#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename T>
class Vector {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

public:
    //member types
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = value_type*;
    using const_iterator = const value_type*;
};

#endif
