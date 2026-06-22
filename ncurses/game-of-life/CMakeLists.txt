cmake_minimum_required(VERSION 3.10)

project(GameTutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.cpp)
set(SOURCES ${SOURCES})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR} include)

add_executable(main ${SOURCES})
target_link_libraries(main ${CURSES_LIBRARIES})