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
        int sourceHeight,
        double currentTime,
        double duration,
        double speed,
        bool paused
    );

    void pollInput();

    bool shouldQuit() const;

    bool consumePauseToggle();

    bool consumeSeekBackward();
    bool consumeSeekForward();

    bool consumeLongSeekBackward();
    bool consumeLongSeekForward();

    bool consumeSpeedIncrease();
    bool consumeSpeedDecrease();
    bool consumeSpeedReset();

private:

    // -------------------------------------------------------------------------
    // Rendering state
    // -------------------------------------------------------------------------

    bool quit_;

    // false = grayscale
    // true  = color
    bool colorMode_;

    // false = ASCII
    // true  = rectangles
    bool rectangleMode_;

    // -------------------------------------------------------------------------
    // Input state
    // -------------------------------------------------------------------------

    bool pauseToggle_;

    bool seekBackward_;
    bool seekForward_;

    bool longSeekBackward_;
    bool longSeekForward_;

    bool speedIncrease_;
    bool speedDecrease_;
    bool speedReset_;

    // -------------------------------------------------------------------------
    // Terminal
    // -------------------------------------------------------------------------

    int terminalWidth_;
    int terminalHeight_;

    // -------------------------------------------------------------------------
    // Terminal management
    // -------------------------------------------------------------------------

    void updateTerminalSize();

    void initializeColors();

    void handleInput();

    // -------------------------------------------------------------------------
    // Pixel conversion
    // -------------------------------------------------------------------------

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

    // -------------------------------------------------------------------------
    // Rendering modes
    // -------------------------------------------------------------------------

    void renderAscii(
        const AVFrame* frame,
        int sourceWidth,
        int sourceHeight
    );

    void renderRectangles(
        const AVFrame* frame,
        int sourceWidth,
        int sourceHeight
    );

    // -------------------------------------------------------------------------
    // UI
    // -------------------------------------------------------------------------

    void renderProgressBar(
        double currentTime,
        double duration,
        double speed,
        bool paused
    );

    std::string formatTime(double seconds);
};
