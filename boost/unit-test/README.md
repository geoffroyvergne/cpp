# Boos.test

## simple
g++ -lboost_unit_test_framework -o bin/simple simple.cpp
./bin/simple --log_level=all

## test-module
g++ -lboost_unit_test_framework -o bin/test-module test-module/testMain.cpp test-module/hello.cpp test-module/test1.cpp
./bin/test-module --log_level=all

## test-class
g++ -lboost_unit_test_framework -o bin/test-class test-class/test-class-main.cpp test-class/test-class.cpp
./bin/test-class --log_level=all

