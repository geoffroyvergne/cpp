#include "AsciiRenderer.hpp"

#include <ncurses.h>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

AsciiRenderer::AsciiRenderer()
    : quit_(false),
      colorMode_(false),
      rectangleMode_(false),
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

    cbreak();
    noecho();

    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    curs_set(0);

    start_color();
    use_default_colors();

    initializeColors();
    updateTerminalSize();

    erase();
    refresh();
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

void AsciiRenderer::initializeColors()
{
    if (!has_colors())
        return;

    /*
     * Basic ANSI colors.
     */
    for (int color = 0; color < 8; ++color)
    {
        init_pair(
            color + 1,
            color,
            -1
        );
    }

    /*
     * Grayscale background colors.
     *
     * Important:
     * rectangles are drawn using a space character,
     * therefore the grayscale color must be the
     * BACKGROUND color, not the foreground color.
     */
    if (COLORS >= 256 && COLOR_PAIRS >= 34)
    {
        for (int i = 0; i < 24; ++i)
        {
            const int pair = 10 + i;
            const int color = 232 + i;

            init_pair(
                pair,
                COLOR_WHITE,
                color
            );
        }
    }
}

void AsciiRenderer::pollInput()
{
    handleInput();
}

void AsciiRenderer::handleInput()
{
    int ch;

    while ((ch = getch()) != ERR)
    {
        switch (ch)
        {
            case 'q':
            case 'Q':
                quit_ = true;
                break;

            case ' ':
                pauseToggle_ = true;
                break;

            case KEY_LEFT:
                seekBackward_ = true;
                break;

            case KEY_RIGHT:
                seekForward_ = true;
                break;

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
            case '_':
                speedDecrease_ = true;
                break;

            case '0':
                speedReset_ = true;
                break;

            case 'c':
            case 'C':
                colorMode_ = !colorMode_;
                break;

            case 'm':
            case 'M':
                rectangleMode_ = !rectangleMode_;
                break;

            default:
                break;
        }
    }
}

bool AsciiRenderer::shouldQuit() const
{
    return quit_;
}

bool AsciiRenderer::consumePauseToggle()
{
    bool value = pauseToggle_;
    pauseToggle_ = false;

    return value;
}

bool AsciiRenderer::consumeSeekBackward()
{
    bool value = seekBackward_;
    seekBackward_ = false;

    return value;
}

bool AsciiRenderer::consumeSeekForward()
{
    bool value = seekForward_;
    seekForward_ = false;

    return value;
}

bool AsciiRenderer::consumeLongSeekBackward()
{
    bool value = longSeekBackward_;
    longSeekBackward_ = false;

    return value;
}

bool AsciiRenderer::consumeLongSeekForward()
{
    bool value = longSeekForward_;
    longSeekForward_ = false;

    return value;
}

bool AsciiRenderer::consumeSpeedIncrease()
{
    bool value = speedIncrease_;
    speedIncrease_ = false;

    return value;
}

bool AsciiRenderer::consumeSpeedDecrease()
{
    bool value = speedDecrease_;
    speedDecrease_ = false;

    return value;
}

bool AsciiRenderer::consumeSpeedReset()
{
    bool value = speedReset_;
    speedReset_ = false;

    return value;
}

char AsciiRenderer::pixelToAscii(
    unsigned char r,
    unsigned char g,
    unsigned char b
)
{
    const double gray =
        0.2126 * static_cast<double>(r) +
        0.7152 * static_cast<double>(g) +
        0.0722 * static_cast<double>(b);

    static const char* ramp = " .:-=+*#%@";

    constexpr int rampSize = 10;

    int index =
        static_cast<int>(
            gray *
            (rampSize - 1) /
            255.0
        );

    index = std::clamp(
        index,
        0,
        rampSize - 1
    );

    return ramp[index];
}

