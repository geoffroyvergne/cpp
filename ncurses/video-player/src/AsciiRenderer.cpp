#include "AsciiRenderer.hpp"

#include <ncurses.h>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

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

// -----------------------------------------------------------------------------
// Initialization
// -----------------------------------------------------------------------------

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

    clear();
    refresh();
}

// -----------------------------------------------------------------------------
// Shutdown
// -----------------------------------------------------------------------------

void AsciiRenderer::shutdown()
{
    endwin();
}

// -----------------------------------------------------------------------------
// Terminal size
// -----------------------------------------------------------------------------

void AsciiRenderer::updateTerminalSize()
{
    getmaxyx(stdscr, terminalHeight_, terminalWidth_);
}

// -----------------------------------------------------------------------------
// Colors
// -----------------------------------------------------------------------------

void AsciiRenderer::initializeColors()
{
    if (!has_colors())
        return;

    /*
     * Basic colors for ASCII color mode.
     *
     * Pair 1..8:
     * black, red, green, yellow,
     * blue, magenta, cyan, white
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
     * Grayscale pairs.
     *
     * xterm 256 grayscale:
     *
     * 232 = almost black
     * ...
     * 255 = white
     *
     * We use pairs 10..33.
     */

    if (COLORS >= 256 && COLOR_PAIRS >= 34)
    {
        for (int i = 0; i < 24; ++i)
        {
            int pair = 10 + i;
            int color = 232 + i;

            init_pair(
                pair,
                COLOR_WHITE,
                color
            );
        }
    }
}

// -----------------------------------------------------------------------------
// Input
// -----------------------------------------------------------------------------

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

            /*
             * C:
             *
             * GRAY  <-> COLOR
             *
             * This NEVER changes rectangleMode_.
             */

            case 'c':
            case 'C':
                colorMode_ = !colorMode_;
                break;

            /*
             * M:
             *
             * ASCII <-> RECTANGLES
             *
             * This NEVER changes colorMode_.
             */

            case 'm':
            case 'M':
                rectangleMode_ = !rectangleMode_;
                break;

            default:
                break;
        }
    }
}

// -----------------------------------------------------------------------------
// State getters / consumers
// -----------------------------------------------------------------------------

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

// -----------------------------------------------------------------------------
// ASCII brightness
// -----------------------------------------------------------------------------

char AsciiRenderer::pixelToAscii(
    unsigned char r,
    unsigned char g,
    unsigned char b
)
{
    /*
     * Perceived luminance.
     */

    const double gray =
        0.2126 * static_cast<double>(r) +
        0.7152 * static_cast<double>(g) +
        0.0722 * static_cast<double>(b);

    /*
     * Dark -> bright.
     */

    static const char* ramp =
        " .:-=+*#%@";

    constexpr int rampSize = 10;

    int index =
        static_cast<int>(
            gray * (rampSize - 1) / 255.0
        );

    index = std::clamp(
        index,
        0,
        rampSize - 1
    );

    return ramp[index];
}

// -----------------------------------------------------------------------------
// Basic ncurses color
// -----------------------------------------------------------------------------

int AsciiRenderer::pixelToColor(
    unsigned char r,
    unsigned char g,
    unsigned char b
)
{
    /*
     * Convert RGB to luminance.
     */

    const double gray =
        0.2126 * static_cast<double>(r) +
        0.7152 * static_cast<double>(g) +
        0.0722 * static_cast<double>(b);

    /*
     * Very simple dominant-color classification.
     */

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

    /*
     * For neutral colors choose white.
     */

    return COLOR_WHITE;
}

// -----------------------------------------------------------------------------
// RGB -> xterm 256
// -----------------------------------------------------------------------------

