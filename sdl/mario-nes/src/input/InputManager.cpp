#include "InputManager.h"

#include <SDL.h>

#include <cstring>

void InputManager::update()
{
    m_quitRequested = false;

    // -------------------------------------------------
    // Process SDL events
    // -------------------------------------------------

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            m_quitRequested = true;
        }

        if (event.type == SDL_KEYDOWN &&
            event.key.repeat == 0)
        {
            const SDL_Scancode key =
                event.key.keysym.scancode;

            if (key == SDL_SCANCODE_ESCAPE ||
                key == SDL_SCANCODE_Q)
            {
                m_quitRequested = true;
            }
        }
    }

    // -------------------------------------------------
    // Save current state as previous state
    // -------------------------------------------------

    std::memcpy(
        m_previousKeys,
        m_currentKeys,
        sizeof(m_currentKeys));

    // -------------------------------------------------
    // Get new keyboard state
    // -------------------------------------------------

    const Uint8* keyboardState =
        SDL_GetKeyboardState(nullptr);

    std::memcpy(
        m_currentKeys,
        keyboardState,
        sizeof(m_currentKeys));

    // -------------------------------------------------
    // Game controls
    // -------------------------------------------------

    m_left =
        down(SDL_SCANCODE_LEFT) ||
        down(SDL_SCANCODE_A);

    m_right =
        down(SDL_SCANCODE_RIGHT) ||
        down(SDL_SCANCODE_D);

    m_jump =
        pressed(SDL_SCANCODE_SPACE) ||
        pressed(SDL_SCANCODE_Z) ||
        pressed(SDL_SCANCODE_X);
}

bool InputManager::quitRequested() const
{
    return m_quitRequested;
}

bool InputManager::down(
    SDL_Scancode key) const
{
    if (key < 0 ||
        key >= SDL_NUM_SCANCODES)
    {
        return false;
    }

    return m_currentKeys[key] != 0;
}

bool InputManager::pressed(
    SDL_Scancode key) const
{
    if (key < 0 ||
        key >= SDL_NUM_SCANCODES)
    {
        return false;
    }

    return m_currentKeys[key] != 0 &&
           m_previousKeys[key] == 0;
}

bool InputManager::released(
    SDL_Scancode key) const
{
    if (key < 0 ||
        key >= SDL_NUM_SCANCODES)
    {
        return false;
    }

    return m_currentKeys[key] == 0 &&
           m_previousKeys[key] != 0;
}