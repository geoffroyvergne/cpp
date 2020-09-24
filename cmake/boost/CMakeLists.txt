cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Boost VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
#add_executable(boost boost.cpp)

#find_package(Boost 1.36.0)
#find_package(Boost REQUIRED COMPONENTS lambda) 

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED) 

if(Boost_FOUND)
    add_executable(boost boost.cpp) 
    target_link_libraries(boost Boost::boost)
endif()

install(TARGETS boost DESTINATION bin)
