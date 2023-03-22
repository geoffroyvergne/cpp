#include <iostream>
#include <SDL.h>
#include <sdl-core.hpp>
#include <game.hpp>
#include <board.hpp>

int main(int argc, char** argv) {
    
    SDL_Log("%s", SdlCore::getInstance()->name.c_str());

    Game *game = new Game();
    game->board = new Board(Pattern::random);
    BoardSize boardSize = game->board->initTable();

    SdlCore::getInstance()->size = 5;

    SdlCore::getInstance()->init(boardSize.x, boardSize.y);

    game->newGame();
    game->startLoop();

    return EXIT_SUCCESS;
}
