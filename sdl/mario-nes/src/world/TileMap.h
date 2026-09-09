#pragma once

#include <cstdint>
#include <vector>

class Camera;
class Level;
class Renderer;

class TileMap
{
public:
    static constexpr int TILE_SIZE = 16;

    enum class TileType : std::uint8_t
    {
        Empty = 0,
        Ground,
        Brick,
        QuestionBlock
    };

    TileMap() = default;

    bool initialize(
        const Level& level);

    void render(
        Renderer& renderer,
        const Camera& camera) const;

    TileType getTile(
        int tileX,
        int tileY) const;

    void setTile(
        int tileX,
        int tileY,
        TileType type);

    bool isSolid(
        int tileX,
        int tileY) const;

    int width() const
    {
        return m_width;
    }

    int height() const
    {
        return m_height;
    }

    float worldWidth() const
    {
        return static_cast<float>(
            m_width * TILE_SIZE);
    }

    float worldHeight() const
    {
        return static_cast<float>(
            m_height * TILE_SIZE);
    }

private:
    bool isInside(
        int tileX,
        int tileY) const;

    TileType tileFromCharacter(
        char character) const;

private:
    int m_width{0};
    int m_height{0};

    std::vector<TileType> m_tiles;
};