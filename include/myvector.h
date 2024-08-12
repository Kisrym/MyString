#ifndef VECTOR_H
#define VECTOR_H

#include <ostream>

#include "myvectoriterator.h"

template<typename T>
class MyVector {
friend std::ostream &operator<<(std::ostream &os, const MyVector &obj) {
    os << "[";
    for (std::size_t i = 0; i < obj.size; i++) {
        os << obj.vec[i] << (i == (obj.size - 1) ? "" : ", ");
    }
    os << "]";
    return os;
}

private:
    T *vec;
    std::size_t size;
    std::size_t capacity;

    void resize(std::size_t new_capacity);

public:
    // constructors
    MyVector();
    MyVector(std::initializer_list<T> values);
    MyVector(const MyVector &other);
    MyVector(MyVector &&other);

    ~MyVector();

    // operator overloading
    inline T &operator[](std::size_t index) {return vec[index];};

    // member methods
    inline std::size_t get_size() const noexcept {return size;};
    inline std::size_t get_capacity() const noexcept {return capacity;};
    inline T *data() const noexcept {return vec;};

    void append(const T &value) noexcept;
    // void emplace_back() // talvez implementar depois
    void pop() noexcept;
    void clear() noexcept;
    bool contains(const T &value) noexcept;

    // iterator
    using iterator = MyVectorIterator<T>;
    using const_iterator = const MyVectorIterator<T>;

    iterator begin() {
        return MyVectorIterator(vec);
    }

    iterator end() {
        return MyVectorIterator(vec + size);
    }

    const_iterator cbegin() const {
        return MyVectorIterator(vec);
    }

    const_iterator cend() const {
        return MyVectorIterator(vec + size);
    }
};

#include "myvector.tpp"

#endif