#include "Game.h"

#include <SDL.h>

#include <chrono>
#include <iostream>
#include <stdexcept>

Game::~Game()
{
    shutdown();
}

bool Game::initialize()
{
    if (m_initialized)
    {
        return true;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << '\n';
        return false;
    }

    if (!m_renderer.initialize())
    {
        SDL_Quit();
        return false;
    }

    m_initialized = true;
    m_running = true;

    return true;
}

void Game::run()
{
    if (!m_initialized)
    {
        throw std::runtime_error("Game::run() called before initialize()");
    }

    using Clock = std::chrono::steady_clock;

    auto previousTime = Clock::now();

    while (m_running)
    {
        const auto currentTime = Clock::now();
        const std::chrono::duration<float> elapsed = currentTime - previousTime;
        previousTime = currentTime;

        // Clamp a long pause/debug break so the game does not make a huge
        // simulation step when execution resumes.
        const float deltaTime = (elapsed.count() < 0.25f)
            ? elapsed.count()
            : 0.25f;

        processInput();
        update(deltaTime);
        render();
    }
}

void Game::shutdown()
{
    if (!m_initialized)
    {
        return;
    }

    m_renderer.shutdown();
    SDL_Quit();

    m_initialized = false;
    m_running = false;
}

void Game::processInput()
{
    m_input.update();

    if (m_input.quitRequested() || m_input.isKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        m_running = false;
    }
}

void Game::update(float deltaTime)
{
    (void)deltaTime;

    // Future gameplay systems will be updated here:
    // - player
    // - physics
    // - collision
    // - enemies
    // - level
    // - camera
}

void Game::render()
{
    m_renderer.beginFrame();

    // Step 1/2 intentionally renders only a background.
    // The tile map and Mario sprite will be added in later steps.

    m_renderer.endFrame();
}
