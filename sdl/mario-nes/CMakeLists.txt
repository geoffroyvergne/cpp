cmake_minimum_required(VERSION 3.16)

project(mario_nes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(mario_nes

    src/main.cpp

    src/core/Game.cpp

    src/graphics/Renderer.cpp

    src/input/InputManager.cpp

    src/camera/Camera.cpp

    src/world/Level.cpp
    src/world/TileMap.cpp

    src/player/Player.cpp

    src/physics/Collision.cpp

    src/entities/Goomba.cpp
)

target_include_directories(mario_nes
    PRIVATE
        src
)

target_link_libraries(mario_nes
    PRIVATE
        SDL2::SDL2
)

# Copy assets next to the executable.
add_custom_command(
    TARGET mario_nes
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND}
        -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:mario_nes>/assets
)