#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <game.hpp>
#include <core.hpp>

int main(int argc, char** argv) {
    Core::getInstance()->init();

    Game *game = new Game();
    SDL_Log("%s", Core::getInstance()->name.c_str());

    game->newLevel(w11); // World 1 - 1
    game->player = new Player();

    game->startLoop();
    
    delete game;

    return EXIT_SUCCESS;
}
