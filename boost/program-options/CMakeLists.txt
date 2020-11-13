cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(program-options VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package( Boost REQUIRED program_options )

if(Boost_FOUND)
    add_executable( ${PROJECT_NAME} main.cpp )
    target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES} )
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
