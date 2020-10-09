# Basic cmake project

https://cmake.org/cmake/help/v3.18/guide/tutorial/index.html

https://github.com/Kitware/CMake/tree/master/Help/guide/tutorial

mkdir bin
cd bin

## Build
cmake ..
cmake --build .

## install

make install
cmake install ./
cmake --install ./ --prefix app

cd <project/root>
cmake -S . -B build/
cmake --build build/

## test
ctest

## Package
cpack
make package