int AsciiRenderer::pixelToColor(
    unsigned char r,
    unsigned char g,
    unsigned char b
)
{
    const double gray =
        0.2126 * static_cast<double>(r) +
        0.7152 * static_cast<double>(g) +
        0.0722 * static_cast<double>(b);

    if (gray < 35.0)
        return COLOR_BLACK;

    if (r > g * 1.35 && r > b * 1.35)
        return COLOR_RED;

    if (g > r * 1.25 && g > b * 1.25)
        return COLOR_GREEN;

    if (b > r * 1.25 && b > g * 1.20)
        return COLOR_BLUE;

    if (r > 150 && g > 120 && b < 100)
        return COLOR_YELLOW;

    if (r > 120 && b > 120 && g < 100)
        return COLOR_MAGENTA;

    if (g > 120 && b > 120 && r < 100)
        return COLOR_CYAN;

    if (gray > 180)
        return COLOR_WHITE;

    return COLOR_WHITE;
}

static int rgbToXterm256(
    unsigned char r,
    unsigned char g,
    unsigned char b
)
{
    auto componentToCube =
        [](unsigned char value) -> int
    {
        if (value < 48)
            return 0;

        if (value < 114)
            return 1;

        return static_cast<int>(
            std::round(
                (static_cast<double>(value) - 55.0) /
                40.0
            )
        );
    };

    const int rr =
        std::clamp(
            componentToCube(r),
            0,
            5
        );

    const int gg =
        std::clamp(
            componentToCube(g),
            0,
            5
        );

    const int bb =
        std::clamp(
            componentToCube(b),
            0,
            5
        );

    return 16 +
           (36 * rr) +
           (6 * gg) +
           bb;
}

void AsciiRenderer::render(
    const AVFrame* frame,
    int sourceWidth,
    int sourceHeight,
    double currentTime,
    double duration,
    double speed,
    bool paused
)
{
    if (!frame)
        return;

    updateTerminalSize();

    const int availableHeight =
        terminalHeight_ - 3;

    if (availableHeight <= 0 ||
        terminalWidth_ <= 0)
    {
        return;
    }

    /*
     * IMPORTANT:
     *
     * Do NOT call clear() or erase() here.
     *
     * Clearing the entire ncurses window before
     * drawing every frame causes a visible black
     * flash when the terminal is refreshed.
     *
     * Instead, we clear only the video area.
     */

    for (int y = 1;
         y < terminalHeight_ - 2;
         ++y)
    {
        move(y, 0);
        clrtoeol();
    }

    /*
     * Help line.
     */
    const char* mode;

    if (!rectangleMode_ && !colorMode_)
    {
        mode = "ASCII GRAY";
    }
    else if (!rectangleMode_ && colorMode_)
    {
        mode = "ASCII COLOR";
    }
    else if (rectangleMode_ && !colorMode_)
    {
        mode = "RECT GRAY";
    }
    else
    {
        mode = "RECT COLOR";
    }

    std::string help =
        std::string(mode) +
        "  SPACE: pause  "
        "LEFT/RIGHT: +/-5s  "
        "</>: +/-30s  "
        "+/-: speed  "
        "0: 1x  "
        "C: color  "
        "M: mode  "
        "Q: quit";

    move(0, 0);
    clrtoeol();

    mvaddnstr(
        0,
        0,
        help.c_str(),
        std::max(0, terminalWidth_ - 1)
    );

    /*
     * Render video.
     */
    if (rectangleMode_)
    {
        renderRectangles(
            frame,
            sourceWidth,
            sourceHeight
        );
    }
    else
    {
        renderAscii(
            frame,
            sourceWidth,
            sourceHeight
        );
    }

    /*
     * Progress bar and status.
     */
    renderProgressBar(
        currentTime,
        duration,
        speed,
        paused
    );

    /*
     * One single refresh for the whole frame.
     */
    refresh();
}

