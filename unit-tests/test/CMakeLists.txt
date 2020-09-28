set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
set(SOURCES ${TEST_SOURCES})

include(FetchContent)

FetchContent_Declare(
        gtest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG "release-1.10.0"
        #GIT_TAG "master"
        #SOURCE_DIR googletest
)

FetchContent_MakeAvailable(gtest)

add_executable(${BINARY} ${TEST_SOURCES})
add_test(NAME ${BINARY} COMMAND ${BINARY})

#add_executable(google-test src/google-test.cpp)

#target_link_libraries(${BINARY} PUBLIC gtest)

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)