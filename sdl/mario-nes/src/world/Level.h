#pragma once

#include <string>
#include <vector>

class Level
{
public:
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

private:
    int m_width{0};
    int m_height{0};

    std::vector<std::string> m_rows;
};