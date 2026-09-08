#pragma once

#include <SDL.h>

#include <array>
#include <cstdint>

class InputManager
{
public:
    void update();

    bool quitRequested() const { return m_quitRequested; }

    bool isKeyDown(SDL_Scancode key) const;
    bool isKeyPressed(SDL_Scancode key) const;
    bool isKeyReleased(SDL_Scancode key) const;

private:
    static constexpr std::size_t KEY_COUNT = SDL_NUM_SCANCODES;

    std::array<bool, KEY_COUNT> m_previousKeys{};
    std::array<bool, KEY_COUNT> m_currentKeys{};
    bool m_quitRequested{false};
};
