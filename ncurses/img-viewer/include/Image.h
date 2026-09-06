#pragma once

#include <vector>
#include <cstdint>

struct Image
{
    int width;
    int height;

    // RGB: 3 bytes per pixel
    std::vector<uint8_t> pixels;

    const uint8_t* pixel(int x, int y) const;
};
