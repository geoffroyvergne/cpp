# easyhttpcpp

https://github.com/sony/easyhttpcpp
https://github.com/sony/easyhttpcpp/blob/master/samples/SimpleHttpClient/SimpleHttpClient.cpp


mkdir build
conan install . -if build/
cmake . -B build/
cmake -DCMAKE_CXX_FLAGS="-static" . -B build/
cmake --build build/
