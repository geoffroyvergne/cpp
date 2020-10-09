cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(program-options VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package( Boost 1.68.0 REQUIRED program_options )

if(Boost_FOUND)
    add_executable( ${PROJECT_NAME} simple-example.cpp )
    target_link_libraries( ${PROJECT_NAME} Boost::program_options )
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)