#include "Level.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

bool Level::loadFromFile(
    const std::string& path)
{
    m_rows.clear();
    m_width = 0;
    m_height = 0;

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
        // Remove Windows carriage return
        // when reading CRLF files.
        if (!line.empty() &&
            line.back() == '\r')
        {
            line.pop_back();
        }

        // Ignore completely empty lines.
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

    // All rows must have the same width.
    // Shorter rows are padded with empty tiles.
    for (std::string& row : m_rows)
    {
        if (static_cast<int>(row.length()) <
            m_width)
        {
            row.append(
                m_width - row.length(),
                '.');
        }
    }

    m_height =
        static_cast<int>(
            m_rows.size());

    std::cout
        << "Loaded level: "
        << path
        << " ("
        << m_width
        << "x"
        << m_height
        << " tiles)"
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