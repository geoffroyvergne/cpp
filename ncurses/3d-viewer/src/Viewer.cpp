#include <locale.h>
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

    getmaxyx(
        stdscr,
        height,
        width
    );

    /*
     * Reserve two terminal lines for the interface.
     */
    renderer_.resize(
        width,
        std::max(
            1,
            height - 2
        )
    );
}

void Viewer::handleInput(int key)
{
    constexpr float rotationStep =
        0.10f;

    switch (key)
    {
        /*
         * X rotation.
         */
        case 'x':
            rotationX_ -= rotationStep;
            break;

        case 'X':
            rotationX_ += rotationStep;
            break;

        /*
         * Y rotation.
         */
        case 'y':
            rotationY_ -= rotationStep;
            break;

        case 'Y':
            rotationY_ += rotationStep;
            break;

        /*
         * Z rotation.
         */
        case 'z':
            rotationZ_ -= rotationStep;
            break;

        case 'Z':
            rotationZ_ += rotationStep;
            break;

        /*
         * Zoom.
         */
        case '+':
        case '=':
            zoom_ *= 1.1f;

            zoom_ =
                std::min(
                    zoom_,
                    20.0f
                );

            break;

        case '-':
        case '_':
            zoom_ /= 1.1f;

            zoom_ =
                std::max(
                    zoom_,
                    0.05f
                );

            break;

        /*
         * Reset.
         */
        case 'r':
        case 'R':
            reset();
            break;

        /*
         * Solid ASCII.
         */
        case 's':
        case 'S':
            renderer_.setMode(
                Renderer::Mode::Solid
            );
            break;

        /*
         * Wireframe.
         */
        case 'w':
        case 'W':
            renderer_.setMode(
                Renderer::Mode::Wireframe
            );
            break;

        /*
         * Unicode half-block.
         */
        case 'u':
        case 'U':
            renderer_.setMode(
                Renderer::Mode::HalfBlock
            );
            break;

        default:
            break;
    }
}

const char* Viewer::modeName() const
{
    switch (renderer_.mode())
    {
        case Renderer::Mode::Solid:
            return "SOLID";

        case Renderer::Mode::Wireframe:
            return "WIREFRAME";

        case Renderer::Mode::HalfBlock:
            return "HALF-BLOCK";
    }

    return "UNKNOWN";
}

void Viewer::drawInterface()
{
    int height;
    int width;

    getmaxyx(
        stdscr,
        height,
        width
    );

    /*
     * First status line.
     */
    move(
        height - 2,
        0
    );

    clrtoeol();

    mvprintw(
        height - 2,
        0,
        "X/x: rotate X   Y/y: rotate Y   Z/z: rotate Z"
    );

    /*
     * Second status line.
     */
    move(
        height - 1,
        0
    );

    clrtoeol();

    mvprintw(
        height - 1,
        0,
        "+/-: zoom   S: solid   W: wireframe   U: half-block   "
        "R: reset   Q: quit   Zoom: %.2f   Mode: %s",
        zoom_,
        modeName()
    );

    (void)width;
}

void Viewer::run()
{
    setlocale(LC_ALL, "");

    initscr();

    cbreak();
    noecho();

    keypad(
        stdscr,
        TRUE
    );

    nodelay(
        stdscr,
        TRUE
    );

    curs_set(0);

    /*
     * Use ncurses exclusively.
     *
     * Do not mix std::cout or ANSI cursor manipulation
     * with ncurses.
     */
    clear();

    resize();

    bool running = true;

    while (running)
    {
        const int key =
            getch();

        if (key == 'q' ||
            key == 'Q')
        {
            running = false;
            continue;
        }

        if (key == KEY_RESIZE)
        {
            clear();
            resize();
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

        /*
         * Approximately 60 FPS.
         */
        napms(16);
    }

    endwin();
}
