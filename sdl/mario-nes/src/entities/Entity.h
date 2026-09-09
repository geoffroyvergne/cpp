#pragma once

class Camera;
class Renderer;
class TileMap;

class Entity
{
public:
    virtual ~Entity() = default;

    virtual void update(
        float deltaTime,
        const TileMap& tileMap) = 0;

    virtual void render(
        Renderer& renderer,
        const Camera& camera) const = 0;

    virtual bool isAlive() const = 0;

    virtual float x() const = 0;

    virtual float y() const = 0;
};