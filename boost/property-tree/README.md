
g++ -Wall -std=c++11 -o bin/propertytreetest main.cpp

cd <project/root>

mkdir build
conan install . -if build/
cmake . -B build/
cmake --build build/
