#pragma once

#include <cstdint>

struct SDL_Renderer;
struct SDL_Window;

class Renderer
{
public:
    static constexpr int VIRTUAL_WIDTH = 256;
    static constexpr int VIRTUAL_HEIGHT = 240;

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

    SDL_Renderer* nativeRenderer() const { return m_renderer; }
    SDL_Window* nativeWindow() const { return m_window; }

private:
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
};
