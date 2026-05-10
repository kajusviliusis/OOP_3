#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

// pagal https://en.cppreference.com/cpp/container/vector

template <typename T>
class Vector {
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

private:
    pointer data_;
    size_type size_;
    size_type capacity_;

    //helper funkcija capacity metodams, DRY :)
    void reallocate(size_type newCapacity)
    {
        pointer newData = newCapacity > 0 ? new value_type[newCapacity] : nullptr;

        for (size_type i = 0; i < size_; i++) {
            newData[i] = data_[i];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    //helper funkcija skirta push_back
    void growIfFull()
    {
        if (size_ < capacity_) return;

        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }

public:
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
            throw std::out_of_range("Vektoriaus indeksas uz ribu");
        }

        return data_[index];
    }

    const_reference at(size_type index) const
    {
        if (index >= size_) {
            throw std::out_of_range("Vektoriaus indeksas uz ribu");
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

    // iterators
    iterator begin()
    {
        return data_;
    }

    const_iterator begin() const
    {
        return data_;
    }

    iterator end()
    {
        return data_ + size_;
    }

    const_iterator end() const
    {
        return data_ + size_;
    }

    // capacity
    size_type size() const
    {
        return size_;
    }

    size_type capacity() const
    {
        return capacity_;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    void reserve(size_type newCapacity)
    {
        if (newCapacity <= capacity_) return;

        reallocate(newCapacity);
    }

    void shrink_to_fit()
    {
        if (capacity_ == size_) return;

        reallocate(size_);
    }

    // modifiers
    void push_back(const_reference value)
    {
        growIfFull();
        data_[size_] = value;
        size_++;
    }

    void push_back(value_type&& value)
    {
        growIfFull();
        data_[size_] = std::move(value);
        size_++;
    }

    void pop_back()
    {
        if (size_ > 0) {
            size_--;
        }
    }
    // docs: size() returns zero, leaves the capacity() of the vector unchanged
    void clear()
    {
        size_ = 0;
        // delete[] data;
        // data_ = nullptr;
        // capacity_ = 0;
    }

    void resize(size_type count)
    {
        if (count > capacity_) {
            reserve(count);
        }

        for (size_type i = size_; i < count; i++) {
            data_[i] = value_type{};
        }

        size_ = count;
    }

    void resize(size_type count, const_reference value)
    {
        if (count > capacity_) {
            reserve(count);
        }

        for (size_type i = size_; i < count; i++) {
            data_[i] = value;
        }

        size_ = count;
    }

    void swap(Vector& other) noexcept
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    iterator erase(const_iterator pos)
    {
        if (size_ == 0 || pos < data_ || pos >= data_ + size_) {
            throw std::out_of_range("Vektoriaus erase iteratorius uz ribu");
        }

        return erase(pos, pos + 1);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        if (first < data_ || last < first || last > data_ + size_) {
            throw std::out_of_range("Vektoriaus erase iteratorius uz ribu");
        }

        size_type firstIndex = first - data_;
        size_type lastIndex = last - data_;
        size_type count = lastIndex - firstIndex;
        // perstumia likusius elementus i kaire
        for (size_type i = firstIndex; i + count < size_; i++) {
            data_[i] = std::move(data_[i + count]);
        }

        size_ -= count;
        return data_ + firstIndex;
    }


};

// non-member functions
// comparison operatoriai
template <typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
{
    if (lhs.size() != rhs.size()) return false;

    for (std::size_t i = 0; i < lhs.size(); i++) {
        if (lhs[i] != rhs[i]) return false;
    }

    return true;
}

template <typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs)
{
    return !(lhs == rhs);
}

#endif