static int rgbToXterm256(
    unsigned char r,
    unsigned char g,
    unsigned char b
)
{
    /*
     * xterm 256:
     *
     * 0..15   = standard colors
     * 16..231 = 6x6x6 RGB cube
     * 232..255 = grayscale
     *
     * We use the RGB cube.
     */

    auto componentToCube = [](unsigned char value) -> int
    {
        if (value < 48)
            return 0;

        if (value < 114)
            return 1;

        return static_cast<int>(
            std::round(
                (static_cast<double>(value) - 55.0) / 40.0
            )
        );
    };

    int rr = std::clamp(componentToCube(r), 0, 5);
    int gg = std::clamp(componentToCube(g), 0, 5);
    int bb = std::clamp(componentToCube(b), 0, 5);

    return 16 + (36 * rr) + (6 * gg) + bb;
}

// -----------------------------------------------------------------------------
// Main render
// -----------------------------------------------------------------------------

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

    /*
     * Leave:
     *
     * line 0 = help
     * last 2 lines = progress/status
     *
     * Video occupies the middle.
     */

    int availableHeight =
        terminalHeight_ - 3;

    if (availableHeight <= 0 || terminalWidth_ <= 0)
        return;

    clear();

    /*
     * Display current mode.
     */

    const char* mode;

    if (!rectangleMode_ && !colorMode_)
        mode = "ASCII GRAY";
    else if (!rectangleMode_ && colorMode_)
        mode = "ASCII COLOR";
    else if (rectangleMode_ && !colorMode_)
        mode = "RECT GRAY";
    else
        mode = "RECT COLOR";

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

    mvaddnstr(
        0,
        0,
        help.c_str(),
        terminalWidth_ - 1
    );

    /*
     * Select renderer.
     *
     * IMPORTANT:
     *
     * rectangleMode_ and colorMode_ are independent.
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

    renderProgressBar(
        currentTime,
        duration,
        speed,
        paused
    );

    refresh();
}

// -----------------------------------------------------------------------------
// ASCII renderer
// -----------------------------------------------------------------------------

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
     * Character cells are physically taller than they are wide.
     *
     * cellAspect = width / height
     */

    constexpr double cellAspect = 0.55;

    const double sourceAspect =
        static_cast<double>(sourceWidth) /
        static_cast<double>(sourceHeight);

    const double terminalAspect =
        (static_cast<double>(terminalWidth_) * cellAspect) /
        static_cast<double>(availableHeight);

    int renderWidth;
    int renderHeight;

    if (sourceAspect > terminalAspect)
    {
        renderWidth = terminalWidth_;

        renderHeight =
            static_cast<int>(
                (static_cast<double>(renderWidth) * cellAspect) /
                sourceAspect
            );
    }
    else
    {
        renderHeight = availableHeight;

        renderWidth =
            static_cast<int>(
                (static_cast<double>(renderHeight) * sourceAspect) /
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

    /*
     * Center the image.
     */

    const int offsetX =
        (terminalWidth_ - renderWidth) / 2;

    const int offsetY =
        1 +
        (availableHeight - renderHeight) / 2;

    const int bytesPerPixel = 3;

    for (int y = 0; y < renderHeight; ++y)
    {
        const double sourceY =
            (static_cast<double>(y) + 0.5) *
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

        for (int x = 0; x < renderWidth; ++x)
        {
            const double sourceX =
                (static_cast<double>(x) + 0.5) *
                static_cast<double>(sourceWidth) /
                static_cast<double>(renderWidth);

            const int sx =
                std::clamp(
                    static_cast<int>(sourceX),
                    0,
                    sourceWidth - 1
                );

            const uint8_t* pixel =
                row + sx * bytesPerPixel;

            const unsigned char r = pixel[0];
            const unsigned char g = pixel[1];
            const unsigned char b = pixel[2];

            const char character =
                pixelToAscii(
                    r,
                    g,
                    b
                );

            if (colorMode_ && has_colors())
            {
                int color =
                    pixelToColor(
                        r,
                        g,
                        b
                    );

                int pair =
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

// -----------------------------------------------------------------------------
// Rectangle renderer
// -----------------------------------------------------------------------------

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

    /*
     * Physical terminal cell aspect ratio.
     *
     * Width / height.
     *
     * Increasing this value makes the image physically wider.
     */

    constexpr double cellAspect = 0.55;

    const double sourceAspect =
        static_cast<double>(sourceWidth) /
        static_cast<double>(sourceHeight);

    const double terminalAspect =
        (static_cast<double>(terminalWidth_) * cellAspect) /
        static_cast<double>(availableHeight);

    int renderWidth;
    int renderHeight;

    if (sourceAspect > terminalAspect)
    {
        renderWidth = terminalWidth_;

        renderHeight =
            static_cast<int>(
                (static_cast<double>(renderWidth) * cellAspect) /
                sourceAspect
            );
    }
    else
    {
        renderHeight = availableHeight;

        renderWidth =
            static_cast<int>(
                (static_cast<double>(renderHeight) * sourceAspect) /
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

    /*
     * Center image.
     */

    const int offsetX =
        (terminalWidth_ - renderWidth) / 2;

    const int offsetY =
        1 +
        (availableHeight - renderHeight) / 2;

    /*
     * Each terminal cell represents a rectangular area
     * of the source image.
     *
     * We calculate the average RGB value of that area.
     */

    for (int y = 0; y < renderHeight; ++y)
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

        for (int x = 0; x < renderWidth; ++x)
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
                 sy < sy1 && sy < sourceHeight;
                 ++sy)
            {
                const uint8_t* row =
                    frame->data[0] +
                    sy * frame->linesize[0];

                for (int sx = sx0;
                     sx < sx1 && sx < sourceWidth;
                     ++sx)
                {
                    const uint8_t* pixel =
                        row + sx * 3;

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
             * -------------------------------------------------------------
             * COLOR RECTANGLES
             * -------------------------------------------------------------
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

                /*
                 * Allocate/reuse a manageable range of pairs.
                 *
                 * We cannot assume that COLOR_PAIRS provides one pair
                 * for every xterm color.
                 *
                 * Use a deterministic reduced palette.
                 */

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
                            (color %
                             std::max(
                                 1,
                                 COLOR_PAIRS - 1
                             ));
                    }

                    /*
                     * Reinitialize the pair with the current color.
                     *
                     * This is an approximation because classic ncurses
                     * does not provide unlimited RGB pairs.
                     */

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
                    /*
                     * Fallback if too few color pairs exist.
                     */

                    int basicColor =
                        pixelToColor(
                            r,
                            g,
                            b
                        );

                    int basicPair =
                        basicColor + 1;

                    attron(COLOR_PAIR(basicPair));

                    mvaddch(
                        offsetY + y,
                        offsetX + x,
                        ' '
                    );

                    attroff(COLOR_PAIR(basicPair));
                }
            }

            /*
             * -------------------------------------------------------------
             * GRAY RECTANGLES
             * -------------------------------------------------------------
             */

            else if (!colorMode_ &&
                     has_colors() &&
                     COLORS >= 256 &&
                     COLOR_PAIRS >= 34)
            {
                const double gray =
                    0.2126 * static_cast<double>(r) +
                    0.7152 * static_cast<double>(g) +
                    0.0722 * static_cast<double>(b);

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
             * -------------------------------------------------------------
             * FALLBACK
             * -------------------------------------------------------------
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
}

// -----------------------------------------------------------------------------
// Progress bar
// -----------------------------------------------------------------------------

void AsciiRenderer::renderProgressBar(
    double currentTime,
    double duration,
    double speed,
    bool paused
)
{
    if (terminalHeight_ < 3)
        return;

    const int y =
        terminalHeight_ - 2;

    /*
     * Progress bar width.
     */

    const int barWidth =
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

    move(y, 0);

    for (int i = 0; i < barWidth; ++i)
    {
        if (i < filled)
            addch('=');
        else
            addch('-');
    }

    /*
     * Status line.
     */

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
        terminalWidth_ - 1
    );
}

// -----------------------------------------------------------------------------
// Time formatting
// -----------------------------------------------------------------------------

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
