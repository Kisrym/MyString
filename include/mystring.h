#ifndef MYSTRING_H
#define MYSTRING_H

#include <ostream>
#include <vector>

#include "mystringiterator.h"

class MyString {
friend std::ostream &operator<<(std::ostream &os, const MyString &obj);
friend MyString operator+(const MyString &lhs, const MyString &rhs);

private:
    char *str;
    std::size_t size;

    inline std::size_t get_len(const char* string) const;
    std::size_t find_substring(const char* substring, std::pair<int, int> range = {0, -1}) const;
    inline void copy(char *str1, const char *str2, std::size_t num) const;
    void concat(char *str1, const char *str2) const noexcept;

public:
    // constructors
    MyString();
    MyString(const char *string);
    MyString(const std::string &string) : MyString(string.c_str()) {};
    MyString(const MyString &other) : MyString(other.str) {};
    MyString(MyString &&other) noexcept;

    // member operator overloadings
    MyString &operator=(const MyString &other);
    MyString &operator=(MyString &&other);
    const char operator[](std::size_t index) const {
        if (index > size - 1) {
            throw std::out_of_range("Index fora dos limites");
        }
        return str[index];

    };
    MyString operator[](std::pair<std::size_t, std::size_t> range) const;
    char &operator[](int index) {return str[index];};
    bool operator==(const char *string) const;
    bool operator==(const MyString &other) const {return *this == other.str;};

    MyString &operator+=(const char* string);
    MyString &operator+=(const char caracter);
    MyString &operator+=(const MyString &other) {return *this += other.str;};
    MyString &operator+=(const std::string &string) {return *this += string.c_str();};

    ~MyString();

    // member methods
    inline std::size_t len() const noexcept {return size;};
    MyString capitalize();
    std::vector<MyString> split(const char separator) const noexcept;
    std::vector<MyString> split(const char *separator) const noexcept;
    bool isAlpha() const noexcept;
    bool isNumeric() const noexcept;
    bool isAlphaNum() const noexcept;
    inline bool isEmpty() const noexcept {return (*this == "" || str[0] == '\0');}; // também vai retornar True se o único caracter for \0
    MyString toLower() const noexcept;
    MyString toUpper() const noexcept;
    void clear() noexcept;
    MyString trim() const noexcept;
    std::size_t find(const char *substring) const noexcept;
    std::vector<std::size_t> findAll(const char *substring) const noexcept;
    MyString replace(const char *origin, const char *dest) const noexcept;
    MyString format(std::initializer_list<const char*> values) const;
    const char *c_str() const noexcept {return str;};

    template <typename T>
    MyString join(const T &container) const noexcept{
        if (container.empty()) {
            return MyString("");
        }

        MyString result;
        for (auto it = container.cbegin(); it != container.cend(); it++) {
            if (it != container.cbegin()) {
                result += str;
            }
            result += *it;
        }

        return result;
    }

    // static methods
    template <typename T>
    static bool contains(const T &value, const std::vector<T> &vec) noexcept{
        for (const auto &v : vec) {
            if (value == v) {
                return true;
            }
        }
        return false;
    }

    // iterator
    using iterator = MyStringIterator;
    using const_iterator = const MyStringIterator;

    iterator begin() {
        return MyStringIterator(str);
    }

    iterator end() {
        return MyStringIterator(str + size);
    }

    const_iterator cbegin() const {
        return MyStringIterator(str);
    }

    const_iterator cend() const {
        return MyStringIterator(str);
    }
    
};

#endif