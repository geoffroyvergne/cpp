#pragma once

#include <string>
#include <vector>

class Level
{
public:
    struct GoombaSpawn
    {
        float x{0.0f};
        float y{0.0f};
    };

    Level() = default;

    bool loadFromFile(
        const std::string& path);

    int width() const
    {
        return m_width;
    }

    int height() const
    {
        return m_height;
    }

    char getTile(
        int x,
        int y) const;

    bool hasPlayerSpawn() const
    {
        return m_hasPlayerSpawn;
    }

    float playerSpawnX() const
    {
        return m_playerSpawnX;
    }

    float playerSpawnY() const
    {
        return m_playerSpawnY;
    }

    const std::vector<GoombaSpawn>&
    goombaSpawns() const
    {
        return m_goombaSpawns;
    }

private:
    int m_width{0};
    int m_height{0};

    std::vector<std::string> m_rows;

    bool m_hasPlayerSpawn{false};

    float m_playerSpawnX{0.0f};
    float m_playerSpawnY{0.0f};

    std::vector<GoombaSpawn>
        m_goombaSpawns;
};