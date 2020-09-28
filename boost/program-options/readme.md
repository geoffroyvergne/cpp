# boost program options

https://github.com/boostorg/program_options
https://www.boost.org/doc/libs/1_74_0/libs/program_options/example/first.cpp
https://github.com/boostorg/program_options/blob/develop/example/first.cpp

g++ -Wall -std=c++11 
g++ -o bin/simple-example simple-example.cpp -lboost_program_options

cd <project/root>

cmake -S . -B build/
cmake --build build/