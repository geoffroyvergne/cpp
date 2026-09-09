#include "Player.h"

#include "camera/Camera.h"
#include "graphics/Renderer.h"
#include "input/InputManager.h"
#include "physics/Collision.h"
#include "world/TileMap.h"

#include <algorithm>

void Player::initialize(
    float x,
    float y)
{
    m_x = x;
    m_y = y;

    m_velocityX = 0.0f;
    m_velocityY = 0.0f;

    m_grounded = false;
    m_facingRight = true;
}

void Player::update(
    float deltaTime,
    const InputManager& input,
    const TileMap& tileMap)
{
    updateHorizontalMovement(
        deltaTime,
        input);

    updateVerticalMovement(
        deltaTime,
        input);

    moveAndCollideX(
        deltaTime,
        tileMap);

    moveAndCollideY(
        deltaTime,
        tileMap);
}

void Player::updateHorizontalMovement(
    float deltaTime,
    const InputManager& input)
{
    const bool movingLeft =
        input.left();

    const bool movingRight =
        input.right();

    if (movingLeft && !movingRight)
    {
        m_velocityX -=
            MOVE_ACCELERATION * deltaTime;

        m_facingRight = false;
    }
    else if (movingRight && !movingLeft)
    {
        m_velocityX +=
            MOVE_ACCELERATION * deltaTime;

        m_facingRight = true;
    }
    else
    {
        if (m_velocityX > 0.0f)
        {
            m_velocityX -=
                MOVE_DECELERATION * deltaTime;

            if (m_velocityX < 0.0f)
            {
                m_velocityX = 0.0f;
            }
        }
        else if (m_velocityX < 0.0f)
        {
            m_velocityX +=
                MOVE_DECELERATION * deltaTime;

            if (m_velocityX > 0.0f)
            {
                m_velocityX = 0.0f;
            }
        }
    }

    m_velocityX =
        std::clamp(
            m_velocityX,
            -MAX_HORIZONTAL_SPEED,
            MAX_HORIZONTAL_SPEED);
}

void Player::updateVerticalMovement(
    float deltaTime,
    const InputManager& input)
{
    if (input.jump() &&
        m_grounded)
    {
        m_velocityY =
            JUMP_VELOCITY;

        m_grounded = false;
    }

    m_velocityY +=
        GRAVITY * deltaTime;
}

void Player::moveAndCollideX(
    float deltaTime,
    const TileMap& tileMap)
{
    m_x +=
        m_velocityX * deltaTime;

    Collision::resolveHorizontal(
        m_x,
        m_y,
        WIDTH,
        HEIGHT,
        m_velocityX,
        tileMap);

    const float maxX =
        tileMap.worldWidth() -
        WIDTH;

    m_x =
        std::clamp(
            m_x,
            0.0f,
            std::max(0.0f, maxX));
}

void Player::moveAndCollideY(
    float deltaTime,
    const TileMap& tileMap)
{
    m_y +=
        m_velocityY * deltaTime;

    Collision::resolveVertical(
        m_x,
        m_y,
        WIDTH,
        HEIGHT,
        m_velocityY,
        m_grounded,
        tileMap);
}

void Player::bounce()
{
    m_velocityY =
        JUMP_VELOCITY * 0.65f;

    m_grounded = false;
}

void Player::render(
    Renderer& renderer,
    const Camera& camera) const
{
    const float screenX =
        m_x - camera.x();

    const float screenY =
        m_y - camera.y();

    // Hat / hair
    renderer.drawRect(
        screenX + 2.0f,
        screenY,
        8.0f,
        4.0f,
        200,
        30,
        30);

    // Face
    renderer.drawRect(
        screenX + 3.0f,
        screenY + 4.0f,
        7.0f,
        5.0f,
        255,
        190,
        140);

    // Body
    renderer.drawRect(
        screenX + 2.0f,
        screenY + 9.0f,
        8.0f,
        5.0f,
        200,
        30,
        30);

    // Left leg
    renderer.drawRect(
        screenX + 1.0f,
        screenY + 14.0f,
        5.0f,
        2.0f,
        40,
        70,
        180);

    // Right leg
    renderer.drawRect(
        screenX + 7.0f,
        screenY + 14.0f,
        5.0f,
        2.0f,
        40,
        70,
        180);
}