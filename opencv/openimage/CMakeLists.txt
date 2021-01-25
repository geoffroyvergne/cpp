cmake_minimum_required(VERSION 2.8.12)
project(dispayimage)

#set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.cpp)
set(SOURCES ${SOURCES})

find_package( OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS} include)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
