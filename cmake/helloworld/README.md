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

## test
ctest

## Package
cpack
make package