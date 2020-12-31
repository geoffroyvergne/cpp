#include <iostream>
#include <SDL.h>
#include <game.hpp>

int main(int argc, char** argv) {

    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    game->init();
    //game->loadPlateau();
    game->startLoop();
    game->cleanup();

    free(game);
    return EXIT_SUCCESS;
}
