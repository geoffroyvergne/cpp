#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <game.hpp>
#include <cursor.hpp>
#include <sdl-core.hpp>

int main(int argc, char** argv) {

    SdlCore::getInstance()->size = 50;

    SdlCore::getInstance()->width = SdlCore::getInstance()->size*8;
    SdlCore::getInstance()->height = SdlCore::getInstance()->size*8;

    SdlCore::getInstance()->init();

    Game *game = new Game();
    SDL_Log("%s", SdlCore::getInstance()->name.c_str());

    game->board = new Board();
    game->cursor = new Cursor();
    game->cursor->color = game->currentPlayer.color;
    game->cursor->setColor();

    game->startLoop();
    
    delete game;

    return EXIT_SUCCESS;
}
