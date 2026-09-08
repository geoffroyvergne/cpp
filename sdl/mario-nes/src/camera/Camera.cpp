#include "Camera.h"

#include <algorithm>
#include <cmath>

void Camera::initialize(
    float x,
    float y)
{
    m_x = x;
    m_y = y;
}

void Camera::update(
    float targetX,
    float targetY,
    float worldWidth,
    float worldHeight)
{
    // ---------------------------------------------------------
    // Horizontal scrolling
    //
    // Mario has a larger amount of space behind him and a
    // smaller amount of space in front of him.
    //
    // This makes the camera naturally encourage movement
    // toward the right, similar to a classic Mario level.
    // ---------------------------------------------------------

    constexpr float DEAD_ZONE_LEFT =
        80.0f;

    constexpr float DEAD_ZONE_RIGHT =
        176.0f;

    const float playerScreenX =
        targetX - m_x;

    // ---------------------------------------------------------
    // Mario is too far to the right.
    //
    // The camera MUST move right.
    // ---------------------------------------------------------
    if (playerScreenX > DEAD_ZONE_RIGHT)
    {
        m_x =
            targetX -
            DEAD_ZONE_RIGHT;
    }

    // ---------------------------------------------------------
    // Mario is too far to the left.
    //
    // We deliberately do NOT move the camera immediately.
    //
    // This is the important difference from a conventional
    // camera that always centers the player.
    //
    // Only when Mario goes sufficiently far back do we allow
    // the camera to follow him.
    // ---------------------------------------------------------
    else if (playerScreenX < DEAD_ZONE_LEFT)
    {
        m_x =
            targetX -
            DEAD_ZONE_LEFT;
    }

    // ---------------------------------------------------------
    // Vertical camera
    // ---------------------------------------------------------

    constexpr float DEAD_ZONE_TOP =
        96.0f;

    constexpr float DEAD_ZONE_BOTTOM =
        144.0f;

    const float playerScreenY =
        targetY - m_y;

    if (playerScreenY > DEAD_ZONE_BOTTOM)
    {
        m_y =
            targetY -
            DEAD_ZONE_BOTTOM;
    }
    else if (playerScreenY < DEAD_ZONE_TOP)
    {
        m_y =
            targetY -
            DEAD_ZONE_TOP;
    }

    // ---------------------------------------------------------
    // Clamp camera to world boundaries.
    // ---------------------------------------------------------

    const float maxX =
        std::max(
            0.0f,
            worldWidth -
                VIEW_WIDTH);

    const float maxY =
        std::max(
            0.0f,
            worldHeight -
                VIEW_HEIGHT);

    m_x =
        std::clamp(
            m_x,
            0.0f,
            maxX);

    m_y =
        std::clamp(
            m_y,
            0.0f,
            maxY);

    // ---------------------------------------------------------
    // Pixel-perfect scrolling.
    //
    // Never render the camera at a fractional pixel.
    // ---------------------------------------------------------

    m_x =
        std::floor(m_x);

    m_y =
        std::floor(m_y);
}