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

    // Read and process keyboard input.
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

    bool quit_;
    bool colorMode_;

    bool pauseToggle_;

    bool seekBackward_;
    bool seekForward_;

    bool longSeekBackward_;
    bool longSeekForward_;

    bool speedIncrease_;
    bool speedDecrease_;
    bool speedReset_;

    int terminalWidth_;
    int terminalHeight_;

    void updateTerminalSize();
    void initializeColors();

    void handleInput();

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

    void renderProgressBar(
        double currentTime,
        double duration,
        double speed,
        bool paused
    );

    std::string formatTime(double seconds);
};