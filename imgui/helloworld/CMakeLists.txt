cmake_minimum_required(VERSION 3.26.1)
project(imgui-test)

#set(BINARY ${CMAKE_PROJECT_NAME})
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.cpp)
set(SOURCES ${SOURCES})

include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} )
