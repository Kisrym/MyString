#include "mystring.h"

MyString::MyString()
    : str(nullptr), size(1)
{
    str = new char[size];
    *str = '\0';
}

MyString::MyString(const char *string)
    : str(nullptr), size(0)
{
    //std::cout << "calling constructor" << std::endl;
    size = get_len(string);

    str = new char[size];
    
    for (std::size_t i = 0; i < size; i++){
        str[i] = string[i];
    }
}

MyString::MyString(const std::string &string)
    : str(nullptr), size(string.length())
{
    str = new char[size];
    for (std::size_t i = 0; i < size; i++) {
        str[i] = string[i];
    }

}

MyString::MyString(const MyString &other){
    //std::cout << "calling copy constructor" << std::endl;
    size = other.size;
    str = new char[size];

    for (std::size_t i = 0; i < size; i++) {
        str[i] = other.str[i];
    }
}

MyString::MyString(MyString &&other) noexcept
    : str(other.str), size(other.size)
{
    //std::cout << "calling move constructor" << std::endl;
    other.str = nullptr;
    other.size = 0;
}

MyString::~MyString() {
    delete str;
}

std::ostream &operator<<(std::ostream &os, const MyString &obj) {
    os << (obj.str ? obj.str : "");
    return os;
}

MyString &MyString::operator=(const MyString &other) {
    //std::cout << "calling copy constructor by assignment operator" << std::endl;
    if (this == &other) {
        return *this;
    }

    if (this->str != nullptr) {
        delete [] str;
    }

    size = other.size;
    str = new char[size];
    
    for (std::size_t i = 0; i < size; i++) {
        str[i] = other.str[i];
    }

    return *this;
}

MyString &MyString::operator=(MyString &&other) {
    //std::cout << "calling move constructor by assignment operator" << std::endl;
    if (this == &other) {
        return *this;
    }

    if (this->str != nullptr) {
        delete [] str;
    }

    size = other.size;
    str = other.str;

    other.str = nullptr;

    return *this;
}

MyString MyString::operator[](std::pair<std::size_t, std::size_t> range) const {
    if (range.second == -1) {range.second = size;}
    if (range.first >= size || range.second > size || range.first > range.second) {
        throw std::out_of_range("Index fora dos limites");
    }

    std::size_t len = range.second - range.first;
    char *slice = new char[len + 1];
    slice[len] = '\0';
    std::strncpy(slice, str + range.first, len);

    MyString result(slice);
    delete [] slice;
    return result;
}

MyString operator+(const MyString &lhs, const MyString &rhs){
    size_t new_size = lhs.size + rhs.size;

    char* buff = new char[new_size + 1];
    buff[new_size+1] = '\0';

    std::strncpy(buff, lhs.str, lhs.size);
    std::strcat(buff, rhs.str);

    MyString temp(buff);
    delete [] buff;
    return temp;
}

MyString &MyString::operator+=(const char* string) {
    std::size_t newSize = size + get_len(string);
    char* newStr = new char[newSize + 1];

    if (str != nullptr) {
        std::strcpy(newStr, str);
    }
    std::strcat(newStr, string);

    delete [] str;
    this->str = newStr;
    this->size = newSize;

    return *this;
}

MyString &MyString::operator+=(const char caracter) {
    char* newStr = new char[size + 2]; // um espaço para o \0
    newStr[size + 1] = '\0';

    if (str != nullptr) {
        std::strcpy(newStr, str);
    }

    newStr[size] = caracter;
    
    delete [] str;
    this->str = newStr;
    this->size += 1;

    return *this;
}

bool MyString::operator==(const char *string) const {
    if (size != get_len(string)) {
        return false;
    }
    for (std::size_t i = 0; i < size; i++) {
        if (!(str[i] == string[i])) {
            return false;
        }
    }

    return true;
}

// private methods
std::size_t MyString::get_len(const char* string) const {
    std::size_t size = 0;
    while (string[size] != '\0') {
        size++;
    }

    return size;
}

std::size_t MyString::find_substring(const char* substring, std::pair<int, int> range) const {
    std::size_t substring_len = get_len(substring);

    if (substring_len == 0) {
        return 0;
    }

    // dita os ranges
    std::size_t start = range.first;
    std::size_t end = ((range.second == -1) ? size : range.second);

    for (std::size_t i = start; i <= end - substring_len; i++) {
        /*
        Itera até o limite onde é POSSÍVEL ter a substring.

        Por exemplo, caso 'size' for 10 e 'len' for 4, temos que deixar esse espaço
        de quatro itens (6) para não passar do tamanho da string (pois tem outro loop interno abaixo).
        */
    
        std::size_t j = 0;
        while (j < substring_len && str[i + j] == substring[j]) {
            /*
            Irá comparar uma parte do str do tamanho 'len' e a subtring

            Por exemplo, se i = 2 e a substring é "abc", verificamos se:
            str[2] == substring[0]
            str[3] == substring[1]
            str[4] == substring[2]

            Isso varia com o 'len', tamanho da substring
            */
            j++;
        }
        if (j == substring_len) {
            return i;
        }
    }
    return std::string::npos;
}

// member methods
MyString MyString::capitalize() {
    MyString temp (*this);
    if (str[0] >= 97 && str[0] <= 122) {
        temp.str[0] = str[0] - 32; // é a distância de uma letra minúscula e maiúscula no ascii
    }

    return temp;
}

