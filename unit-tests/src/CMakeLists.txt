set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES})

add_executable(${BINARY}_bin ${SOURCES})
#add_executable(${PROJECT_NAME} src/main.cpp)
add_library(${BINARY}_lib STATIC ${SOURCES})

install(TARGETS ${BINARY}_bin DESTINATION bin)