void AsciiRenderer::renderAscii(
    const AVFrame* frame,
    int sourceWidth,
    int sourceHeight
)
{
    if (!frame)
        return;

    const int availableHeight =
        terminalHeight_ - 3;

    if (availableHeight <= 0)
        return;

    /*
     * Approximate aspect ratio of a terminal character cell.
     *
     * A terminal character is normally taller than it
     * is wide, so we compensate horizontally.
     */
    constexpr double cellAspect = 0.55;

    const double sourceAspect =
        static_cast<double>(sourceWidth) /
        static_cast<double>(sourceHeight);

    const double terminalAspect =
        (
            static_cast<double>(terminalWidth_) *
            cellAspect
        ) /
        static_cast<double>(availableHeight);

    int renderWidth;
    int renderHeight;

    if (sourceAspect > terminalAspect)
    {
        renderWidth = terminalWidth_;

        renderHeight =
            static_cast<int>(
                (
                    static_cast<double>(renderWidth) *
                    cellAspect
                ) /
                sourceAspect
            );
    }
    else
    {
        renderHeight = availableHeight;

        renderWidth =
            static_cast<int>(
                (
                    static_cast<double>(renderHeight) *
                    sourceAspect
                ) /
                cellAspect
            );
    }

    renderWidth =
        std::clamp(
            renderWidth,
            1,
            terminalWidth_
        );

    renderHeight =
        std::clamp(
            renderHeight,
            1,
            availableHeight
        );

    const int offsetX =
        (terminalWidth_ - renderWidth) / 2;

    const int offsetY =
        1 +
        (availableHeight - renderHeight) / 2;

    constexpr int bytesPerPixel = 3;

    for (int y = 0;
         y < renderHeight;
         ++y)
    {
        const double sourceY =
            (
                static_cast<double>(y) +
                0.5
            ) *
            static_cast<double>(sourceHeight) /
            static_cast<double>(renderHeight);

        const int sy =
            std::clamp(
                static_cast<int>(sourceY),
                0,
                sourceHeight - 1
            );

        const uint8_t* row =
            frame->data[0] +
            sy * frame->linesize[0];

        for (int x = 0;
             x < renderWidth;
             ++x)
        {
            const double sourceX =
                (
                    static_cast<double>(x) +
                    0.5
                ) *
                static_cast<double>(sourceWidth) /
                static_cast<double>(renderWidth);

            const int sx =
                std::clamp(
                    static_cast<int>(sourceX),
                    0,
                    sourceWidth - 1
                );

            const uint8_t* pixel =
                row +
                sx * bytesPerPixel;

            const unsigned char r = pixel[0];
            const unsigned char g = pixel[1];
            const unsigned char b = pixel[2];

            const char character =
                pixelToAscii(r, g, b);

            if (colorMode_ && has_colors())
            {
                const int color =
                    pixelToColor(r, g, b);

                const int pair =
                    color + 1;

                attron(COLOR_PAIR(pair));

                mvaddch(
                    offsetY + y,
                    offsetX + x,
                    character
                );

                attroff(COLOR_PAIR(pair));
            }
            else
            {
                mvaddch(
                    offsetY + y,
                    offsetX + x,
                    character
                );
            }
        }
    }
}

