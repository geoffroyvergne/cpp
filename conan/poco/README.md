# conan podo md5

https://github.com/conan-io/examples/tree/master/libraries/poco/md5

mkdir build && cd build
conan install ..
cmake ..
cmake --build .

cd <project/root>

mkdir build
conan install . -if build/
cmake . -B build/
cmake --build build/

./build/bin/md5
