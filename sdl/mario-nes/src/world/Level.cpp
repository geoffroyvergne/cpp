#include "Level.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

namespace
{

constexpr char PLAYER_SPAWN = 'S';
constexpr char GOOMBA_SPAWN = 'G';

constexpr float TILE_SIZE = 16.0f;

}

bool Level::loadFromFile(
    const std::string& path)
{
    m_rows.clear();

    m_width = 0;
    m_height = 0;

    m_hasPlayerSpawn = false;

    m_playerSpawnX = 0.0f;
    m_playerSpawnY = 0.0f;

    m_goombaSpawns.clear();

    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr
            << "Failed to open level file: "
            << path
            << '\n';

        return false;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (!line.empty() &&
            line.back() == '\r')
        {
            line.pop_back();
        }

        if (line.empty())
        {
            continue;
        }

        m_rows.push_back(line);

        m_width =
            std::max(
                m_width,
                static_cast<int>(
                    line.length()));
    }

    file.close();

    if (m_rows.empty())
    {
        std::cerr
            << "Level file is empty: "
            << path
            << '\n';

        return false;
    }

    for (std::string& row : m_rows)
    {
        if (static_cast<int>(row.length()) <
            m_width)
        {
            row.append(
                m_width -
                    static_cast<int>(
                        row.length()),
                '.');
        }
    }

    m_height =
        static_cast<int>(
            m_rows.size());

    for (int y = 0;
         y < m_height;
         ++y)
    {
        for (int x = 0;
             x < m_width;
             ++x)
        {
            const char character =
                m_rows[y][x];

            if (character == PLAYER_SPAWN)
            {
                if (m_hasPlayerSpawn)
                {
                    std::cerr
                        << "Warning: multiple player "
                           "spawn points found. "
                           "Using the first one."
                        << '\n';

                    continue;
                }

                m_hasPlayerSpawn = true;

                m_playerSpawnX =
                    static_cast<float>(x) *
                    TILE_SIZE;

                m_playerSpawnY =
                    static_cast<float>(y) *
                    TILE_SIZE;

                m_rows[y][x] = '.';

                continue;
            }

            if (character == GOOMBA_SPAWN)
            {
                GoombaSpawn spawn;

                spawn.x =
                    static_cast<float>(x) *
                    TILE_SIZE;

                spawn.y =
                    static_cast<float>(y) *
                    TILE_SIZE;

                m_goombaSpawns.push_back(
                    spawn);

                m_rows[y][x] = '.';
            }
        }
    }

    std::cout
        << "Loaded level: "
        << path
        << " ("
        << m_width
        << "x"
        << m_height
        << " tiles)";

    if (m_hasPlayerSpawn)
    {
        std::cout
            << ", player spawn: ("
            << m_playerSpawnX
            << ", "
            << m_playerSpawnY
            << ")";
    }

    std::cout
        << ", Goombas: "
        << m_goombaSpawns.size()
        << '\n';

    return true;
}

char Level::getTile(
    int x,
    int y) const
{
    if (x < 0 ||
        x >= m_width ||
        y < 0 ||
        y >= m_height)
    {
        return '.';
    }

    return m_rows[y][x];
}