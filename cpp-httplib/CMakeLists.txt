cmake_minimum_required(VERSION 3.18.2)
project(cpp-httplib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(${PROJECT_NAME} main.cpp)
