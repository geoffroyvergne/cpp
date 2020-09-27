# google test

https://github.com/google/googletest
https://github.com/google/googletest/blob/master/googletest/README.md

cd <project/root>
cmake -S . -B build/

cmake --build build/

cmake -DCMAKE_C_COMPILER=/usr/bin/gcc --build build/
cmake -DCMAKE_CXX_COMPILER=/usr/bin/g++ --build build/
cmake -DCMAKE_CXX_COMPILER=clang++ --build build/