cmake_minimum_required(VERSION 3.9)
project(gumbotest)

find_package(gumbo REQUIRED)

add_executable(gumbotest gumbo-parser-test.cpp)
target_link_libraries(gumbotest PRIVATE gumbo)