void AsciiRenderer::renderRectangles(
    const AVFrame* frame,
    int sourceWidth,
    int sourceHeight
)
{
    if (!frame)
        return;

    const int availableHeight =
        terminalHeight_ - 3;

    if (availableHeight <= 0)
        return;

    constexpr double cellAspect = 0.55;

    const double sourceAspect =
        static_cast<double>(sourceWidth) /
        static_cast<double>(sourceHeight);

    const double terminalAspect =
        (
            static_cast<double>(terminalWidth_) *
            cellAspect
        ) /
        static_cast<double>(availableHeight);

    int renderWidth;
    int renderHeight;

    if (sourceAspect > terminalAspect)
    {
        renderWidth = terminalWidth_;

        renderHeight =
            static_cast<int>(
                (
                    static_cast<double>(renderWidth) *
                    cellAspect
                ) /
                sourceAspect
            );
    }
    else
    {
        renderHeight = availableHeight;

        renderWidth =
            static_cast<int>(
                (
                    static_cast<double>(renderHeight) *
                    sourceAspect
                ) /
                cellAspect
            );
    }

    renderWidth =
        std::clamp(
            renderWidth,
            1,
            terminalWidth_
        );

    renderHeight =
        std::clamp(
            renderHeight,
            1,
            availableHeight
        );

    const int offsetX =
        (terminalWidth_ - renderWidth) / 2;

    const int offsetY =
        1 +
        (availableHeight - renderHeight) / 2;

    for (int y = 0;
         y < renderHeight;
         ++y)
    {
        const int sy0 =
            static_cast<int>(
                static_cast<double>(y) *
                sourceHeight /
                renderHeight
            );

        const int sy1 =
            std::max(
                sy0 + 1,
                static_cast<int>(
                    static_cast<double>(y + 1) *
                    sourceHeight /
                    renderHeight
                )
            );

        for (int x = 0;
             x < renderWidth;
             ++x)
        {
            const int sx0 =
                static_cast<int>(
                    static_cast<double>(x) *
                    sourceWidth /
                    renderWidth
                );

            const int sx1 =
                std::max(
                    sx0 + 1,
                    static_cast<int>(
                        static_cast<double>(x + 1) *
                        sourceWidth /
                        renderWidth
                    )
                );

            long long totalR = 0;
            long long totalG = 0;
            long long totalB = 0;
            long long count = 0;

            for (int sy = sy0;
                 sy < sy1 &&
                 sy < sourceHeight;
                 ++sy)
            {
                const uint8_t* row =
                    frame->data[0] +
                    sy * frame->linesize[0];

                for (int sx = sx0;
                     sx < sx1 &&
                     sx < sourceWidth;
                     ++sx)
                {
                    const uint8_t* pixel =
                        row +
                        sx * 3;

                    totalR += pixel[0];
                    totalG += pixel[1];
                    totalB += pixel[2];

                    ++count;
                }
            }

            if (count == 0)
                continue;

            const unsigned char r =
                static_cast<unsigned char>(
                    totalR / count
                );

            const unsigned char g =
                static_cast<unsigned char>(
                    totalG / count
                );

            const unsigned char b =
                static_cast<unsigned char>(
                    totalB / count
                );

            /*
             * COLOR RECTANGLES
             *
             * A space character is used, so the same
             * color is used for foreground and background.
             */
            if (colorMode_ &&
                has_colors() &&
                COLORS >= 256 &&
                COLOR_PAIRS >= 2)
            {
                const int color =
                    rgbToXterm256(
                        r,
                        g,
                        b
                    );

                constexpr int firstPair = 40;
                constexpr int pairCount = 200;

                int pair;

                if (COLOR_PAIRS > firstPair + 1)
                {
                    pair =
                        firstPair +
                        (color % pairCount);

                    if (pair >= COLOR_PAIRS)
                    {
                        pair =
                            1 +
                            (
                                color %
                                std::max(
                                    1,
                                    COLOR_PAIRS - 1
                                )
                            );
                    }

                    init_pair(
                        pair,
                        color,
                        color
                    );

                    attron(COLOR_PAIR(pair));

                    mvaddch(
                        offsetY + y,
                        offsetX + x,
                        ' '
                    );

                    attroff(COLOR_PAIR(pair));
                }
                else
                {
                    const int basicColor =
                        pixelToColor(
                            r,
                            g,
                            b
                        );

                    const int basicPair =
                        basicColor + 1;

                    attron(
                        COLOR_PAIR(basicPair)
                    );

                    mvaddch(
                        offsetY + y,
                        offsetX + x,
                        ' '
                    );

                    attroff(
                        COLOR_PAIR(basicPair)
                    );
                }
            }

            /*
             * GRAYSCALE RECTANGLES
             *
             * Use the xterm grayscale palette as the
             * BACKGROUND because the rendered character
             * itself is a space.
             */
            else if (!colorMode_ &&
                     has_colors() &&
                     COLORS >= 256 &&
                     COLOR_PAIRS >= 34)
            {
                const double gray =
                    0.2126 *
                        static_cast<double>(r) +
                    0.7152 *
                        static_cast<double>(g) +
                    0.0722 *
                        static_cast<double>(b);

                int grayIndex =
                    static_cast<int>(
                        std::round(
                            232.0 +
                            gray * 23.0 / 255.0
                        )
                    );

                grayIndex =
                    std::clamp(
                        grayIndex,
                        232,
                        255
                    );

                const int pair =
                    10 +
                    (grayIndex - 232);

                attron(COLOR_PAIR(pair));

                mvaddch(
                    offsetY + y,
                    offsetX + x,
                    ' '
                );

                attroff(COLOR_PAIR(pair));
            }

            /*
             * FALLBACK
             */
            else
            {
                const char character =
                    pixelToAscii(
                        r,
                        g,
                        b
                    );

                if (colorMode_ &&
                    has_colors())
                {
                    const int color =
                        pixelToColor(
                            r,
                            g,
                            b
                        );

                    const int pair =
                        color + 1;

                    attron(
                        COLOR_PAIR(pair)
                    );

                    mvaddch(
                        offsetY + y,
                        offsetX + x,
                        character
                    );

                    attroff(
                        COLOR_PAIR(pair)
                    );
                }
                else
                {
                    mvaddch(
                        offsetY + y,
                        offsetX + x,
                        character
                    );
                }
            }
        }
    }
}

