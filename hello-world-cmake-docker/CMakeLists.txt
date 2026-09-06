cmake_minimum_required(VERSION 3.10)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(HelloWorld VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(helloworld main.cpp)
