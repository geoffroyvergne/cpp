cmake_minimum_required(VERSION 3.9)
project(pistacheio)

#Pistache
include(FetchContent)

set(FETCHCONTENT_QUIET off)
get_filename_component(fc_base "../fc_base" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
set(FETCHCONTENT_BASE_DIR ${fc_base})

FetchContent_Declare(
        pistache
        GIT_REPOSITORY "https://github.com/pistacheio/pistache.git"
        GIT_TAG "master"
)

FetchContent_MakeAvailable(pistache)

add_executable(pistacheio main.cpp)
target_link_libraries(pistacheio PRIVATE pistache)
