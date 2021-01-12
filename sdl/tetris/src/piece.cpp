#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <piece.hpp>
//#include <block.hpp>
#include <block-type.hpp>
//#include <plateau.hpp>

Piece::Piece(SDL_Renderer *render, BlockType type, SDL_Texture *sdl_texture) {
    this->render = render;
    this->sdl_texture = sdl_texture;

    switch(type) {
        case base : 
            addBase(type);
            break;

        case I : 
            addI(type);
            break;
        case Z : 
            addZ(type);
            break;
        case L : 
            addL(type);
            break;
        case J : 
            addJ(type);
            break;
        case T : 
            addT(type);
            break;
        case S : 
            addS(type);
            break;
        case O : 
            addO(type);
            break;
    }

    //std::string imagePath = "../assets/image-set.png"; 
    //sdl_texture = IMG_LoadTexture(render, imagePath.c_str());
   
}

Piece::~Piece() { 
    cleanup();
}

void Piece::addBlock(Block *block) {
     blockList.push_back(block);
}

void Piece::nextPosition() {
    switch(position) {
        case 0 : 
            position = 1;
            break;
        case 1 : 
            position = 2;
            break;
        case 2 : 
            position = 3;
            break;
        case 3 : 
            position = 0;
            break;
    }
}

void Piece::previousPosition() {
    switch(position) {
        case 1 : 
            position = 0;
            break;
        case 2 : 
            position = 1;
            break;
        case 3 : 
            position = 2;
            break;
        case 0 : 
            position = 3;
            break;
    }
}

// Block Base
void Piece::addBase(BlockType type) {
    Block *block = new Block(render, type, sdl_texture);
    addBlock(block);
}

// Block I
void Piece::addI(BlockType type) {
    for(int i=0; i<4; i++) {
        Block *block = new Block(render, type, sdl_texture);
        if(i==1) block->destTextureParams.y += 50;
        if(i==2) block->destTextureParams.y += 100;
        if(i==3) block->destTextureParams.y += 150;
        addBlock(block);
    }
}

void Piece::rotateI(BlockType type) {
    switch(position) {
        case 0 : case 2 :
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.y += 50;
                    if(i==2) blockList[i]->destTextureParams.y += 100;
                    if(i==3) blockList[i]->destTextureParams.y += 150;
                }
                break;
            }
        case 1 : case 3 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.x -= 50;
                    if(i==2) blockList[i]->destTextureParams.x += 50;
                    if(i==3) blockList[i]->destTextureParams.x -= 100;                    
                }
                break;
            }
    }
}

// Block Z
void Piece::addZ(BlockType type) {
    for(int i=0; i<4; i++) {
        Block *block = new Block(render, type, sdl_texture);        
        if(i==1) block->destTextureParams.x -= 50;
        if(i==2) block->destTextureParams.y += 50;
        if(i==3) {
            block->destTextureParams.x += 50;
            block->destTextureParams.y += 50;
        }
        addBlock(block);
    }    
}

void Piece::rotateZ(BlockType type) {
    switch(position) {
        case 0 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.x -= 50;
                    if(i==2) blockList[i]->destTextureParams.y += 50;
                    if(i==3) {
                        blockList[i]->destTextureParams.x += 50;
                        blockList[i]->destTextureParams.y += 50;
                    }
                }
                break;
            }
        case 1 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.x -= 50;                                        
                    if(i==2) blockList[i]->destTextureParams.y -= 50;
                    if(i==3) {
                        blockList[i]->destTextureParams.x -= 50;
                        blockList[i]->destTextureParams.y += 50;
                    }
                }
                break;
            }
        case 2 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.x += 50;
                    if(i==2) blockList[i]->destTextureParams.y -= 50;
                    if(i==3) {
                        blockList[i]->destTextureParams.x -= 50;
                        blockList[i]->destTextureParams.y -= 50;
                    }
                }
                break;
            }
        case 3 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.x -= 50;
                    if(i==2) blockList[i]->destTextureParams.y += 50;
                    if(i==3) {
                        blockList[i]->destTextureParams.x -= 50;
                        blockList[i]->destTextureParams.y -= 50;
                    }
                }
                break;
            }
    }
}

