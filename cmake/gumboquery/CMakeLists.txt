cmake_minimum_required(VERSION 3.14)
project(gumboquery)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
        gumbo
        GIT_REPOSITORY "https://github.com/google/gumbo-parser"
        GIT_TAG "v0.10.1"
        #GIT_BRANCH "master"
)

FetchContent_MakeAvailable(gumbo)

add_executable(gumboquery src/gumboquery.cpp)
target_link_libraries(gumboquery gumbo)
