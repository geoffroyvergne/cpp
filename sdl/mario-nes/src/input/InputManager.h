#pragma once

#include <SDL.h>

class InputManager
{
public:
    InputManager() = default;

    void update();

    bool quitRequested() const;

    // -------------------------------------------------
    // Generic keyboard state
    // -------------------------------------------------

    bool down(SDL_Scancode key) const;

    bool pressed(SDL_Scancode key) const;

    bool released(SDL_Scancode key) const;

    // -------------------------------------------------
    // Game controls
    // -------------------------------------------------

    bool left() const
    {
        return m_left;
    }

    bool right() const
    {
        return m_right;
    }

    bool jump() const
    {
        return m_jump;
    }

private:
    static constexpr int KEY_COUNT =
        SDL_NUM_SCANCODES;

    bool m_quitRequested{false};

    // Current keyboard state.
    Uint8 m_currentKeys[KEY_COUNT]{};

    // Keyboard state from the previous frame.
    Uint8 m_previousKeys[KEY_COUNT]{};

    // Convenient game-specific states.
    bool m_left{false};
    bool m_right{false};
    bool m_jump{false};
};