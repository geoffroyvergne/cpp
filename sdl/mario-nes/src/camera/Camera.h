#pragma once

class Camera
{
public:
    static constexpr float VIEW_WIDTH = 256.0f;
    static constexpr float VIEW_HEIGHT = 240.0f;

    Camera() = default;

    void initialize(
        float x,
        float y);

    void update(
        float targetX,
        float targetY,
        float worldWidth,
        float worldHeight);

    float x() const
    {
        return m_x;
    }

    float y() const
    {
        return m_y;
    }

private:
    float m_x{0.0f};
    float m_y{0.0f};
};