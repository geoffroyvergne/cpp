#pragma once

#include "Image.h"
#include "RenderConfig.h"

#include <string>
#include <vector>

struct RenderCell
{
    std::string character;

    // ncurses color pair.
    // 0 means default/no color.
    int colorPair = 0;
};

using RenderedLine = std::vector<RenderCell>;
using RenderedImage = std::vector<RenderedLine>;

class AsciiRenderer
{
public:
    static std::vector<std::string> render(
        const Image& image,
        int maxWidth,
        int maxHeight,
        const RenderConfig& config
    );

    static RenderedImage renderColored(
        const Image& image,
        int maxWidth,
        int maxHeight,
        const RenderConfig& config
    );
};