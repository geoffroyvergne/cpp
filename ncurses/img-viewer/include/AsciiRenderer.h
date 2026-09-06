#pragma once

#include "Image.h"
#include "RenderConfig.h"

#include <string>
#include <vector>

class AsciiRenderer
{
public:
    static std::vector<std::string> render(
        const Image& image,
        int maxWidth,
        int maxHeight,
        const RenderConfig& config
    );
};