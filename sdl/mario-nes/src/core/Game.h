#pragma once

#include "camera/Camera.h"
#include "entities/Entity.h"
#include "graphics/Renderer.h"
#include "input/InputManager.h"
#include "player/Player.h"
#include "world/Level.h"
#include "world/TileMap.h"

#include <memory>
#include <vector>

class Game
{
public:
    Game() = default;

    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    bool initialize();

    void run();

    void shutdown();

private:
    bool initializeLevel();

    void update(
        float deltaTime);

    void updateEntityCollisions();

    void render();

private:
    bool m_running{false};
    bool m_initialized{false};

    Renderer m_renderer;
    InputManager m_input;
    Camera m_camera;

    Level m_level;
    TileMap m_tileMap;
    Player m_player;

    std::vector<
        std::unique_ptr<Entity>>
        m_entities;
};