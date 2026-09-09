#include "Goomba.h"

#include "camera/Camera.h"
#include "graphics/Renderer.h"
#include "physics/Collision.h"
#include "world/TileMap.h"

Goomba::Goomba(
    float x,
    float y)
    : m_x(x),
      m_y(y)
{
}

void Goomba::update(
    float deltaTime,
    const TileMap& tileMap)
{
    if (!m_alive)
    {
        return;
    }

    // Squashed Goomba remains visible
    // for a short time before disappearing.
    if (m_squashed)
    {
        m_squashedTimer -= deltaTime;

        if (m_squashedTimer <= 0.0f)
        {
            m_alive = false;
        }

        return;
    }

    // Gravity.
    m_velocityY +=
        GRAVITY * deltaTime;

    // Horizontal movement and collision.
    const bool hitWall =
        Collision::resolveHorizontal(
            m_x,
            m_y,
            WIDTH,
            HEIGHT,
            m_velocityX,
            tileMap);

    if (hitWall)
    {
        // Reverse direction when hitting
        // a solid tile.
        m_velocityX =
            -m_velocityX;
    }

    // Vertical movement and collision.
    bool grounded = false;

    Collision::resolveVertical(
        m_x,
        m_y,
        WIDTH,
        HEIGHT,
        m_velocityY,
        grounded,
        tileMap);
}

void Goomba::render(
    Renderer& renderer,
    const Camera& camera) const
{
    if (!m_alive)
    {
        return;
    }

    const float screenX =
        m_x - camera.x();

    const float screenY =
        m_y - camera.y();

    // -------------------------------------------------
    // Squashed Goomba
    // -------------------------------------------------

    if (m_squashed)
    {
        renderer.drawRect(
            screenX,
            screenY + 8.0f,
            WIDTH,
            6.0f,
            139,
            69,
            19);

        return;
    }

    // -------------------------------------------------
    // Body
    // -------------------------------------------------

    renderer.drawRect(
        screenX + 1.0f,
        screenY + 4.0f,
        12.0f,
        10.0f,
        139,
        69,
        19);

    // -------------------------------------------------
    // Head
    // -------------------------------------------------

    renderer.drawRect(
        screenX + 2.0f,
        screenY + 2.0f,
        10.0f,
        7.0f,
        181,
        92,
        28);

    // -------------------------------------------------
    // Eyes
    // -------------------------------------------------

    renderer.drawRect(
        screenX + 4.0f,
        screenY + 4.0f,
        2.0f,
        2.0f,
        0,
        0,
        0);

    renderer.drawRect(
        screenX + 8.0f,
        screenY + 4.0f,
        2.0f,
        2.0f,
        0,
        0,
        0);

    // -------------------------------------------------
    // Left foot
    // -------------------------------------------------

    renderer.drawRect(
        screenX,
        screenY + 12.0f,
        6.0f,
        2.0f,
        100,
        50,
        15);

    // -------------------------------------------------
    // Right foot
    // -------------------------------------------------

    renderer.drawRect(
        screenX + 8.0f,
        screenY + 12.0f,
        6.0f,
        2.0f,
        100,
        50,
        15);
}

void Goomba::stomp()
{
    if (!m_alive ||
        m_squashed)
    {
        return;
    }

    m_squashed = true;

    m_squashedTimer =
        SQUASHED_DURATION;

    m_velocityX = 0.0f;
    m_velocityY = 0.0f;
}

bool Goomba::isAlive() const
{
    return m_alive;
}

float Goomba::x() const
{
    return m_x;
}

float Goomba::y() const
{
    return m_y;
}