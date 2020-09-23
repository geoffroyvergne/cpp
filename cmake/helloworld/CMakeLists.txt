cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(HelloWorld VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(helloworld helloworld.cpp)

install(TARGETS helloworld DESTINATION bin)

# Testing part
enable_testing()

add_test(NAME Runs COMMAND helloworld)

function(do_test target result)
  add_test(NAME Comp COMMAND ${target})
  set_tests_properties(Comp
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction(do_test)

do_test(helloworld "Hello World!")

# Cpack

include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
#set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
#set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)