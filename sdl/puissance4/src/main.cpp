#include <iostream>
#include <SDL.h>
#include <game.hpp>

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    game->init(); 

    std::string imagePath = "../assets/images-set.png"; 
    SDL_Texture *sdl_texture = IMG_LoadTexture(game->render, imagePath.c_str());

    game->plateau = new Plateau(game->render, sdl_texture);
    game->message = new Message(game->render);
    game->currentPiece = new Piece(game->render, red_circle, sdl_texture);
    game->startLoop();
    
    game->newGame();

    delete game;

    return EXIT_SUCCESS;
}