// Block L
void Piece::addL(BlockType type) {
    for(int i=0; i<4; i++) {
        Block *block = new Block(render, type, sdl_texture);
        //block->destTextureParams.y += ((i+1)*50);
        if(i==1) block->destTextureParams.y += 50;
        if(i==2) block->destTextureParams.y += 100;
        if(i==3) {
            block->destTextureParams.x += 50;
            block->destTextureParams.y += 100;
        }
        addBlock(block);
    }
}

void Piece::rotateL(BlockType type) {
    switch(position) {
        case 0 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.y += 50;
                    if(i==2) blockList[i]->destTextureParams.y += 100;
                    if(i==3) {
                        blockList[i]->destTextureParams.x += 50;
                        blockList[i]->destTextureParams.y += 100;
                    }
                }
                break;
            }
        case 1 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY+50;

                    if(i==1) blockList[i]->destTextureParams.x += 50;

                    if(i==2) blockList[i]->destTextureParams.x -= 50;
                    if(i==3) {
                        blockList[i]->destTextureParams.x -= 50;
                        blockList[i]->destTextureParams.y += 50;
                    }
                }
                break;
            }
        case 2 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.y += 50;
                    if(i==2) blockList[i]->destTextureParams.y += 100;
                    if(i==3) blockList[i]->destTextureParams.x -= 50;
                }
                break;
            }
        case 3 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY+50;

                    if(i==1) blockList[i]->destTextureParams.x += 50;

                    if(i==2) blockList[i]->destTextureParams.x -= 50;
                    if(i==3) {
                        blockList[i]->destTextureParams.x += 50;
                        blockList[i]->destTextureParams.y -= 50;
                    }
                }
                break;
            }
    }
}

// Block J
void Piece::addJ(BlockType type) {
    for(int i=0; i<4; i++) {
        Block *block = new Block(render, type, sdl_texture);
        //block->destTextureParams.y += ((i+1)*50);
        if(i==1) block->destTextureParams.y += 50;
        if(i==2) block->destTextureParams.y += 100;
        if(i==3) {
            block->destTextureParams.x -= 50;
            block->destTextureParams.y += 100;
        }
        addBlock(block);
    }
}

void Piece::rotateJ(BlockType type) {
    switch(position) {
        case 0 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.y += 50;
                    if(i==2) blockList[i]->destTextureParams.y += 100;
                    if(i==3) {
                        blockList[i]->destTextureParams.x -= 50;
                        blockList[i]->destTextureParams.y += 100;
                    }
                }
                break;
            }
        case 1 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY+50;

                    if(i==1) blockList[i]->destTextureParams.x += 50;

                    if(i==2) blockList[i]->destTextureParams.x -= 50;
                    if(i==3) {
                        blockList[i]->destTextureParams.x += 50;
                        blockList[i]->destTextureParams.y += 50;
                    }
                }
                break;
            }
        case 2 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.y += 50;
                    if(i==2) blockList[i]->destTextureParams.y += 100;
                    if(i==3) blockList[i]->destTextureParams.x += 50;
                }
                break;
            }
        case 3 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY+50;

                    if(i==1) blockList[i]->destTextureParams.x += 50;

                    if(i==2) blockList[i]->destTextureParams.x -= 50;
                    if(i==3) {
                        blockList[i]->destTextureParams.x -= 50;
                        blockList[i]->destTextureParams.y -= 50;
                    }
                }
                break;
            }
    }
}

// Block T
void Piece::addT(BlockType type) {
    for(int i=0; i<4; i++) {
        Block *block = new Block(render, type, sdl_texture);
        if(i==0) block->destTextureParams.x -= 50;
        if(i==2) block->destTextureParams.x += 50;
        if(i==3) block->destTextureParams.y += 50;
        addBlock(block);
    }
}

void Piece::rotateT(BlockType type) {
    switch(position) {
        case 0 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==0) blockList[i]->destTextureParams.x -= 50;
                    if(i==2) blockList[i]->destTextureParams.x += 50;
                    if(i==3) blockList[i]->destTextureParams.y += 50;
                }
                break;
            }
        case 1 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==0) blockList[i]->destTextureParams.y -= 50;
                    if(i==2) blockList[i]->destTextureParams.y += 50;
                    if(i==3) blockList[i]->destTextureParams.x -= 50;
                }
                break;
            }
        case 2 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==0) blockList[i]->destTextureParams.x -= 50;
                    if(i==2) blockList[i]->destTextureParams.x += 50;
                    if(i==3) blockList[i]->destTextureParams.y -= 50;
                }
                break;
            }
        case 3 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==0) blockList[i]->destTextureParams.y -= 50;
                    if(i==2) blockList[i]->destTextureParams.y += 50;
                    if(i==3) blockList[i]->destTextureParams.x += 50;
                }
                break;
            }
    }
}

