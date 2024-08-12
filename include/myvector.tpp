#include "myvector.h"

template <typename T>
MyVector<T>::MyVector()
    : vec(nullptr), size(0), capacity(0)
{}

template <typename T>
MyVector<T>::MyVector(std::initializer_list<T> values)
    : size(values.size()), capacity(values.size())
{
    vec = new T[capacity];
    std::size_t i = 0;
    for (const T &v : values) {
        vec[i++] = v;
    }
}

template <typename T>
MyVector<T>::MyVector(const MyVector &other)
    : size(other.size), capacity(other.capacity)
{
    vec = new T[capacity];
    for (std::size_t i = 0; i < size; i++) {
        vec[i] = other.vec[i];
    }
}

template <typename T>
MyVector<T>::MyVector(MyVector &&other)
    : vec(other.vec), size(other.size), capacity(other.capacity)
{
    // std::cout << "calling move constructor" << std::endl;
    other.vec = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template <typename T>
MyVector<T>::~MyVector() {
    delete [] vec;
}

// private methods
template <typename T>
void MyVector<T>::resize(std::size_t new_capacity) {
    T *new_vec = new T[new_capacity];

    for (std::size_t i = 0; i < size; i++) {
        new_vec[i] = std::move(vec[i]);
    }

    delete [] vec;
    vec = new_vec;
    capacity = new_capacity;
}

// member methods
template <typename T>
void MyVector<T>::append(const T &value) noexcept {
    if (size >= capacity) {
        // se for o primeiro valor a ser adicionado, a capacidade vai para 1, se não, vai para o dobro da capacidade atual
        resize((capacity == 0) ? 1 : capacity * 2);
    }

    vec[size++] = value; // adiciona o valor no final e incrementa o size
}

template <typename T>
void MyVector<T>::pop() noexcept {
    if (size > 0){
        --size; // o objeto excluído ainda estará lá, mas você irá sobrepor ele
    }
}

template <typename T>
void MyVector<T>::clear() noexcept {
    if (size > 0) {
        delete [] vec;
        vec = nullptr;
        size = 0;
        capacity = 0;
    }
}

template <typename T>
bool MyVector<T>::contains(const T &value) noexcept {
    if (size > 0) {
        for (const T &v : *this) {
            if (value == v) {
                return true;
            }
        }
    }

    return false;
}