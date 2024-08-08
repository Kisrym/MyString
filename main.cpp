#include <iostream>

#include "mystring.h"
#include <map>
#include <list>
#include <array>
#include <deque>

int main() {
    MyString teste("kaio é muito {}");
    
    MyString nome("     kaio santos      ");

    std::cout << nome.trim();
}