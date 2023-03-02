#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <sdl-core.hpp>

int main(int argc, char** argv) {

    SdlCore::getInstance()->init();

    Game *game = new Game();
    SDL_Log("%s", SdlCore::getInstance()->name.c_str());

    game->plateau = new Plateau();
    game->currentPiece = new Piece(PieceType::red_circle);
    game->currentPiece->position.x = 3;
    game->currentPiece->position.y = 0;

    game->startLoop();

    return EXIT_SUCCESS;
}
