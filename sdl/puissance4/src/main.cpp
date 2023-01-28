#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <core.hpp>

int main(int argc, char** argv) {

    Core::getInstance()->init();

    Game *game = new Game();
    SDL_Log("%s", Core::getInstance()->name.c_str());

    game->plateau = new Plateau();
    game->currentPiece = new Piece(red_circle);
    game->startLoop();

    return EXIT_SUCCESS;
}
