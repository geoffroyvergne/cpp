#include "AsciiRenderer.hpp"

#include <ncurses.h>

#include <algorithm>
#include <cmath>
#include <cstdio>

AsciiRenderer::AsciiRenderer()
    : quit_(false),
      colorMode_(false),

      pauseToggle_(false),

      seekBackward_(false),
      seekForward_(false),

      longSeekBackward_(false),
      longSeekForward_(false),

      speedIncrease_(false),
      speedDecrease_(false),
      speedReset_(false),

      terminalWidth_(0),
      terminalHeight_(0)
{
}

void AsciiRenderer::initialize()
{
    initscr();

    noecho();

    nodelay(stdscr, TRUE);

    keypad(stdscr, TRUE);

    curs_set(0);

    raw();

    updateTerminalSize();

    initializeColors();
}

void AsciiRenderer::shutdown()
{
    endwin();
}

void AsciiRenderer::initializeColors()
{
    if (!has_colors())
        return;

    start_color();

    use_default_colors();

    if (COLORS >= 256)
    {
        int maxColors =
            std::min(
                256,
                COLOR_PAIRS - 1
            );

        for (int color = 0;
             color < maxColors;
             ++color)
        {
            init_pair(
                color + 1,
                color,
                -1
            );
        }
    }
    else
    {
        for (int color = 0;
             color < COLORS && color < 16;
             ++color)
        {
            if (color + 1 < COLOR_PAIRS)
            {
                init_pair(
                    color + 1,
                    color,
                    -1
                );
            }
        }
    }
}

void AsciiRenderer::updateTerminalSize()
{
    getmaxyx(
        stdscr,
        terminalHeight_,
        terminalWidth_
    );
}

void AsciiRenderer::pollInput()
{
    handleInput();
}

void AsciiRenderer::handleInput()
{
    pauseToggle_ = false;

    seekBackward_ = false;
    seekForward_ = false;

    longSeekBackward_ = false;
    longSeekForward_ = false;

    speedIncrease_ = false;
    speedDecrease_ = false;
    speedReset_ = false;

    int key;

    while ((key = getch()) != ERR)
    {
        switch (key)
        {
            case 'q':
            case 'Q':
            case 27:
                quit_ = true;
                break;

            case ' ':
                pauseToggle_ = true;
                break;

            case 'c':
            case 'C':
                if (has_colors())
                {
                    colorMode_ = !colorMode_;
                }
                break;

            case KEY_LEFT:
                seekBackward_ = true;
                break;

            case KEY_RIGHT:
                seekForward_ = true;
                break;

            /*
             * Shift + LEFT / RIGHT cannot reliably be
             * distinguished from the normal arrow keys
             * in every terminal.
             *
             * We therefore use:
             *
             *   < / >  = 30 seconds
             */
            case '<':
                longSeekBackward_ = true;
                break;

            case '>':
                longSeekForward_ = true;
                break;

            case '+':
            case '=':
                speedIncrease_ = true;
                break;

            case '-':
                speedDecrease_ = true;
                break;

            case '0':
                speedReset_ = true;
                break;

            case KEY_RESIZE:
                updateTerminalSize();
                break;

            default:
                break;
        }
    }
}

char AsciiRenderer::pixelToAscii(
    unsigned char r,
    unsigned char g,
    unsigned char b)
{
    double luminance =
        0.2126 * r +
        0.7152 * g +
        0.0722 * b;

    static const char* gradient =
        " .,:;irsXA253hMHGS#9B&@";

    constexpr int gradientSize = 23;

    int index =
        static_cast<int>(
            luminance *
            (gradientSize - 1) /
            255.0
        );

    index =
        std::clamp(
            index,
            0,
            gradientSize - 1
        );

    return gradient[index];
}

