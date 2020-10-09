set(BINARY ${CMAKE_PROJECT_NAME}_src_bin)
set(LIB ${CMAKE_PROJECT_NAME}_lib)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)
set(SOURCES ${SOURCES})

add_executable(${BINARY} ${SOURCES})
#add_executable(${PROJECT_NAME} src/main.cpp)
add_library(${LIB} STATIC ${SOURCES})

install(TARGETS ${BINARY} DESTINATION bin)

add_custom_command(TARGET ${BINARY} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${BINARY}> ../bin/${BINARY})

#/Users/geoffroy.vergne/dev/github/cpp/unit-tests/build/bin/${BINARY}

