#include "Renderer.h"

#include <SDL.h>

#include <algorithm>
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

    /*
     * Make sure SDL uses nearest-neighbour filtering.
     *
     * This must be set BEFORE creating the renderer/framebuffer
     * texture.
     */
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    m_window = SDL_CreateWindow(
        "Mario NES",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (m_window == nullptr)
    {
        std::cerr
            << "SDL_CreateWindow failed: "
            << SDL_GetError()
            << '\n';

        return false;
    }

    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC |
        SDL_RENDERER_TARGETTEXTURE);

    if (m_renderer == nullptr)
    {
        std::cerr
            << "SDL_CreateRenderer failed: "
            << SDL_GetError()
            << '\n';

        shutdown();
        return false;
    }

    /*
     * Create our actual NES framebuffer.
     *
     * Everything in the game is rendered into this
     * exact 256x240 texture.
     */
    m_framebuffer = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        VIRTUAL_WIDTH,
        VIRTUAL_HEIGHT);

    if (m_framebuffer == nullptr)
    {
        std::cerr
            << "SDL_CreateTexture failed: "
            << SDL_GetError()
            << '\n';

        shutdown();
        return false;
    }

    /*
     * Explicitly use nearest-neighbour filtering.
     *
     * This is essential for pixel-art rendering.
     */
    SDL_SetTextureScaleMode(
        m_framebuffer,
        SDL_ScaleModeNearest);

    /*
     * The framebuffer itself should not blend with anything.
     */
    SDL_SetTextureBlendMode(
        m_framebuffer,
        SDL_BLENDMODE_NONE);

    return true;
}

void Renderer::shutdown()
{
    if (m_framebuffer != nullptr)
    {
        SDL_DestroyTexture(m_framebuffer);
        m_framebuffer = nullptr;
    }

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
    /*
     * Select the 256x240 framebuffer as the render target.
     */
    SDL_SetRenderTarget(m_renderer, m_framebuffer);

    /*
     * NES-style sky background.
     *
     * This color will eventually be replaced by the level/
     * palette system.
     */
    SDL_SetRenderDrawColor(
        m_renderer,
        92,
        148,
        252,
        255);

    SDL_RenderClear(m_renderer);
}

void Renderer::endFrame()
{
    presentVirtualFrame();
}

void Renderer::presentVirtualFrame()
{
    /*
     * Get the actual window dimensions.
     */
    int windowWidth = 0;
    int windowHeight = 0;

    SDL_GetWindowSize(
        m_window,
        &windowWidth,
        &windowHeight);

    /*
     * We want integer scaling.
     *
     * Example:
     *
     * 256x240 × 4 = 1024x960
     *
     * 256x240 × 3 = 768x720
     *
     * This prevents blurry/interpolated pixels.
     */
    const int scaleX =
        windowWidth / VIRTUAL_WIDTH;

    const int scaleY =
        windowHeight / VIRTUAL_HEIGHT;

    int scale = std::min(scaleX, scaleY);

    /*
     * The window should never be smaller than the
     * virtual framebuffer.
     *
     * In that case SDL will scale it down to fit.
     */
    if (scale < 1)
    {
        scale = 1;
    }

    int destinationWidth =
        VIRTUAL_WIDTH * scale;

    int destinationHeight =
        VIRTUAL_HEIGHT * scale;

    /*
     * If the window is smaller than 256x240,
     * allow fractional/downscaling as a fallback.
     */
    if (destinationWidth > windowWidth ||
        destinationHeight > windowHeight)
    {
        destinationWidth = windowWidth;
        destinationHeight =
            (windowWidth * VIRTUAL_HEIGHT)
            / VIRTUAL_WIDTH;
    }

    /*
     * Center the NES image in the window.
     */
    SDL_Rect destinationRect{};

    destinationRect.w = destinationWidth;
    destinationRect.h = destinationHeight;

    destinationRect.x =
        (windowWidth - destinationWidth) / 2;

    destinationRect.y =
        (windowHeight - destinationHeight) / 2;

    /*
     * Restore the default render target:
     * the actual window.
     */
    SDL_SetRenderTarget(m_renderer, nullptr);

    /*
     * Clear the window first.
     *
     * This produces black borders when the aspect ratio
     * doesn't match the NES framebuffer.
     */
    SDL_SetRenderDrawColor(
        m_renderer,
        0,
        0,
        0,
        255);

    SDL_RenderClear(m_renderer);

    /*
     * Copy the 256x240 framebuffer to the window.
     *
     * SDL_ScaleModeNearest guarantees pixel-perfect
     * nearest-neighbour scaling.
     */
    SDL_RenderCopy(
        m_renderer,
        m_framebuffer,
        nullptr,
        &destinationRect);

    SDL_RenderPresent(m_renderer);
}

void Renderer::drawPixel(
    int x,
    int y,
    std::uint8_t r,
    std::uint8_t g,
    std::uint8_t b)
{
    if (m_renderer == nullptr)
    {
        return;
    }

    /*
     * Ignore pixels outside the NES framebuffer.
     */
    if (x < 0 ||
        x >= VIRTUAL_WIDTH ||
        y < 0 ||
        y >= VIRTUAL_HEIGHT)
    {
        return;
    }

    SDL_SetRenderDrawColor(
        m_renderer,
        r,
        g,
        b,
        255);

    SDL_RenderDrawPoint(
        m_renderer,
        x,
        y);
}

void Renderer::drawRect(
    int x,
    int y,
    int width,
    int height,
    std::uint8_t r,
    std::uint8_t g,
    std::uint8_t b)
{
    if (m_renderer == nullptr)
    {
        return;
    }

    if (width <= 0 || height <= 0)
    {
        return;
    }

    SDL_SetRenderDrawColor(
        m_renderer,
        r,
        g,
        b,
        255);

    SDL_Rect rect{
        x,
        y,
        width,
        height
    };

    SDL_RenderFillRect(
        m_renderer,
        &rect);
}