#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <piece.hpp>
#include <plateau.hpp>
#include <sdl-core.hpp>

int main(int argc, char** argv) {

    SdlCore::getInstance()->init();

    Game *game = new Game();
    SDL_Log("%s", SdlCore::getInstance()->name.c_str());

    Plateau *plateau = new Plateau();
    game->plateau = plateau;
    
    // Init lastCurrentPiece
    game->currentPiece = new Piece(PieceType::red_circle);
    game->currentPiece->destTextureParams.x = 210;
    game->currentPiece->destTextureParams.y = 210;
    game->currentPiece->position.x = 2;
    game->currentPiece->position.y = 2;

    game->currentPiece = plateau->addCurrentPiece(game->currentPiece, game->currentPlayer);

    game->startLoop();

    //delete game;
    return EXIT_SUCCESS;
}
