#include <iostream>
#include <SDL.h>
#include <game.hpp>
#include <piece.hpp>
#include <plateau.hpp>

int main(int argc, char** argv) {

    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    game->init();

    std::string imagePath = "../assets/images-set.png"; 
    SDL_Texture *sdl_texture = IMG_LoadTexture(game->render, imagePath.c_str());

    Plateau *plateau = new Plateau(game->render, sdl_texture);
    game->plateau = plateau;
    
    // Message
    game->message = new Message(game->render);

    // Init lastCurrentPiece
    game->currentPiece = new Piece(game->render, red_circle, sdl_texture);
    game->currentPiece->destTextureParams.x = 210;
    game->currentPiece->destTextureParams.y = 210;

    game->currentPiece = plateau->addCurrentPiece(game->currentPiece, game->currentPlayer);

    game->startLoop();
    //game->cleanup();

    delete game;
    return EXIT_SUCCESS;
}
