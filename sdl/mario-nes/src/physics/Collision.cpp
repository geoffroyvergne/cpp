#include "Collision.h"

#include "world/TileMap.h"

#include <cmath>

AABB Collision::makeAABB(
    float x,
    float y,
    float width,
    float height)
{
    return AABB{
        x,
        y,
        x + width,
        y + height
    };
}

bool Collision::overlaps(
    const AABB& a,
    const AABB& b)
{
    return a.left < b.right &&
           a.right > b.left &&
           a.top < b.bottom &&
           a.bottom > b.top;
}

bool Collision::overlapsSolidTile(
    const AABB& box,
    const TileMap& tileMap)
{
    const float safeRight =
        box.right - EPSILON;

    const float safeBottom =
        box.bottom - EPSILON;

    const int firstTileX =
        static_cast<int>(
            std::floor(
                box.left /
                TileMap::TILE_SIZE));

    const int lastTileX =
        static_cast<int>(
            std::floor(
                safeRight /
                TileMap::TILE_SIZE));

    const int firstTileY =
        static_cast<int>(
            std::floor(
                box.top /
                TileMap::TILE_SIZE));

    const int lastTileY =
        static_cast<int>(
            std::floor(
                safeBottom /
                TileMap::TILE_SIZE));

    for (int tileY = firstTileY;
         tileY <= lastTileY;
         ++tileY)
    {
        for (int tileX = firstTileX;
             tileX <= lastTileX;
             ++tileX)
        {
            if (tileMap.isSolid(tileX, tileY))
            {
                return true;
            }
        }
    }

    return false;
}

bool Collision::resolveHorizontal(
    float& x,
    float y,
    float width,
    float height,
    float& velocityX,
    const TileMap& tileMap)
{
    if (velocityX == 0.0f)
    {
        return false;
    }

    const AABB box =
        makeAABB(x, y, width, height);

    if (!overlapsSolidTile(box, tileMap))
    {
        return false;
    }

    if (velocityX > 0.0f)
    {
        /*
         * Moving right.
         *
         * Use the right edge minus EPSILON so that
         * an object exactly touching a tile boundary
         * is not considered inside the next tile.
         */
        const float right =
            box.right - EPSILON;

        const int tileX =
            static_cast<int>(
                std::floor(
                    right /
                    TileMap::TILE_SIZE));

        const int firstTileY =
            static_cast<int>(
                std::floor(
                    box.top /
                    TileMap::TILE_SIZE));

        const int lastTileY =
            static_cast<int>(
                std::floor(
                    (box.bottom - EPSILON) /
                    TileMap::TILE_SIZE));

        for (int tileY = firstTileY;
             tileY <= lastTileY;
             ++tileY)
        {
            if (tileMap.isSolid(tileX, tileY))
            {
                x =
                    tileX *
                    TileMap::TILE_SIZE -
                    width;

                velocityX = 0.0f;

                return true;
            }
        }
    }
    else
    {
        /*
         * Moving left.
         *
         * The left edge determines the tile we
         * collided with.
         */
        const int tileX =
            static_cast<int>(
                std::floor(
                    box.left /
                    TileMap::TILE_SIZE));

        const int firstTileY =
            static_cast<int>(
                std::floor(
                    box.top /
                    TileMap::TILE_SIZE));

        const int lastTileY =
            static_cast<int>(
                std::floor(
                    (box.bottom - EPSILON) /
                    TileMap::TILE_SIZE));

        for (int tileY = firstTileY;
             tileY <= lastTileY;
             ++tileY)
        {
            if (tileMap.isSolid(tileX, tileY))
            {
                x =
                    (tileX + 1) *
                    TileMap::TILE_SIZE;

                velocityX = 0.0f;

                return true;
            }
        }
    }

    return false;
}

bool Collision::resolveVertical(
    float x,
    float& y,
    float width,
    float height,
    float& velocityY,
    bool& grounded,
    const TileMap& tileMap)
{
    grounded = false;

    const AABB box =
        makeAABB(x, y, width, height);

    if (!overlapsSolidTile(box, tileMap))
    {
        return false;
    }

    if (velocityY > 0.0f)
    {
        /*
         * Moving down.
         *
         * The bottom edge determines the tile
         * containing the collision.
         */
        const float bottom =
            box.bottom - EPSILON;

        const int tileY =
            static_cast<int>(
                std::floor(
                    bottom /
                    TileMap::TILE_SIZE));

        const int firstTileX =
            static_cast<int>(
                std::floor(
                    box.left /
                    TileMap::TILE_SIZE));

        const int lastTileX =
            static_cast<int>(
                std::floor(
                    (box.right - EPSILON) /
                    TileMap::TILE_SIZE));

        for (int tileX = firstTileX;
             tileX <= lastTileX;
             ++tileX)
        {
            if (tileMap.isSolid(tileX, tileY))
            {
                y =
                    tileY *
                    TileMap::TILE_SIZE -
                    height;

                velocityY = 0.0f;
                grounded = true;

                return true;
            }
        }
    }
    else if (velocityY < 0.0f)
    {
        /*
         * Moving up.
         *
         * The top edge determines the tile
         * containing the collision.
         */
        const int tileY =
            static_cast<int>(
                std::floor(
                    box.top /
                    TileMap::TILE_SIZE));

        const int firstTileX =
            static_cast<int>(
                std::floor(
                    box.left /
                    TileMap::TILE_SIZE));

        const int lastTileX =
            static_cast<int>(
                std::floor(
                    (box.right - EPSILON) /
                    TileMap::TILE_SIZE));

        for (int tileX = firstTileX;
             tileX <= lastTileX;
             ++tileX)
        {
            if (tileMap.isSolid(tileX, tileY))
            {
                y =
                    (tileY + 1) *
                    TileMap::TILE_SIZE;

                velocityY = 0.0f;

                return true;
            }
        }
    }

    return false;
}