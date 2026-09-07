#include "Terminal.h"

#include <ncurses.h>

#include <algorithm>
#include <locale.h>

namespace
{
    constexpr int COLOR_LEVELS = 16;

    //constexpr int COLOR_PAIRS_COUNT = COLOR_LEVELS * COLOR_LEVELS;

    

    /*
     * Convert a 0-15 grayscale level to
     * a 0-1000 ncurses grayscale value.
     */
    int levelToNcursesGray(int level)
    {
        return static_cast<int>(
            level *
            1000.0 /
            (COLOR_LEVELS - 1)
        );
    }

    /*
     * Approximate a grayscale level using
     * the terminal's color palette.
     *
     * We use the standard 256-color grayscale
     * range when available:
     *
     *     232 ... 255
     */
    int levelToColor(int level)
    {
        return 232 +
               static_cast<int>(
                   std::round(
                       level *
                       23.0 /
                       (COLOR_LEVELS - 1)
                   )
               );
    }

    int displayWidth(
        const std::string& text)
    {
        int width = 0;

        for (size_t i = 0;
             i < text.size();)
        {
            unsigned char c =
                static_cast<unsigned char>(
                    text[i]
                );

            if ((c & 0x80) == 0)
                i += 1;
            else if ((c & 0xE0) == 0xC0)
                i += 2;
            else if ((c & 0xF0) == 0xE0)
                i += 3;
            else if ((c & 0xF8) == 0xF0)
                i += 4;
            else
                i += 1;

            ++width;
        }

        return width;
    }
}

Terminal::Terminal()
{
    /*
     * Important for UTF-8 characters such as ▀.
     */
    setlocale(LC_ALL, "");

    initscr();

    cbreak();
    noecho();

    keypad(stdscr, TRUE);

    curs_set(0);

    /*
     * Initialize color support.
     */
    if (has_colors())
    {
        start_color();

        /*
         * Use 256-color mode if supported.
         */
        if (COLORS >= 256)
        {
            use_default_colors();

            /*
             * Create 16 x 16 =
             * 256 possible foreground/background
             * combinations.
             *
             * Pair 0 remains the default pair.
             */
            int pair = 1;

            for (int upper = 0;
                 upper < COLOR_LEVELS;
                 ++upper)
            {
                for (int lower = 0;
                     lower < COLOR_LEVELS;
                     ++lower)
                {
                    if (pair >= COLOR_PAIRS)
                        break;

                    init_pair(
                        pair,
                        levelToColor(upper),
                        levelToColor(lower)
                    );

                    ++pair;
                }
            }
        }
        else
        {
            /*
             * Fallback for terminals without
             * 256-color support.
             */
            init_pair(
                1,
                COLOR_WHITE,
                COLOR_BLACK
            );
        }
    }
}

Terminal::~Terminal()
{
    endwin();
}

void Terminal::getSize(
    int& rows,
    int& cols) const
{
    getmaxyx(
        stdscr,
        rows,
        cols
    );
}

void Terminal::draw(
    const std::vector<std::string>& lines)
{
    ::clear();

    int rows;
    int cols;

    getmaxyx(
        stdscr,
        rows,
        cols
    );

    int startY =
        std::max(
            0,
            (rows - 1 -
             static_cast<int>(
                 lines.size()
             )) / 2
        );

    for (size_t i = 0;
         i < lines.size();
         ++i)
    {
        const int y =
            startY +
            static_cast<int>(i);

        if (y < 0 || y >= rows - 1)
            continue;

        const int textWidth =
            displayWidth(lines[i]);

        const int x =
            std::max(
                0,
                (cols - textWidth) / 2
            );

        if (x >= cols)
            continue;

        mvaddstr(
            y,
            x,
            lines[i].c_str()
        );
    }

    refresh();
}

void Terminal::drawColored(
    const RenderedImage& image)
{
    ::clear();

    int rows;
    int cols;

    getmaxyx(
        stdscr,
        rows,
        cols
    );

    int startY =
        std::max(
            0,
            (rows - 1 -
             static_cast<int>(
                 image.size()
             )) / 2
        );

    for (size_t y = 0;
         y < image.size();
         ++y)
    {
        const int screenY =
            startY +
            static_cast<int>(y);

        if (screenY < 0 ||
            screenY >= rows - 1)
        {
            continue;
        }

        const int width =
            static_cast<int>(
                image[y].size()
            );

        const int startX =
            std::max(
                0,
                (cols - width) / 2
            );

        for (size_t x = 0;
             x < image[y].size();
             ++x)
        {
            const int screenX =
                startX +
                static_cast<int>(x);

            if (screenX < 0 ||
                screenX >= cols)
            {
                continue;
            }

            const RenderCell& cell =
                image[y][x];

            if (has_colors() &&
                COLORS >= 256 &&
                cell.colorPair > 0 &&
                cell.colorPair < COLOR_PAIRS)
            {
                attron(
                    COLOR_PAIR(
                        cell.colorPair
                    )
                );
            }

            mvaddstr(
                screenY,
                screenX,
                cell.character.c_str()
            );

            if (has_colors() &&
                COLORS >= 256 &&
                cell.colorPair > 0 &&
                cell.colorPair < COLOR_PAIRS)
            {
                attroff(
                    COLOR_PAIR(
                        cell.colorPair
                    )
                );
            }
        }
    }

    refresh();
}

void Terminal::drawStatus(
    const std::string& text)
{
    int rows;
    int cols;

    getmaxyx(
        stdscr,
        rows,
        cols
    );

    if (rows <= 0 || cols <= 0)
        return;

    move(
        rows - 1,
        0
    );

    clrtoeol();

    mvaddnstr(
        rows - 1,
        0,
        text.c_str(),
        cols
    );

    refresh();
}

int Terminal::readKey()
{
    return getch();
}