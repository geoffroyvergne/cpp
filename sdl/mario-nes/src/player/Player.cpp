#include "Player.h"

#include "camera/Camera.h"
#include "graphics/Renderer.h"
#include "input/InputManager.h"
#include "physics/Collision.h"
#include "world/TileMap.h"

#include <SDL.h>

#include <algorithm>
#include <cmath>

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
    deltaTime =
        std::min(
            deltaTime,
            0.05f);

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
    const bool left =
        input.isKeyDown(SDL_SCANCODE_LEFT) ||
        input.isKeyDown(SDL_SCANCODE_A);

    const bool right =
        input.isKeyDown(SDL_SCANCODE_RIGHT) ||
        input.isKeyDown(SDL_SCANCODE_D);

    const float acceleration =
        MOVE_ACCELERATION *
        deltaTime;

    const float deceleration =
        MOVE_DECELERATION *
        deltaTime;

    // ---------------------------------------------------------
    // Move right
    // ---------------------------------------------------------
    if (right && !left)
    {
        m_facingRight = true;

        if (m_velocityX < 0.0f)
        {
            // Brake existing leftward velocity first.
            m_velocityX += deceleration;

            if (m_velocityX > 0.0f)
            {
                m_velocityX = 0.0f;
            }
        }
        else
        {
            // Accelerate to the right.
            m_velocityX += acceleration;
        }
    }

    // ---------------------------------------------------------
    // Move left
    // ---------------------------------------------------------
    else if (left && !right)
    {
        m_facingRight = false;

        if (m_velocityX > 0.0f)
        {
            // Brake existing rightward velocity first.
            m_velocityX -= deceleration;

            if (m_velocityX < 0.0f)
            {
                m_velocityX = 0.0f;
            }
        }
        else
        {
            // Accelerate to the left.
            m_velocityX -= acceleration;
        }
    }

    // ---------------------------------------------------------
    // No horizontal input.
    //
    // Mario keeps a small amount of momentum and gradually
    // comes to a stop.
    // ---------------------------------------------------------
    else
    {
        if (m_velocityX > 0.0f)
        {
            m_velocityX -= deceleration;

            if (m_velocityX < 0.0f)
            {
                m_velocityX = 0.0f;
            }
        }
        else if (m_velocityX < 0.0f)
        {
            m_velocityX += deceleration;

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
    const bool jumpPressed =
        input.isKeyPressed(SDL_SCANCODE_SPACE) ||
        input.isKeyPressed(SDL_SCANCODE_Z) ||
        input.isKeyPressed(SDL_SCANCODE_X);

    const bool jumpHeld =
        input.isKeyDown(SDL_SCANCODE_SPACE) ||
        input.isKeyDown(SDL_SCANCODE_Z) ||
        input.isKeyDown(SDL_SCANCODE_X);

    if (jumpPressed && m_grounded)
    {
        m_velocityY =
            JUMP_VELOCITY;

        m_grounded = false;
    }

    m_velocityY +=
        GRAVITY *
        deltaTime;

    // Short hop when the jump button is released early.
    if (!jumpHeld &&
        m_velocityY < -80.0f)
    {
        m_velocityY +=
            GRAVITY *
            1.5f *
            deltaTime;
    }

    m_velocityY =
        std::min(
            m_velocityY,
            300.0f);
}

void Player::moveAndCollideX(
    float deltaTime,
    const TileMap& tileMap)
{
    if (m_velocityX == 0.0f)
    {
        return;
    }

    m_x +=
        m_velocityX *
        deltaTime;

    const bool collided =
        Collision::resolveHorizontal(
            m_x,
            m_y,
            WIDTH,
            HEIGHT,
            m_velocityX,
            tileMap);

    // ---------------------------------------------------------
    // World boundaries
    // ---------------------------------------------------------

    const float worldWidth =
        tileMap.worldWidth();

    const float minX =
        0.0f;

    const float maxX =
        worldWidth - WIDTH;

    if (m_x < minX)
    {
        m_x = minX;
        m_velocityX = 0.0f;
    }

    if (m_x > maxX)
    {
        m_x = maxX;
        m_velocityX = 0.0f;
    }

    // Explicitly stop after a collision.
    if (collided)
    {
        m_velocityX = 0.0f;
    }
}

void Player::moveAndCollideY(
    float deltaTime,
    const TileMap& tileMap)
{
    m_y +=
        m_velocityY *
        deltaTime;

    Collision::resolveVertical(
        m_x,
        m_y,
        WIDTH,
        HEIGHT,
        m_velocityY,
        m_grounded,
        tileMap);
}

void Player::render(
    Renderer& renderer,
    const Camera& camera) const
{
    const int x =
        static_cast<int>(
            std::round(
                m_x -
                camera.x()));

    const int y =
        static_cast<int>(
            std::round(
                m_y -
                camera.y()));

    // Hat
    renderer.drawRect(
        x + 2,
        y,
        9,
        3,
        220,
        30,
        30);

    // Face
    renderer.drawRect(
        x + 3,
        y + 3,
        7,
        5,
        245,
        180,
        130);

    // Shirt
    renderer.drawRect(
        x + 2,
        y + 8,
        9,
        5,
        220,
        30,
        30);

    // Overalls
    renderer.drawRect(
        x + 3,
        y + 7,
        7,
        7,
        30,
        70,
        190);

    // Feet
    renderer.drawRect(
        x,
        y + 14,
        5,
        2,
        90,
        45,
        25);

    renderer.drawRect(
        x + 7,
        y + 14,
        5,
        2,
        90,
        45,
        25);

    // Eye follows facing direction.
    const int eyeX =
        m_facingRight
            ? x + 8
            : x + 3;

    renderer.drawRect(
        eyeX,
        y + 4,
        2,
        2,
        20,
        20,
        20);
}