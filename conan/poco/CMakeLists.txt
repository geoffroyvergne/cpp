cmake_minimum_required(VERSION 3.16.3)
project(MD5Encrypter)

#if(CMAKE_VERSION VERSION_LESS 3.0.0)
#    include(CheckCXXCompilerFlag)
#    check_cxx_compiler_flag(-std=c++11 COMPILER_SUPPORTS_CXX11)
#    check_cxx_compiler_flag(-std=c++0x COMPILER_SUPPORTS_CXX0X)
#    if(COMPILER_SUPPORTS_CXX11)
#      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#    elseif(COMPILER_SUPPORTS_CXX0X)
#      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
#    endif()
#else()
#    SET(CMAKE_CXX_STANDARD 11)
#    SET(CMAKE_CXX_STANDARD_REQUIRED ON)
#endif()

#SET(CMAKE_CXX_STANDARD 11)
#SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#include(${CMAKE_BINARY_DIR}/conan.cmake)
#conan_cmake_run(CONANFILE conanfile.txt
#                BASIC_SETUP
#                BUILD missing)

add_executable(${PROJECT_NAME} md5.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
