# C++ Singleton

## Simple singleton
g++ -std=c++11 simple-singleton.cpp -o bin/simple-singleton

## Thread safe singleton
g++ -std=c++11 tread-safe-singleton.cpp -o bin/tread-safe-singleton

## All together
g++ -std=c++11 simple-singleton.cpp tread-safe-singleton.cpp main.cpp -o bin/all-simple-singleton

./bin/all-simple-singleton

