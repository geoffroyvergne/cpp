cmake_minimum_required(VERSION 3.10)

project(VideoPlayer VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.cpp)
set(SOURCES ${SOURCES})

find_package(PkgConfig REQUIRED)

pkg_check_modules(FFMPEG REQUIRED
    libavformat
    libavcodec
    libavutil
    libswscale
)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR} ${FFMPEG_INCLUDE_DIRS} include)

link_directories(
    ${FFMPEG_LIBRARY_DIRS}
    ${CURSES_LIBRARY_DIRS}
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CURSES_LIBRARIES} ${FFMPEG_LIBRARIES})