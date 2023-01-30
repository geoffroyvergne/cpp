#include <iostream>
#include <vector>
#include <SDL.h>

#include <block.hpp>
//#include <plateau.hpp>
#include <direction.hpp>

#ifndef SNAKE
#define SNAKE

class Snake {
    public:
        Snake();
        ~Snake();

        std::vector<Block*> blockList;        
        Direction currentDirection;

        //void addBlock(Block *block);

        /*void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();*/

        void moveCurrentDirection();
        bool isNewDirection(Direction direction);
        void changeDirection(Direction direction);

        void display();
        void cleanup();
};

#endif