int AsciiRenderer::pixelToColor(
    unsigned char r,
    unsigned char g,
    unsigned char b)
{
    if (COLORS < 256)
    {
        int color;

        if (r > 200 && g > 200 && b > 200)
            color = COLOR_WHITE;
        else if (r > 150 && g < 100 && b < 100)
            color = COLOR_RED;
        else if (r < 100 && g > 150 && b < 100)
            color = COLOR_GREEN;
        else if (r < 100 && g < 100 && b > 150)
            color = COLOR_BLUE;
        else if (r > 150 && g > 150 && b < 100)
            color = COLOR_YELLOW;
        else if (r > 150 && g < 100 && b > 150)
            color = COLOR_MAGENTA;
        else if (r < 100 && g > 150 && b > 150)
            color = COLOR_CYAN;
        else
            color = COLOR_WHITE;

        return color;
    }

    int red =
        static_cast<int>(
            std::round(
                r / 255.0 * 5.0
            )
        );

    int green =
        static_cast<int>(
            std::round(
                g / 255.0 * 5.0
            )
        );

    int blue =
        static_cast<int>(
            std::round(
                b / 255.0 * 5.0
            )
        );

    red = std::clamp(red, 0, 5);
    green = std::clamp(green, 0, 5);
    blue = std::clamp(blue, 0, 5);

    return
        16 +
        36 * red +
        6 * green +
        blue;
}

std::string AsciiRenderer::formatTime(double seconds)
{
    if (seconds < 0.0)
        seconds = 0.0;

    int totalSeconds =
        static_cast<int>(
            seconds
        );

    int hours =
        totalSeconds / 3600;

    int minutes =
        (totalSeconds % 3600) / 60;

    int secs =
        totalSeconds % 60;

    char buffer[32];

    if (hours > 0)
    {
        std::snprintf(
            buffer,
            sizeof(buffer),
            "%02d:%02d:%02d",
            hours,
            minutes,
            secs
        );
    }
    else
    {
        std::snprintf(
            buffer,
            sizeof(buffer),
            "%02d:%02d",
            minutes,
            secs
        );
    }

    return std::string(buffer);
}

void AsciiRenderer::renderProgressBar(
    double currentTime,
    double duration,
    double speed,
    bool paused)
{
    if (terminalHeight_ < 2)
        return;

    int barY =
        terminalHeight_ - 2;

    int infoY =
        terminalHeight_ - 1;

    /*
     * Clear the two bottom lines.
     */
    move(barY, 0);
    clrtoeol();

    move(infoY, 0);
    clrtoeol();

    /*
     * Progress bar.
     */
    int barWidth =
        std::max(
            10,
            terminalWidth_ - 2
        );

    double progress = 0.0;

    if (duration > 0.0)
    {
        progress =
            currentTime /
            duration;
    }

    progress =
        std::clamp(
            progress,
            0.0,
            1.0
        );

    int filled =
        static_cast<int>(
            progress *
            barWidth
        );

    mvaddch(
        barY,
        0,
        '['
    );

    for (int x = 0;
         x < barWidth;
         ++x)
    {
        if (x < filled)
        {
            mvaddch(
                barY,
                x + 1,
                '='
            );
        }
        else if (x == filled)
        {
            mvaddch(
                barY,
                x + 1,
                '>'
            );
        }
        else
        {
            mvaddch(
                barY,
                x + 1,
                ' '
            );
        }
    }

    if (barWidth + 1 < terminalWidth_)
    {
        mvaddch(
            barY,
            barWidth + 1,
            ']'
        );
    }

    /*
     * Information line.
     */
    std::string current =
        formatTime(currentTime);

    std::string total =
        formatTime(duration);

    const char* state =
        paused
            ? "PAUSED"
            : "PLAY";

    char info[256];

    std::snprintf(
        info,
        sizeof(info),
        "%s / %s   |   %s   |   Speed: %.2gx",
        current.c_str(),
        total.c_str(),
        state,
        speed
    );

    mvaddnstr(
        infoY,
        0,
        info,
        terminalWidth_ - 1
    );
}

