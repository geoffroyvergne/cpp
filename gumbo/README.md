# gumbo-query

https://github.com/lazytiger/gumbo-query

# gumbo-parser

https://github.com/google/gumbo-parser

g++ -std=c++11 src/gumbo-parser-test.cpp -o bin/gumbo-parser-test `pkg-config --cflags --libs gumbo` && ./bin/gumbo-parser-test

g++ -std=c++11 gumbo-parser-test-2.cpp -o bin/gumbo-parser-test-2 `pkg-config --cflags --libs gumbo` && ./bin/gumbo-parser-test-2

## cmake

cd <project/root>
cmake -S . -B build/

cmake --build build/

