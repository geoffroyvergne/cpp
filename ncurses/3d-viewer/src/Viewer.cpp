#include "Viewer.h"

#include <ncurses.h>

#include <algorithm>

Viewer::Viewer(const Mesh& mesh)
    : mesh_(mesh),
      rotationX_(0.0f),
      rotationY_(0.0f),
      rotationZ_(0.0f),
      zoom_(1.0f)
{
}

void Viewer::reset()
{
    rotationX_ = 0.0f;
    rotationY_ = 0.0f;
    rotationZ_ = 0.0f;

    zoom_ = 1.0f;
}

void Viewer::resize()
{
    int height;
    int width;

    getmaxyx(stdscr, height, width);

    renderer_.resize(
        width,
        std::max(1, height - 2)
    );
}

void Viewer::handleInput(int key)
{
    constexpr float rotationStep = 0.10f;

    switch (key)
    {
        case 'x':
            rotationX_ -= rotationStep;
            break;

        case 'X':
            rotationX_ += rotationStep;
            break;

        case 'y':
            rotationY_ -= rotationStep;
            break;

        case 'Y':
            rotationY_ += rotationStep;
            break;

        case 'z':
            rotationZ_ -= rotationStep;
            break;

        case 'Z':
            rotationZ_ += rotationStep;
            break;

        case '+':
        case '=':
            zoom_ *= 1.1f;
            zoom_ =
                std::min(zoom_, 20.0f);
            break;

        case '-':
        case '_':
            zoom_ /= 1.1f;
            zoom_ =
                std::max(zoom_, 0.05f);
            break;

        case 'r':
        case 'R':
            reset();
            break;

        default:
            break;
    }
}

void Viewer::drawInterface()
{
    int height;
    int width;

    getmaxyx(stdscr, height, width);

    move(height - 2, 0);

    clrtoeol();

    mvprintw(
        height - 2,
        0,
        "X/x: rotate X   Y/y: rotate Y   Z/z: rotate Z"
    );

    move(height - 1, 0);

    clrtoeol();

    mvprintw(
        height - 1,
        0,
        "+/-: zoom   R: reset   Q: quit   Zoom: %.2f",
        zoom_
    );

    (void)width;
}

void Viewer::run()
{
    initscr();

    cbreak();
    noecho();

    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    curs_set(0);

    // Hide terminal cursor and clear screen.
    //printw("\033[2J");
    //printw("\033[H");

    clear();

    resize();

    bool running = true;

    while (running)
    {
        const int key = getch();

        if (key == 'q' ||
            key == 'Q')
        {
            running = false;
            continue;
        }

        if (key == KEY_RESIZE)
        {
            resize();
            clear();
        }

        if (key != ERR)
        {
            handleInput(key);
        }

        renderer_.clear();

        renderer_.render(
            mesh_,
            rotationX_,
            rotationY_,
            rotationZ_,
            zoom_
        );

        renderer_.present();

        drawInterface();

        refresh();

        napms(16);
    }

    endwin();
}
