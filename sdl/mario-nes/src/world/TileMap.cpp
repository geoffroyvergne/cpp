#include "TileMap.h"

#include "camera/Camera.h"
#include "graphics/Renderer.h"
#include "world/Level.h"

#include <algorithm>
#include <iostream>

namespace
{

constexpr char EMPTY = '.';
constexpr char GROUND = '#';
constexpr char BRICK = 'B';
constexpr char QUESTION = '?';

}

bool TileMap::initialize(
    const Level& level)
{
    m_width =
        level.width();

    m_height =
        level.height();

    if (m_width <= 0 ||
        m_height <= 0)
    {
        std::cerr
            << "Invalid level dimensions."
            << '\n';

        return false;
    }

    m_tiles.assign(
        m_width * m_height,
        TileType::Empty);

    for (int y = 0;
         y < m_height;
         ++y)
    {
        for (int x = 0;
             x < m_width;
             ++x)
        {
            m_tiles[
                y * m_width + x] =
                tileFromCharacter(
                    level.getTile(x, y));
        }
    }

    std::cout
        << "TileMap initialized: "
        << m_width
        << "x"
        << m_height
        << " tiles"
        << '\n';

    return true;
}

TileMap::TileType TileMap::getTile(
    int tileX,
    int tileY) const
{
    if (!isInside(
            tileX,
            tileY))
    {
        return TileType::Empty;
    }

    return m_tiles[
        tileY * m_width + tileX];
}

void TileMap::setTile(
    int tileX,
    int tileY,
    TileType type)
{
    if (!isInside(
            tileX,
            tileY))
    {
        return;
    }

    m_tiles[
        tileY * m_width + tileX] =
        type;
}

bool TileMap::isSolid(
    int tileX,
    int tileY) const
{
    switch (getTile(
        tileX,
        tileY))
    {
    case TileType::Ground:
    case TileType::Brick:
    case TileType::QuestionBlock:
        return true;

    case TileType::Empty:
    default:
        return false;
    }
}

bool TileMap::isInside(
    int tileX,
    int tileY) const
{
    return tileX >= 0 &&
           tileX < m_width &&
           tileY >= 0 &&
           tileY < m_height;
}

TileMap::TileType
TileMap::tileFromCharacter(
    char character) const
{
    switch (character)
    {
    case GROUND:
        return TileType::Ground;

    case BRICK:
        return TileType::Brick;

    case QUESTION:
        return TileType::QuestionBlock;

    case EMPTY:
    default:
        return TileType::Empty;
    }
}

void TileMap::render(
    Renderer& renderer,
    const Camera& camera) const
{
    if (m_width <= 0 ||
        m_height <= 0)
    {
        return;
    }

    const int firstTileX =
        std::max(
            0,
            static_cast<int>(
                camera.x() /
                TILE_SIZE));

    const int lastTileX =
        std::min(
            m_width - 1,
            static_cast<int>(
                (camera.x() +
                 Camera::VIEW_WIDTH) /
                TILE_SIZE));

    const int firstTileY =
        std::max(
            0,
            static_cast<int>(
                camera.y() /
                TILE_SIZE));

    const int lastTileY =
        std::min(
            m_height - 1,
            static_cast<int>(
                (camera.y() +
                 Camera::VIEW_HEIGHT) /
                TILE_SIZE));

    for (int y = firstTileY;
         y <= lastTileY;
         ++y)
    {
        for (int x = firstTileX;
             x <= lastTileX;
             ++x)
        {
            const TileType tile =
                getTile(x, y);

            if (tile == TileType::Empty)
            {
                continue;
            }

            const int worldX =
                x * TILE_SIZE;

            const int worldY =
                y * TILE_SIZE;

            const int screenX =
                worldX -
                static_cast<int>(
                    camera.x());

            const int screenY =
                worldY -
                static_cast<int>(
                    camera.y());

            switch (tile)
            {
            case TileType::Ground:
            {
                renderer.drawRect(
                    screenX,
                    screenY,
                    TILE_SIZE,
                    TILE_SIZE,
                    150,
                    80,
                    40);

                renderer.drawRect(
                    screenX,
                    screenY,
                    TILE_SIZE,
                    3,
                    190,
                    110,
                    55);

                renderer.drawRect(
                    screenX + 3,
                    screenY + 7,
                    4,
                    3,
                    120,
                    60,
                    30);

                renderer.drawRect(
                    screenX + 10,
                    screenY + 12,
                    3,
                    3,
                    120,
                    60,
                    30);

                break;
            }

            case TileType::Brick:
            {
                renderer.drawRect(
                    screenX,
                    screenY,
                    TILE_SIZE,
                    TILE_SIZE,
                    180,
                    90,
                    45);

                renderer.drawRect(
                    screenX,
                    screenY + 7,
                    TILE_SIZE,
                    2,
                    110,
                    50,
                    30);

                renderer.drawRect(
                    screenX + 7,
                    screenY,
                    2,
                    7,
                    110,
                    50,
                    30);

                renderer.drawRect(
                    screenX + 3,
                    screenY + 9,
                    2,
                    7,
                    110,
                    50,
                    30);

                renderer.drawRect(
                    screenX + 12,
                    screenY + 9,
                    2,
                    7,
                    110,
                    50,
                    30);

                break;
            }

            case TileType::QuestionBlock:
            {
                renderer.drawRect(
                    screenX,
                    screenY,
                    TILE_SIZE,
                    TILE_SIZE,
                    230,
                    170,
                    35);

                renderer.drawRect(
                    screenX,
                    screenY,
                    TILE_SIZE,
                    2,
                    150,
                    90,
                    20);

                renderer.drawRect(
                    screenX,
                    screenY + 14,
                    TILE_SIZE,
                    2,
                    150,
                    90,
                    20);

                renderer.drawRect(
                    screenX,
                    screenY,
                    2,
                    TILE_SIZE,
                    150,
                    90,
                    20);

                renderer.drawRect(
                    screenX + 14,
                    screenY,
                    2,
                    TILE_SIZE,
                    150,
                    90,
                    20);

                renderer.drawRect(
                    screenX + 6,
                    screenY + 4,
                    5,
                    2,
                    255,
                    245,
                    180);

                renderer.drawRect(
                    screenX + 10,
                    screenY + 6,
                    2,
                    4,
                    255,
                    245,
                    180);

                renderer.drawRect(
                    screenX + 7,
                    screenY + 9,
                    4,
                    2,
                    255,
                    245,
                    180);

                renderer.drawRect(
                    screenX + 7,
                    screenY + 12,
                    3,
                    2,
                    255,
                    245,
                    180);

                break;
            }

            case TileType::Empty:
            default:
                break;
            }
        }
    }
}