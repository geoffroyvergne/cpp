#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <game.hpp>

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    int squareWidth = (game->width -100) / 8;

    game->plateau = new Plateau(game->render, game->sdl_texture_symbols, squareWidth);

    game->startLoop();
    
    delete game;

    return EXIT_SUCCESS;
}
