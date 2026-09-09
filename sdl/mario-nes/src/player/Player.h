#pragma once

class Camera;
class InputManager;
class Renderer;
class TileMap;

class Player
{
public:
    static constexpr float WIDTH = 12.0f;
    static constexpr float HEIGHT = 16.0f;

    Player() = default;

    void initialize(
        float x,
        float y);

    void update(
        float deltaTime,
        const InputManager& input,
        const TileMap& tileMap);

    void render(
        Renderer& renderer,
        const Camera& camera) const;

    void bounce();

    float x() const
    {
        return m_x;
    }

    float y() const
    {
        return m_y;
    }

    float velocityX() const
    {
        return m_velocityX;
    }

    float velocityY() const
    {
        return m_velocityY;
    }

    bool isGrounded() const
    {
        return m_grounded;
    }

private:
    void updateHorizontalMovement(
        float deltaTime,
        const InputManager& input);

    void updateVerticalMovement(
        float deltaTime,
        const InputManager& input);

    void moveAndCollideX(
        float deltaTime,
        const TileMap& tileMap);

    void moveAndCollideY(
        float deltaTime,
        const TileMap& tileMap);

private:
    float m_x{0.0f};
    float m_y{0.0f};

    float m_velocityX{0.0f};
    float m_velocityY{0.0f};

    bool m_grounded{false};
    bool m_facingRight{true};

    static constexpr float MOVE_ACCELERATION = 600.0f;
    static constexpr float MOVE_DECELERATION = 800.0f;
    static constexpr float MAX_HORIZONTAL_SPEED = 90.0f;

    static constexpr float GRAVITY = 700.0f;
    static constexpr float JUMP_VELOCITY = -245.0f;
};