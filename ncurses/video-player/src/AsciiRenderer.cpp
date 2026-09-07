#include "AsciiRenderer.hpp"

#include <ncurses.h>

#include <algorithm>


AsciiRenderer::AsciiRenderer()
    : quit_(false),
      terminalWidth_(0),
      terminalHeight_(0)
{
}


void AsciiRenderer::initialize()
{
    initscr();

    // Do not echo keyboard input
    noecho();

    // Do not wait for keyboard input
    nodelay(stdscr, TRUE);

    // Enable special keys
    keypad(stdscr, TRUE);

    // Hide cursor
    curs_set(0);

    // Allow terminal resize
    start_color();

    updateTerminalSize();
}


void AsciiRenderer::shutdown()
{
    endwin();
}


void AsciiRenderer::updateTerminalSize()
{
    getmaxyx(
        stdscr,
        terminalHeight_,
        terminalWidth_
    );
}


char AsciiRenderer::pixelToAscii(
    unsigned char r,
    unsigned char g,
    unsigned char b)
{
    // Standard luminance calculation

    double luminance =
        0.2126 * r +
        0.7152 * g +
        0.0722 * b;


    // ASCII gradient from dark -> bright

    static const char* gradient =
        " .:-=+*#%@";

    constexpr int gradientSize = 10;


    int index =
        static_cast<int>(
            luminance *
            (gradientSize - 1) /
            255.0
        );


    index = std::clamp(
        index,
        0,
        gradientSize - 1
    );


    return gradient[index];
}


void AsciiRenderer::render(
    const AVFrame* frame,
    int sourceWidth,
    int sourceHeight)
{
    updateTerminalSize();

    erase();


    if (terminalWidth_ <= 0 ||
        terminalHeight_ <= 0)
    {
        return;
    }


    // ---------------------------------------------
    // Character aspect ratio compensation
    //
    // Terminal characters are roughly twice as
    // tall as they are wide.
    // ---------------------------------------------

    constexpr double characterAspect = 0.5;


    double scaleX =
        static_cast<double>(terminalWidth_) /
        sourceWidth;

    double scaleY =
        static_cast<double>(terminalHeight_) /
        sourceHeight /
        characterAspect;


    double scale =
        std::min(scaleX, scaleY);


    int outputWidth =
        static_cast<int>(
            sourceWidth * scale
        );

    int outputHeight =
        static_cast<int>(
            sourceHeight *
            scale *
            characterAspect
        );


    outputWidth =
        std::max(1, outputWidth);

    outputHeight =
        std::max(1, outputHeight);


    // Center the image

    int offsetX =
        (terminalWidth_ - outputWidth) / 2;

    int offsetY =
        (terminalHeight_ - outputHeight) / 2;


    // ---------------------------------------------
    // Render
    // ---------------------------------------------

    for (int y = 0;
         y < outputHeight;
         ++y)
    {
        int sourceY =
            y * sourceHeight /
            outputHeight;


        for (int x = 0;
             x < outputWidth;
             ++x)
        {
            int sourceX =
                x * sourceWidth /
                outputWidth;


            uint8_t* pixel =
                frame->data[0] +
                sourceY * frame->linesize[0] +
                sourceX * 3;


            unsigned char r = pixel[0];
            unsigned char g = pixel[1];
            unsigned char b = pixel[2];


            char ascii =
                pixelToAscii(r, g, b);


            mvaddch(
                offsetY + y,
                offsetX + x,
                ascii
            );
        }
    }


    refresh();
}


bool AsciiRenderer::shouldQuit() const
{
    return quit_;
}