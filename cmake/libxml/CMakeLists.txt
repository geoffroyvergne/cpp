cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(LibXml VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

# add the executable
add_executable(libxml simple-example.cpp)

target_link_libraries(libxml ${LIBXML2_LIBRARIES})