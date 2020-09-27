cmake_minimum_required(VERSION 3.14)
project(doctestmain)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
        DocTest
        GIT_REPOSITORY "https://github.com/onqtam/doctest"
        GIT_TAG "2.4.0"
)

FetchContent_MakeAvailable(DocTest)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} doctest)


#find_package(doctest REQUIRED)

#add_executable(gumbotest src/main.cpp)
#target_link_libraries(gumbotest PRIVATE doctest)