bool MyString::isAlpha() const noexcept {
    for (std::size_t i = 0; i < size; i++) {
        if (!((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))) { // vê se está no range das minúsculas e das maiúsculas
            return false;
        }
    }
    return true;
}

bool MyString::isNumeric() const noexcept {
    for (std::size_t i = 0; i < size; i++) {
        if (!(str[i] >= 48 && str[i] <= 57)) {
            return false;
        }
    }
    return true;
}

bool MyString::isAlphaNum() const noexcept {
    for (std::size_t i = 0; i < size; i++) {
        if (!((str[i] >= 48 && str[i] <= 57) || ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)))) {
            return false;
        }
    }
    return true;
}

MyString MyString::toLower() const noexcept {
    if (this->isNumeric()) {
        return *this;
    }

    MyString temp("");

    for (std::size_t i = 0; i < size; i++) {
        if ((str[i] >= 65 && str[i] <= 90)) { // se é uma letra maiúscula
            temp += (str[i] + 32);
        }
        else {
            temp += str[i];
        }
    }

    return temp;
}

MyString MyString::toUpper() const noexcept {
    if (this->isNumeric()) {
        return *this;
    }

    MyString temp("");

    for (std::size_t i = 0; i < size; i++) {
        if ((str[i] >= 97 && str[i] <= 122)) { // se é uma letra minúscula
            temp += (str[i] - 32);
        }
        else {
            temp += str[i];
        }
    }

    return temp;
}   

void MyString::clear() noexcept {
    delete [] str;

    size = 0;
    str = new char[1];
    str[0] = '\0';
}

MyString MyString::trim() const noexcept {
    std::size_t start = 0;
    std::size_t end = size;

    // encontrar o primeiro caractere sem ser espaço
    while (start < size && str[start] == ' ') {
        ++start;
    }

    // se a string estiver toda composta por espaços
    if (start == size) {
        return MyString(""); 
    }

    // encontrar o último caractere sem ser espaço
    while (end > start && str[end - 1] == ' ') {
        --end;
    }

    MyString temp("");
    for (std::size_t i = start; i < end; ++i) {
        temp += str[i];
    }

    return temp;
}

std::vector<MyString> MyString::split(const char separator) const {
    std::vector<char> temp;
    std::vector<MyString> result;

    for (std::size_t i = 0; i <= size; i++){
        if (str[i] == separator || str[i] == '\0') {
            temp.push_back('\0');
            result.emplace_back(temp.data()); // já monta dentro do vetor

            temp.clear();
            continue;
        }

        else {
            temp.push_back(str[i]);
        }
    }

    return result;
}

std::vector<MyString> MyString::split(const char* separator) const {
    std::vector<std::size_t> indexes = this->findAll(separator);
    MyString temp("");
    std::vector<MyString> result;

    for (std::size_t i = 0; i < size; i++) {
        if (contains<std::size_t>(i, indexes)) {
            result.push_back(temp);
            temp.clear();
            i += get_len(separator); // pula o separator
        }
        temp += str[i];
    }

    if (!temp.isEmpty()) {
        result.push_back(temp);
    }

    return result;
}

std::size_t MyString::find(const char* substring) const noexcept {
    if (str == nullptr || substring == nullptr) {
        return -1;
    }

    return find_substring(substring, {0, -1}); // vai retornar a primeira ocorrência desde o início
}

std::vector<std::size_t> MyString::findAll(const char *substring) const noexcept {
    if (str == nullptr || substring == nullptr) {
        return std::vector<std::size_t>(); // Verificação de ponteiros nulos
    }

    std::vector<std::size_t> indexes;

    std::size_t index = 0;
    std::size_t new_start = 0;
    while (index != std::string::npos) {
        index = find_substring(substring, {new_start, -1});
        indexes.push_back(index);
        new_start = index + 1;
    }

    indexes.pop_back();
    return indexes;
}

MyString MyString::replace(const char *origin, const char *dest) const noexcept {
    std::vector<std::size_t> indexes = this->findAll(origin);

    std::size_t origin_len = get_len(origin);
    std::size_t dest_len = get_len(dest);
    std::size_t newSize = size + (dest_len - origin_len) * indexes.size();

    char* newStr = new char[newSize + 1];
    
    std::size_t newStr_index = 0;
    std::size_t str_index = 0;
    
    for (std::size_t k = 0; k < indexes.size(); k++) {
        while (str_index < static_cast<std::size_t>(indexes[k])) {
            newStr[newStr_index++] = str[str_index++]; // Enquanto não chegar no index 'k' na lista, ele irá adicionar os caracteres da string original.
        }

        for (std::size_t c = 0; c < dest_len; c++) {
            newStr[newStr_index++] = dest[c]; // Vai adicionando os caracteres da string de destino
        }

        str_index += origin_len; // move, também, o indíce da string original, para ela não ficar para trás
    }

    while (str_index < size) {
        newStr[newStr_index++] = str[str_index++]; // adiciona o restante dos caracteres
    }

    newStr[newSize] = '\0';
    MyString temp(newStr);
    delete [] newStr;

    return temp;
}


MyString MyString::format(std::initializer_list<const char*> values) const {
    std::vector<MyString> parts = this->split("{}");

    if (values.size() != this->findAll("{}").size()) {
        throw std::invalid_argument("Insufficient or many arguments");
    }

    MyString result;
    auto value_it = values.begin();

    for (std::size_t i = 0; i < parts.size(); i++) {
        result += parts[i];
        if (value_it != values.end()) {
            result += *value_it; // adiciona o próximo valor na lista
            ++value_it; // next
        }
    }

    return result;
}