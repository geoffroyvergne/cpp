# boost program options ini

mkdir build
conan install . -if build/
cmake . -B build/
cmake --build build/
