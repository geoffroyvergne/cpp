## CPR

https://whoshuu.github.io/cpr/

mkdir build
conan install . -if build/
cmake . -B build/
cmake -DCMAKE_CXX_FLAGS="-static" . -B build/
cmake --build build/