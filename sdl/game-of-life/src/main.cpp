#include <iostream>
#include <SDL.h>
#include <sdl-core.hpp>
#include <game.hpp>

int main(int argc, char** argv) {
    SdlCore::getInstance()->init();
    SDL_Log("%s", SdlCore::getInstance()->name.c_str());

    Game *game = new Game();
    game->plateau = new Plateau();
    game->newGame();
    game->startLoop();

    return EXIT_SUCCESS;
}
