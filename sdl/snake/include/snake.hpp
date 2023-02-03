#include <iostream>
#include <vector>
#include <SDL.h>

#include <block.hpp>
//#include <plateau.hpp>
#include <direction.hpp>
#include <list>

#ifndef SNAKE
#define SNAKE

class Snake {
    public:
        Snake();
        ~Snake();

        //std::vector<Block*> blockList;       
        std::list<Block*> blockList;

        Direction previousDirection; 
        Direction currentDirection;        

        void moveCurrentDirection();
        void changeDirection(Direction direction);
        SDL_Rect getNextPositionByDirection(SDL_Rect destTextureParams, Direction direction);        
        
        bool newDirection = false;
        int size = 1;
        bool reachLimit();
        bool touchTail();
        bool pause;

        void display();
        void cleanup();
};

#endif
