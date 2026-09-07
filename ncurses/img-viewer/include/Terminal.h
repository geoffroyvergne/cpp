#pragma once

#include "AsciiRenderer.h"

#include <string>
#include <vector>

class Terminal
{
public:
    Terminal();
    ~Terminal();

    Terminal(const Terminal&) = delete;
    Terminal& operator=(const Terminal&) = delete;

    void getSize(
        int& rows,
        int& cols
    ) const;

    void draw(
        const std::vector<std::string>& lines
    );

    void drawColored(
        const RenderedImage& image
    );

    void drawStatus(
        const std::string& text
    );

    int readKey();
};