#ifndef GAME_H
#define GAME_H

#include <array>
#include <ncurses.h>
#include <plateau.hpp>

class Game {
    public :
        Game();
        ~Game(); 

        Plateau* plateau;
        
        void setTitle(std::string title);
        
        void run();
        void close();
       
};

#endif
