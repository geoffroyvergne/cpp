cmake_minimum_required(VERSION 2.8.12)
project(GumboParserTest)

add_compile_options("-fPIC")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(gumbo-parser gumbo-parser-test.cpp)
target_link_libraries(gumbo-parser ${CONAN_LIBS})
