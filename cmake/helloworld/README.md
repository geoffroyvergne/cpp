# Basic cmake project

mkdir bin
cd bin

## build
cmake ..
cmake --build .

## install

make install
cmake install ./
cmake --install ./ --prefix app

cd <project/root>

mkdir build
cmake . -B build/
cmake --build build/

## test
ctest

## Package
cpack
make package