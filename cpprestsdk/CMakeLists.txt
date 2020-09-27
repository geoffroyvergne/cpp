cmake_minimum_required(VERSION 2.8.12)
project(cpp-rest-sdk-test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#add_executable(boost libnghttp2 main.cpp)
#target_link_libraries(boost libnghttp2 ${CONAN_LIBS})

add_executable(${PROJECT_NAME} main.cpp)
#target_link_libraries(${PROJECT_NAME} doctest range-v3)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})