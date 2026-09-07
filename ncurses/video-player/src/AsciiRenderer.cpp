#include "AsciiRenderer.hpp"

#include <ncurses.h>

#include <algorithm>
#include <cmath>

AsciiRenderer::AsciiRenderer()
    : quit_(false),
      colorMode_(false),

      pauseToggle_(false),
      seekBackward_(false),
      seekForward_(false),
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

void AsciiRenderer::handleInput()
{
    pauseToggle_ = false;
    seekBackward_ = false;
    seekForward_ = false;
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
                    colorMode_ =
                        !colorMode_;
                }
                break;

            case KEY_LEFT:
                seekBackward_ = true;
                break;

            case KEY_RIGHT:
                seekForward_ = true;
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

    red =
        std::clamp(red, 0, 5);

    green =
        std::clamp(green, 0, 5);

    blue =
        std::clamp(blue, 0, 5);

    return
        16 +
        36 * red +
        6 * green +
        blue;
}

void AsciiRenderer::render(
    const AVFrame* frame,
    int sourceWidth,
    int sourceHeight)
{
    handleInput();

    if (quit_)
        return;

    updateTerminalSize();

    erase();

    if (terminalWidth_ <= 0 ||
        terminalHeight_ <= 0)
    {
        return;
    }

    // Terminal characters are normally taller than they are wide.
    // This correction prevents the image from being stretched.
    constexpr double characterAspect = 0.5;

    double scaleX =
        static_cast<double>(
            terminalWidth_
        ) /
        sourceWidth;

    double scaleY =
        static_cast<double>(
            terminalHeight_
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

    int offsetX =
        (terminalWidth_ -
         outputWidth) / 2;

    int offsetY =
        (terminalHeight_ -
         outputHeight) / 2;

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

    // ------------------------------------------------------------
    // Status line
    // ------------------------------------------------------------

    attron(A_BOLD);

    mvprintw(
        0,
        0,
        "%s | SPACE: pause | "
        "LEFT/RIGHT: seek | "
        "+/-: speed | 0: normal | Q: quit",
        colorMode_
            ? "[COLOR]"
            : "[MONO]"
    );

    attroff(A_BOLD);

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
