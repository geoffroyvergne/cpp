#include "AsciiRenderer.h"
#include "ImageLoader.h"
#include "RenderConfig.h"
#include "Terminal.h"
#include <algorithm>

#include <ncurses.h>

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr
            << "Usage: ascii-image <image>\n";

        return 1;
    }

    try
    {
        Image image =
            ImageLoader::load(argv[1]);

        Terminal terminal;

        RenderConfig config;

        bool running = true;

        while (running)
        {
            int rows;
            int cols;

            terminal.getSize(rows, cols);

            /*
             * Leave one line for the help/status bar.
             */
            const int imageHeight =
                std::max(1, rows - 1);

            if (config.mode == RenderMode::ASCII)
            {
                auto ascii =
                    AsciiRenderer::render(
                        image,
                        cols,
                        imageHeight,
                        config
                    );

                terminal.draw(ascii);
            }
            else
            {
                auto rectangles =
                    AsciiRenderer::renderColored(
                        image,
                        cols,
                        imageHeight,
                        config
                    );

                terminal.drawColored(rectangles);
            }

            /*
             * Display controls.
             */
            terminal.drawStatus(
                "q: quit | +/-: size | b/B: brightness | r: reset"
            );

            int key = terminal.readKey();

            switch (key)
            {
                case 'q':
                case 'Q':
                case 27: // ESC
                    running = false;
                    break;

                case '+':
                case '=':
                    config.size =
                        std::min(
                            2.0,
                            config.size + 0.1
                        );
                    break;

                case '-':
                    config.size =
                        std::max(
                            0.1,
                            config.size - 0.1
                        );
                    break;

                case 'b':
                    config.brightness =
                        std::min(
                            3.0,
                            config.brightness + 0.1
                        );
                    break;

                case 'B':
                    config.brightness =
                        std::max(
                            0.1,
                            config.brightness - 0.1
                        );
                    break;

                case 'r':
                case 'R':
                    config = RenderConfig{};
                    break;

                case 'm':
                case 'M':
                    if (config.mode == RenderMode::ASCII)
                    {
                        config.mode = RenderMode::RECTANGLES;
                    }
                    else
                    {
                        config.mode = RenderMode::ASCII;
                    }
                    break;

                case KEY_RESIZE:
                    // Nothing special to do.
                    // The next iteration recalculates
                    // the dimensions.
                    break;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "Error: "
            << e.what()
            << '\n';

        return 1;
    }

    return 0;
}