#include "Renderer.h"

#include <SDL.h>

#include <iostream>

Renderer::~Renderer()
{
    shutdown();
}

bool Renderer::initialize()
{
    if (m_renderer != nullptr)
    {
        return true;
    }

    m_window = SDL_CreateWindow(
        "Mario NES",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (m_window == nullptr)
    {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << '\n';
        return false;
    }

    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

    if (m_renderer == nullptr)
    {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
        return false;
    }

    // Render the game into a fixed NES-like 256x240 coordinate system.
    if (SDL_RenderSetLogicalSize(m_renderer, VIRTUAL_WIDTH, VIRTUAL_HEIGHT) != 0)
    {
        std::cerr << "SDL_RenderSetLogicalSize failed: " << SDL_GetError() << '\n';
        shutdown();
        return false;
    }

    // Pixel art must use nearest-neighbour filtering.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    return true;
}

void Renderer::shutdown()
{
    if (m_renderer != nullptr)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if (m_window != nullptr)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}

void Renderer::beginFrame()
{
    SDL_SetRenderDrawColor(m_renderer, 92, 148, 252, 255);
    SDL_RenderClear(m_renderer);
}

void Renderer::endFrame()
{
    SDL_RenderPresent(m_renderer);
}
