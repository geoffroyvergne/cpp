#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <game.hpp>
#include <cursor.hpp>
#include <core.hpp>

int main(int argc, char** argv) {

    Core::getInstance()->init();

    Game *game = new Game();
    SDL_Log("%s", Core::getInstance()->name.c_str());

    Core::getInstance()->border = 50;
    Core::getInstance()->width = Core::getInstance()->border*10;

    int squareWidth = (Core::getInstance()->width -(Core::getInstance()->border*2)) / 8;
    SDL_Log("squareWidth %d", squareWidth);
    SDL_Log("game->width %d", Core::getInstance()->width);
    SDL_Log("game->border %d", Core::getInstance()->border);

    game->plateau = new Plateau(squareWidth, Core::getInstance()->border);
    game->cursor = new Cursor(squareWidth, Core::getInstance()->border);

    game->startLoop();
    
    delete game;

    return EXIT_SUCCESS;
}
