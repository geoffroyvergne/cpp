#pragma once

#include "graphics/Renderer.h"
#include "input/InputManager.h"

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
    void processInput();
    void update(float deltaTime);
    void render();

    bool m_running{false};
    bool m_initialized{false};

    Renderer m_renderer;
    InputManager m_input;
};
