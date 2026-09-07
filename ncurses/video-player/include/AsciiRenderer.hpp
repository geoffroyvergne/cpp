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

    // Input state
    bool consumePauseToggle();

    bool consumeSeekBackward();

    bool consumeSeekForward();

    bool consumeSpeedIncrease();

    bool consumeSpeedDecrease();

    bool consumeSpeedReset();

private:

    bool quit_;
    bool colorMode_;

    bool pauseToggle_;
    bool seekBackward_;
    bool seekForward_;
    bool speedIncrease_;
    bool speedDecrease_;
    bool speedReset_;

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