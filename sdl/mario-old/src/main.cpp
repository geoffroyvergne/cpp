#include <iostream>
#include <vector>

#include <SDL.h>

#include <settings.hpp>
#include <game.hpp>

int main(int argc, char** argv) {
    SDL_Log("Mario!");

    Game *game = new Game();

    game->init("Mario", width, height);

    game->loadLevel(1);

    game->startLoop();

    game->cleanup();
    free(game);

    return EXIT_SUCCESS;
}
