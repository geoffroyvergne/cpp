cmake_minimum_required(VERSION 3.20)

project(MarioNES
    VERSION 0.1.0
    DESCRIPTION "NES-style Mario game prototype"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)

add_executable(mario_nes
    src/main.cpp
    src/core/Game.cpp
    src/graphics/Renderer.cpp
    src/input/InputManager.cpp
)

target_include_directories(mario_nes PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(mario_nes PRIVATE PkgConfig::SDL2)

# Copy assets next to the executable for future steps.
add_custom_command(TARGET mario_nes POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:mario_nes>/assets
)
