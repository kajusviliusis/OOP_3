#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

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

    //member functions
    // default konstruktorius
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    //konstruktorius su pradiniu size
    explicit Vector(size_type count)
        : data_(count > 0 ? new value_type[count]{} : nullptr),
          size_(count),
          capacity_(count) {}

    //initializer list konstruktorius
    Vector(std::initializer_list<value_type> values)
        : data_(values.size() > 0 ? new value_type[values.size()] : nullptr),
          size_(values.size()),
          capacity_(values.size())
    {
        size_type i = 0;
        for (const auto& value : values) {
            data_[i] = value;
            i++;
        }
    }

    //copy konstruktorius
    Vector(const Vector& other)
        : data_(other.size_ > 0 ? new value_type[other.size_] : nullptr),
          size_(other.size_),
          capacity_(other.size_)
    {
        for (size_type i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }

    //copy assignment operatorius
    Vector& operator=(const Vector& other)
    {
        if (this == &other) return *this;

        delete[] data_;

        data_ = other.capacity_ > 0 ? new value_type[other.capacity_] : nullptr;
        size_ = other.size_;
        capacity_ = other.capacity_;

        for (size_type i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }

        return *this;
    }

    //move konstruktorius
    Vector(Vector&& other) noexcept
        : data_(other.data_),
          size_(other.size_),
          capacity_(other.capacity_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    //move assignment operatorius
    Vector& operator=(Vector&& other) noexcept
    {
        if (this == &other) return *this;

        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }

    ~Vector()
    {
        delete[] data_;
    }

    // element access
    reference operator[](size_type index)
    {
        return data_[index];
    }

    const_reference operator[](size_type index) const
    {
        return data_[index];
    }

    reference at(size_type index)
    {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }

        return data_[index];
    }

    const_reference at(size_type index) const
    {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }

        return data_[index];
    }

    reference front()
    {
        return data_[0];
    }

    const_reference front() const
    {
        return data_[0];
    }

    reference back()
    {
        return data_[size_ - 1];
    }

    const_reference back() const
    {
        return data_[size_ - 1];
    }

    pointer data()
    {
        return data_;
    }

    const_pointer data() const
    {
        return data_;
    }





};

#endif