// Block S
void Piece::addS(BlockType type) {
    for(int i=0; i<4; i++) {
        Block *block = new Block(render, type, sdl_texture);        
        if(i==1) block->destTextureParams.x += 50;
        if(i==2) block->destTextureParams.y += 50;
        if(i==3) {
            block->destTextureParams.x -= 50;
            block->destTextureParams.y += 50;
        }
        addBlock(block);
    }
}

void Piece::rotateS(BlockType type) {
    //SDL_Log("position %d", position);
    switch(position) {
        case 0 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.x += 50;
                    if(i==2) blockList[i]->destTextureParams.y += 50;
                    if(i==3) {
                        blockList[i]->destTextureParams.x -= 50;
                        blockList[i]->destTextureParams.y += 50;
                    }
                }
                break;
            }
        case 1 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.x -= 50;
                    if(i==2) blockList[i]->destTextureParams.y += 50;
                    if(i==3) {
                        blockList[i]->destTextureParams.x -= 50;
                        blockList[i]->destTextureParams.y -= 50;
                    }
                }
                break;
            }
        case 2 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.x -= 50;
                    if(i==2) blockList[i]->destTextureParams.y -= 50;
                    if(i==3) {
                        blockList[i]->destTextureParams.x += 50;
                        blockList[i]->destTextureParams.y -= 50;
                    }
                }
                break;
            }
        case 3 : 
            {
                for (size_t i = 0; i < this->blockList.size(); ++i) {
                    blockList[i]->destTextureParams.x = positionX;
                    blockList[i]->destTextureParams.y = positionY;

                    if(i==1) blockList[i]->destTextureParams.x += 50;
                    if(i==2) blockList[i]->destTextureParams.y += 50;
                    if(i==3) {
                        blockList[i]->destTextureParams.x += 50;
                        blockList[i]->destTextureParams.y -= 50;
                    }
                }
                break;
            }
    }
}

// Block O
void Piece::addO(BlockType type) {
    for(int i=0; i<4; i++) {
        Block *block = new Block(render, type, sdl_texture);
        if(i==1) block->destTextureParams.y += 50;
        if(i==2) block->destTextureParams.x += 50;
        if(i==3) {
            block->destTextureParams.y += 50;
            block->destTextureParams.x += 50;
        }
        addBlock(block);
    }
}

void Piece::rotateO(BlockType type) {

}

void Piece::moveRight() {
    //if(positionX >400) return; 
    positionX += 50;

    for (size_t i = 0; i < this->blockList.size(); ++i) {
        this->blockList[i]->destTextureParams.x += 50;
    }
}

void Piece::moveLeft() {
    //if(positionX <50) return;
    positionX -= 50;
    //SDL_Log("moveLeft");

    for (size_t i = 0; i < this->blockList.size(); ++i) {
        this->blockList[i]->destTextureParams.x -= 50;
    }

    /*if (plateau->detectCollision()) {
        SDL_Log("Collision");
        moveRight();
    }*/
}

void Piece::moveUp() {
    //if(positionY <100) return;
    positionY -= 50;

    for (size_t i = 0; i < this->blockList.size(); ++i) {
        this->blockList[i]->destTextureParams.y -= 50;
    }
}

void Piece::moveDown() {
    //if(positionY >650) return;
    positionY += 50;

    for (size_t i = 0; i < this->blockList.size(); ++i) {
        this->blockList[i]->destTextureParams.y += 50;
        //std::cout << this->blockList[i]->destTextureParams.y << std::endl;
    }
}

void Piece::display() {
    for (size_t i = 0; i < this->blockList.size(); ++i) {
        this->blockList[i]->display();
    }
}

void Piece::cleanup() {
    for (size_t i = 0; i < this->blockList.size(); ++i) {
        this->blockList[i]->cleanup();
    }
}
