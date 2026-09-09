#pragma once

#include "entities/Entity.h"

class Goomba : public Entity
{
public:
    static constexpr float WIDTH = 14.0f;
    static constexpr float HEIGHT = 14.0f;

    Goomba(
        float x,
        float y);

    void update(
        float deltaTime,
        const TileMap& tileMap) override;

    void render(
        Renderer& renderer,
        const Camera& camera) const override;

    bool isAlive() const override;

    float x() const override;
    float y() const override;

    void stomp();

    bool isSquashed() const
    {
        return m_squashed;
    }

private:
    float m_x{0.0f};
    float m_y{0.0f};

    float m_velocityX{-30.0f};
    float m_velocityY{0.0f};

    bool m_alive{true};
    bool m_squashed{false};

    float m_squashedTimer{0.0f};

    static constexpr float GRAVITY = 700.0f;
    static constexpr float SQUASHED_DURATION = 0.35f;
};