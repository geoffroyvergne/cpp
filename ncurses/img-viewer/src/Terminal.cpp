#include "Terminal.h"

#include <ncurses.h>

#include <algorithm>
#include <locale.h>

Terminal::Terminal()
{
    setlocale(LC_ALL, "");

    initscr();

    cbreak();
    noecho();

    keypad(stdscr, TRUE);

    curs_set(0);
}

Terminal::~Terminal()
{
    endwin();
}

int displayWidth(const std::string& text)
{
    int width = 0;

    for (size_t i = 0; i < text.size();)
    {
        unsigned char c =
            static_cast<unsigned char>(text[i]);

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

void Terminal::draw(const std::vector<std::string>& lines)
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
             static_cast<int>(lines.size())) / 2
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

    move(rows - 1, 0);

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