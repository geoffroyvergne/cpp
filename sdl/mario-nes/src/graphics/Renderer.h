#pragma once

#include <cstdint>

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Window;

class Renderer
{
public:
    // Original NES PPU resolution.
    static constexpr int VIRTUAL_WIDTH = 256;
    static constexpr int VIRTUAL_HEIGHT = 240;

    // Initial desktop window size.
    static constexpr int WINDOW_WIDTH = 1024;
    static constexpr int WINDOW_HEIGHT = 960;

    Renderer() = default;
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    bool initialize();
    void shutdown();

    void beginFrame();
    void endFrame();

    // Drawing in NES virtual coordinates.
    void drawPixel(int x, int y, std::uint8_t r, std::uint8_t g, std::uint8_t b);
    void drawRect(
        int x,
        int y,
        int width,
        int height,
        std::uint8_t r,
        std::uint8_t g,
        std::uint8_t b);

    SDL_Renderer* nativeRenderer() const { return m_renderer; }
    SDL_Window* nativeWindow() const { return m_window; }

private:
    void presentVirtualFrame();

    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
    SDL_Texture* m_framebuffer{nullptr};
};