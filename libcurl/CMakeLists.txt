cmake_minimum_required(VERSION 3.14)
project(libcurltest)

#if (APPLE)
#    set(CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
#endif (APPLE)

#set(C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_STANDARD_REQUIRED True)

#include(FetchContent)

#FetchContent_Declare(
#        curl
#        GIT_REPOSITORY "https://github.com/curl/curl.git"
#        GIT_TAG "curl-7_72_0"
        #GIT_TAG "master"
        #SOURCE_DIR googletest
#)

#FetchContent_MakeAvailable(curl)
#add_executable(curl url-get-test.cpp)
#target_link_libraries(libcurltest curl)

find_package( CURL )

if(CURL_FOUND)
    add_executable( ${PROJECT_NAME} main.cpp )
    target_link_libraries( ${PROJECT_NAME} CURL )
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)