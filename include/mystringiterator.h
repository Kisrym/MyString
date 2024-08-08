class MyStringIterator {
private:
    char* ptr;

public:
    // types for stl compatibility
    using value_type = char;
    using pointer = char*;
    using reference = char&;
    using iterator_category = std::forward_iterator_tag; // iterador de avanço
    using difference_type = std::ptrdiff_t;

    MyStringIterator(pointer ptr) : ptr(ptr) {};

    reference operator*() const {return *ptr;};

    MyStringIterator& operator++() { // operador prefixado
        ++ptr;
        return *this;
    };

    MyStringIterator operator++(int) { // operador postfixado
        MyStringIterator temp = *this; // guarda o item atual, e o retorna depois
        ++ptr;
        return temp;
    };

    bool operator==(const MyStringIterator &other) const {
        return ptr == other.ptr;
    };

    bool operator!=(const MyStringIterator &other) const {
        return ptr != other.ptr;
    };
};