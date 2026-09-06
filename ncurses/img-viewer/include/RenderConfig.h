#pragma once

enum class RenderMode
{
    ASCII,
    RECTANGLES
};

struct RenderConfig
{
    double brightness = 1.0;

    // Percentage of terminal dimensions available
    // to the image.
    double size = 1.0;

    RenderMode mode = RenderMode::ASCII;
};