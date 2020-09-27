cmake_minimum_required(VERSION 3.14)
project(google-test)

if (APPLE)
    set(CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
endif (APPLE)

#set(C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
        gtest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG "release-1.10.0"
        #GIT_TAG "master"
        #SOURCE_DIR googletest
)

FetchContent_MakeAvailable(gtest)

add_executable(google-test src/google-test.cpp)


target_link_libraries(google-test gtest)
