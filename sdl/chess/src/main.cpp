#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <game.hpp>
#include <cursor.hpp>

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    game->border = 50;
    game->width = game->border*10;

    int squareWidth = (game->width -(game->border*2)) / 8;

    game->init();
    game->sdl_texture_symbols = IMG_LoadTexture(game->render, "../assets/symbols-v4.png");

    game->plateau = new Plateau(game->render, game->sdl_texture_symbols, squareWidth);
    game->cursor = new Cursor(game->render, game->sdl_texture_symbols, squareWidth, game->border);

    game->startLoop();
    
    delete game;

    return EXIT_SUCCESS;
}
