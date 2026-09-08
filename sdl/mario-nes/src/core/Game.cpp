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

    if (SDL_Init(
            SDL_INIT_VIDEO |
            SDL_INIT_AUDIO) != 0)
    {
        std::cerr
            << "SDL_Init failed: "
            << SDL_GetError()
            << '\n';

        return false;
    }

    if (!m_renderer.initialize())
    {
        SDL_Quit();
        return false;
    }

    /*
     * Initialize the world.
     */
    //m_tileMap.initialize();
    if (!m_tileMap.initialize(
        "assets/levels/world1-1.txt"))
    {
        SDL_Quit();
        return false;
    }

    /*
     * Mario starts in WORLD coordinates.
     */
    m_player.initialize(
        40.0f,
        192.0f);

    /*
     * Camera starts at the beginning
     * of the world.
     */
    m_camera.initialize(
        0.0f,
        0.0f);

    m_initialized = true;
    m_running = true;

    return true;
}

void Game::run()
{
    if (!m_initialized)
    {
        throw std::runtime_error(
            "Game::run() called before initialize()");
    }

    using Clock =
        std::chrono::steady_clock;

    auto previousTime =
        Clock::now();

    while (m_running)
    {
        const auto currentTime =
            Clock::now();

        const std::chrono::duration<float>
            elapsed =
                currentTime -
                previousTime;

        previousTime =
            currentTime;

        const float deltaTime =
            (elapsed.count() < 0.25f)
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

    if (m_input.quitRequested() ||
        m_input.isKeyPressed(
            SDL_SCANCODE_ESCAPE))
    {
        m_running = false;
    }
}

void Game::update(
    float deltaTime)
{
    /*
     * Update Mario in WORLD coordinates.
     */
    m_player.update(
        deltaTime,
        m_input,
        m_tileMap);

    /*
     * Then update the camera based
     * on Mario's WORLD position.
     */
    m_camera.update(
        m_player.x() +
            Player::WIDTH * 0.5f,

        m_player.y() +
            Player::HEIGHT * 0.5f,

        m_tileMap.worldWidth(),
        m_tileMap.worldHeight());
}

void Game::render()
{
    m_renderer.beginFrame();

    /*
     * Background.
     */
    m_renderer.drawRect(
        0,
        0,
        Renderer::VIRTUAL_WIDTH,
        Renderer::VIRTUAL_HEIGHT,
        92,
        148,
        252);

    /*
     * World rendered through camera.
     */
    m_tileMap.render(
        m_renderer,
        m_camera);

    /*
     * Mario rendered through camera.
     */
    m_player.render(
        m_renderer,
        m_camera);

    m_renderer.endFrame();
}