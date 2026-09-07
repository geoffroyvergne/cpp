#pragma once

#include <string>

extern "C" {
#include <libavutil/frame.h>
}

class AsciiRenderer
{
public:

    AsciiRenderer();

    void initialize();
    void shutdown();

    void render(
        const AVFrame* frame,
        int sourceWidth,
        int sourceHeight
    );

    bool shouldQuit() const;

private:

    bool quit_;
    bool colorMode_;

    int terminalWidth_;
    int terminalHeight_;

    void updateTerminalSize();
    void initializeColors();

    char pixelToAscii(
        unsigned char r,
        unsigned char g,
        unsigned char b
    );

    int pixelToColor(
        unsigned char r,
        unsigned char g,
        unsigned char b
    );

    void handleInput();
};