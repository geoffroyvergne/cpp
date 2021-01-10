#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <game.hpp>

int main(int argc, char** argv) {
    Game *game = new Game();
    SDL_Log("%s", game->name.c_str());

    game->init();    
    
    game->player = new Player(game->render);
    game->player->sdl_texture = IMG_LoadTexture(game->render, "../assets/link.png");

    game->currentLevel = new Level(game->render);
    SDL_Texture *sdl_texture = IMG_LoadTexture(game->render, "../assets/overworld-tileset.png");
    game->currentLevel->sdl_texture = sdl_texture;

    game->addSpritesLevel();

    game->startLoop();
    
    delete game;

    return EXIT_SUCCESS;
}

