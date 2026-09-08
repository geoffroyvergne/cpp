#pragma once

class TileMap;

struct AABB
{
    float left{0.0f};
    float top{0.0f};
    float right{0.0f};
    float bottom{0.0f};
};

class Collision
{
public:
    static constexpr float EPSILON = 0.01f;

    static AABB makeAABB(
        float x,
        float y,
        float width,
        float height);

    static bool overlaps(
        const AABB& a,
        const AABB& b);

    static bool overlapsSolidTile(
        const AABB& box,
        const TileMap& tileMap);

    static bool resolveHorizontal(
        float& x,
        float y,
        float width,
        float height,
        float& velocityX,
        const TileMap& tileMap);

    static bool resolveVertical(
        float x,
        float& y,
        float width,
        float height,
        float& velocityY,
        bool& grounded,
        const TileMap& tileMap);
};