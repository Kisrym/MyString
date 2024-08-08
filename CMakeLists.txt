cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(include)

set(SOURCE_FILES 
    src/mystring.cpp
    include/mystring.h
    include/mystringiterator.h
)

add_executable(main ${SOURCE_FILES} main.cpp)

target_compile_options(main PRIVATE -Wall)
