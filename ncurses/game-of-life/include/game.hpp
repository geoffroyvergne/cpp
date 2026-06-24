#ifndef GAME_H
#define GAME_H

#include <array>
#include <ncurses.h>
#include <board.hpp>

class Game {
    public :
        Game();
        ~Game(); 

        Board* board;
        
        void handleInput(int key);
        void setTitle(std::string title);
        
        void run();
        void close();
       
    private:
        bool exit_requested = false;
};

#endif
