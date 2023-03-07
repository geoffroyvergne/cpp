#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <game.hpp>
#include <player.hpp>

#include <sdl-core.hpp>

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    SdlCore::getInstance()->init();

    game->player1 = new Player("player1", PlayerType::p1);
    game->player1->piece = new Piece(PieceType::none);

    game->player2 = new Player("player2", PlayerType::p2);
    game->player2->piece = new Piece(PieceType::none);
    game->player2->piece->destTextureParams.x = 300;

    game->playerNone = new Player("playerNone", PlayerType::none);

    game->startLoop();    

    delete game;

    return EXIT_SUCCESS;
}
