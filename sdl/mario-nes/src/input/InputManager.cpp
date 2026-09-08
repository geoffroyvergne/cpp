#include "InputManager.h"

#include <algorithm>

void InputManager::update()
{
    m_previousKeys = m_currentKeys;

    SDL_Event event{};

    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_quitRequested = true;
            break;

        default:
            break;
        }
    }

    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    for (std::size_t i = 0; i < KEY_COUNT; ++i)
    {
        m_currentKeys[i] = keyboardState[i] != 0;
    }
}

bool InputManager::isKeyDown(SDL_Scancode key) const
{
    return m_currentKeys[static_cast<std::size_t>(key)];
}

bool InputManager::isKeyPressed(SDL_Scancode key) const
{
    const std::size_t index = static_cast<std::size_t>(key);
    return m_currentKeys[index] && !m_previousKeys[index];
}

bool InputManager::isKeyReleased(SDL_Scancode key) const
{
    const std::size_t index = static_cast<std::size_t>(key);
    return !m_currentKeys[index] && m_previousKeys[index];
}
