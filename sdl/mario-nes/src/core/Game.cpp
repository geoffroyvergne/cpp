#include "Game.h"

#include "entities/Goomba.h"
#include "physics/Collision.h"

#include <SDL.h>

#include <iostream>
#include <memory>
#include <string>

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

    if (!initializeLevel())
    {
        m_renderer.shutdown();
        SDL_Quit();
        return false;
    }

    m_initialized = true;
    m_running = true;

    return true;
}

bool Game::initializeLevel()
{
    const std::string levelPath =
        "assets/levels/world1-1.txt";

    if (!m_level.loadFromFile(levelPath))
    {
        return false;
    }

    if (!m_tileMap.initialize(m_level))
    {
        return false;
    }

    if (m_level.hasPlayerSpawn())
    {
        m_player.initialize(
            m_level.playerSpawnX(),
            m_level.playerSpawnY());
    }
    else
    {
        std::cerr
            << "Warning: using fallback player spawn."
            << '\n';

        m_player.initialize(
            40.0f,
            192.0f);
    }

    m_entities.clear();

    for (const Level::GoombaSpawn& spawn :
         m_level.goombaSpawns())
    {
        auto goomba =
            std::make_unique<Goomba>(
                spawn.x,
                spawn.y);

        m_entities.push_back(
            std::move(goomba));
    }

    m_camera.initialize(
        0.0f,
        0.0f);

    m_camera.update(
        m_player.x(),
        m_player.y(),
        m_tileMap.worldWidth(),
        m_tileMap.worldHeight());

    return true;
}

void Game::run()
{
    if (!m_initialized)
    {
        std::cerr
            << "Warning: Game::run() called "
               "before Game::initialize()."
            << '\n';

        return;
    }

    Uint64 previousCounter =
        SDL_GetPerformanceCounter();

    const double frequency =
        static_cast<double>(
            SDL_GetPerformanceFrequency());

    while (m_running)
    {
        const Uint64 currentCounter =
            SDL_GetPerformanceCounter();

        const double deltaSeconds =
            static_cast<double>(
                currentCounter -
                previousCounter) /
            frequency;

        previousCounter =
            currentCounter;

        const float deltaTime =
            static_cast<float>(
                deltaSeconds);

        m_input.update();

        if (m_input.quitRequested())
        {
            m_running = false;
            break;
        }

        update(deltaTime);

        render();
    }
}

void Game::update(
    float deltaTime)
{
    m_player.update(
        deltaTime,
        m_input,
        m_tileMap);

    for (const std::unique_ptr<Entity>& entity :
         m_entities)
    {
        if (!entity)
        {
            continue;
        }

        entity->update(
            deltaTime,
            m_tileMap);
    }

    updateEntityCollisions();

    m_camera.update(
        m_player.x(),
        m_player.y(),
        m_tileMap.worldWidth(),
        m_tileMap.worldHeight());
}

void Game::updateEntityCollisions()
{
    const AABB playerBox =
        Collision::makeAABB(
            m_player.x(),
            m_player.y(),
            Player::WIDTH,
            Player::HEIGHT);

    for (const std::unique_ptr<Entity>& entity :
         m_entities)
    {
        if (!entity ||
            !entity->isAlive())
        {
            continue;
        }

        Goomba* goomba =
            dynamic_cast<Goomba*>(
                entity.get());

        if (goomba == nullptr ||
            goomba->isSquashed())
        {
            continue;
        }

        const AABB goombaBox =
            Collision::makeAABB(
                goomba->x(),
                goomba->y(),
                Goomba::WIDTH,
                Goomba::HEIGHT);

        if (!Collision::overlaps(
                playerBox,
                goombaBox))
        {
            continue;
        }

        const float playerBottom =
            m_player.y() +
            Player::HEIGHT;

        const float goombaTop =
            goomba->y();

        const bool falling =
            m_player.velocityY() > 0.0f;

        const bool landingOnTop =
            falling &&
            playerBottom <=
                goombaTop + 8.0f;

        if (landingOnTop)
        {
            goomba->stomp();
            m_player.bounce();
            continue;
        }

        // Side collision:
        // reset Mario to the level spawn.
        m_player.initialize(
            m_level.playerSpawnX(),
            m_level.playerSpawnY());

        m_camera.initialize(
            0.0f,
            0.0f);

        m_camera.update(
            m_player.x(),
            m_player.y(),
            m_tileMap.worldWidth(),
            m_tileMap.worldHeight());

        break;
    }
}

void Game::render()
{
    m_renderer.beginFrame();

    m_tileMap.render(
        m_renderer,
        m_camera);

    for (const std::unique_ptr<Entity>& entity :
         m_entities)
    {
        if (!entity ||
            !entity->isAlive())
        {
            continue;
        }

        entity->render(
            m_renderer,
            m_camera);
    }

    m_player.render(
        m_renderer,
        m_camera);

    m_renderer.endFrame();
}

void Game::shutdown()
{
    if (!m_initialized)
    {
        return;
    }

    m_running = false;

    m_entities.clear();

    m_renderer.shutdown();

    SDL_Quit();

    m_initialized = false;
}