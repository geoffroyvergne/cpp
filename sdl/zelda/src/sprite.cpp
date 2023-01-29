#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <sprite.hpp>
#include <core.hpp>

Sprite::Sprite() {
    srcTextureParams = { 1, 11,  15, 16 };
    destTextureParams = { 18, 11,  15, 16 };
}

Sprite::~Sprite() { 
    Core::getInstance()->cleanup();
}

void Sprite::display() {
    SDL_RenderCopy(Core::getInstance()->getRender(), Core::getInstance()->getSdlTextureOverWorld(), &srcTextureParams, &destTextureParams);
}

void Sprite::cleanup() {
    SDL_DestroyTexture(Core::getInstance()->getSdlTextureOverWorld());
}