void AsciiRenderer::render(
    const AVFrame* frame,
    int sourceWidth,
    int sourceHeight,
    double currentTime,
    double duration,
    double speed,
    bool paused)
{
    updateTerminalSize();

    if (terminalWidth_ <= 0 ||
        terminalHeight_ <= 2)
    {
        return;
    }

    erase();

    /*
     * Reserve two lines at the bottom for
     * progress and status information.
     */
    int imageHeight =
        terminalHeight_ - 2;

    /*
     * Terminal characters are normally taller
     * than they are wide, so compensate for
     * character aspect ratio.
     */
    constexpr double characterAspect = 0.5;

    double scaleX =
        static_cast<double>(
            terminalWidth_
        ) /
        sourceWidth;

    double scaleY =
        static_cast<double>(
            imageHeight
        ) /
        sourceHeight /
        characterAspect;

    double scale =
        std::min(
            scaleX,
            scaleY
        );

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
        std::max(
            1,
            outputWidth
        );

    outputHeight =
        std::max(
            1,
            outputHeight
        );

    outputWidth =
        std::min(
            outputWidth,
            terminalWidth_
        );

    outputHeight =
        std::min(
            outputHeight,
            imageHeight
        );

    int offsetX =
        (terminalWidth_ -
         outputWidth) / 2;

    int offsetY =
        (imageHeight -
         outputHeight) / 2;

    /*
     * Render image.
     */
    for (int y = 0;
         y < outputHeight;
         ++y)
    {
        int sourceY =
            y *
            sourceHeight /
            outputHeight;

        for (int x = 0;
             x < outputWidth;
             ++x)
        {
            int sourceX =
                x *
                sourceWidth /
                outputWidth;

            uint8_t* pixel =
                frame->data[0] +
                sourceY *
                frame->linesize[0] +
                sourceX * 3;

            unsigned char r =
                pixel[0];

            unsigned char g =
                pixel[1];

            unsigned char b =
                pixel[2];

            char ascii =
                pixelToAscii(
                    r,
                    g,
                    b
                );

            int screenX =
                offsetX + x;

            int screenY =
                offsetY + y;

            /*
             * Never draw the image over the
             * status/progress area.
             */
            if (screenY >= imageHeight)
                continue;

            if (!colorMode_)
            {
                mvaddch(
                    screenY,
                    screenX,
                    ascii
                );

                continue;
            }

            int color =
                pixelToColor(
                    r,
                    g,
                    b
                );

            int pairNumber =
                color + 1;

            if (pairNumber > 0 &&
                pairNumber < COLOR_PAIRS)
            {
                attron(
                    COLOR_PAIR(
                        pairNumber
                    )
                );

                mvaddch(
                    screenY,
                    screenX,
                    ascii
                );

                attroff(
                    COLOR_PAIR(
                        pairNumber
                    )
                );
            }
            else
            {
                mvaddch(
                    screenY,
                    screenX,
                    ascii
                );
            }
        }
    }

    /*
     * Progress / status.
     */
    renderProgressBar(
        currentTime,
        duration,
        speed,
        paused
    );

    /*
     * Controls help.
     */
    if (terminalHeight_ >= 4)
    {
        attron(A_BOLD);

        const char* mode =
            colorMode_
                ? "[COLOR]"
                : "[MONO]";

        std::string help =
            std::string(mode) +
            "  SPACE: pause  "
            "LEFT/RIGHT: +/-5s  "
            "</>: +/-30s  "
            "+/-: speed  "
            "0: 1x  "
            "C: color  "
            "Q: quit";

        /*
         * Put the help line at the top.
         */
        mvaddnstr(
            0,
            0,
            help.c_str(),
            terminalWidth_ - 1
        );

        attroff(A_BOLD);
    }

    refresh();
}

bool AsciiRenderer::shouldQuit() const
{
    return quit_;
}

bool AsciiRenderer::consumePauseToggle()
{
    bool value =
        pauseToggle_;

    pauseToggle_ = false;

    return value;
}

bool AsciiRenderer::consumeSeekBackward()
{
    bool value =
        seekBackward_;

    seekBackward_ = false;

    return value;
}

bool AsciiRenderer::consumeSeekForward()
{
    bool value =
        seekForward_;

    seekForward_ = false;

    return value;
}

bool AsciiRenderer::consumeLongSeekBackward()
{
    bool value =
        longSeekBackward_;

    longSeekBackward_ = false;

    return value;
}

bool AsciiRenderer::consumeLongSeekForward()
{
    bool value =
        longSeekForward_;

    longSeekForward_ = false;

    return value;
}

bool AsciiRenderer::consumeSpeedIncrease()
{
    bool value =
        speedIncrease_;

    speedIncrease_ = false;

    return value;
}

bool AsciiRenderer::consumeSpeedDecrease()
{
    bool value =
        speedDecrease_;

    speedDecrease_ = false;

    return value;
}

bool AsciiRenderer::consumeSpeedReset()
{
    bool value =
        speedReset_;

    speedReset_ = false;

    return value;
}