void AsciiRenderer::renderProgressBar(
    double currentTime,
    double duration,
    double speed,
    bool paused
)
{
    if (terminalHeight_ < 3)
        return;

    const int barY =
        terminalHeight_ - 2;

    const int barWidth =
        std::max(
            10,
            terminalWidth_ - 2
        );

    double progress = 0.0;

    if (duration > 0.0)
    {
        progress =
            currentTime / duration;

        progress =
            std::clamp(
                progress,
                0.0,
                1.0
            );
    }

    const int filled =
        static_cast<int>(
            progress *
            static_cast<double>(barWidth)
        );

    move(barY, 0);

    for (int i = 0;
         i < barWidth;
         ++i)
    {
        if (i < filled)
            addch('=');
        else
            addch('-');
    }

    const std::string current =
        formatTime(currentTime);

    const std::string total =
        formatTime(duration);

    std::ostringstream status;

    status
        << current
        << " / "
        << total
        << "   "
        << std::fixed
        << std::setprecision(2)
        << speed
        << "x";

    if (paused)
        status << "   PAUSED";

    const std::string text =
        status.str();

    move(
        terminalHeight_ - 1,
        0
    );

    clrtoeol();

    mvaddnstr(
        terminalHeight_ - 1,
        0,
        text.c_str(),
        std::max(0, terminalWidth_ - 1)
    );
}

std::string AsciiRenderer::formatTime(
    double seconds
)
{
    if (seconds < 0.0)
        seconds = 0.0;

    const int totalSeconds =
        static_cast<int>(seconds);

    const int hours =
        totalSeconds / 3600;

    const int minutes =
        (totalSeconds % 3600) / 60;

    const int secs =
        totalSeconds % 60;

    std::ostringstream stream;

    if (hours > 0)
    {
        stream
            << std::setfill('0')
            << std::setw(2)
            << hours
            << ":"
            << std::setw(2)
            << minutes
            << ":"
            << std::setw(2)
            << secs;
    }
    else
    {
        stream
            << std::setfill('0')
            << std::setw(2)
            << minutes
            << ":"
            << std::setw(2)
            << secs;
    }

    return stream.str();
}
