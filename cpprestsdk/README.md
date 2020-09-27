# CppRestSdk

https://github.com/microsoft/cpprestsdk

https://gist.github.com/SeanCline/6005128

brew install cpprestsdk
vcpkg install cpprestsdk 

cd <project/root>

mkdir build
conan install . -if build/
cmake . -B build/
cmake --build build/

./build/bin/cpp-rest-sdk-test 
