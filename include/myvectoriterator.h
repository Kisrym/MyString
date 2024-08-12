
template <typename T>
class MyVectorIterator {
private:
    T *ptr;

public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::forward_iterator_tag; // iterador de avanço
    using difference_type = std::ptrdiff_t;

    MyVectorIterator(pointer ptr) : ptr(ptr) {};

    reference operator*() const {return *ptr;};

    MyVectorIterator &operator++() { // prefixado
        ++ptr;
        return *this;
    };

    MyVectorIterator operator++(int) { // posfixado
        MyVectorIterator temp = *this;
        ++ptr;
        return temp;
    };

    bool operator==(const MyVectorIterator &other) const {
        return ptr == other.ptr;
    };

    bool operator!=(const MyVectorIterator &other) const {
        return ptr != other.ptr;
    };
};