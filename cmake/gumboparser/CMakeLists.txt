cmake_minimum_required(VERSION 3.14)
project(gumboparser)

add_compile_options("-fPIC")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
        gumbo
        GIT_REPOSITORY "https://github.com/geoffroyvergne/gumbo-parser"
        GIT_TAG "v0.11.0-cmake"
        #GIT_BRANCH "master"
)


FetchContent_MakeAvailable(gumbo)

add_executable(gumboparser src/gumboparser.cpp)
#add_executable(gumboparser src/test-gumbo.cpp)

target_link_libraries(gumboparser gumbo)
