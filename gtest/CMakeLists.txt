cmake_minimum_required(VERSION 2.8.12)
project(gtest-test)

#file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp *.h)
#file(GLOB SOURCES *.hpp *.cpp *.h)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.hpp src/*.cpp src/*.h)
set(SOURCES ${SOURCES})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(gtest-test ${CONAN_LIBS})
