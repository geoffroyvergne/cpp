#include "core/Game.h"

#include <iostream>

int main(
    int argc,
    char* argv[])
{
    (void)argc;
    (void)argv;

    try
    {
        Game game;

        if (!game.initialize())
        {
            std::cerr
                << "Failed to initialize game."
                << '\n';

            return 1;
        }

        game.run();

        game.shutdown();
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "Fatal error: "
            << e.what()
            << '\n';

        return 1;
    }

    return 0;
}