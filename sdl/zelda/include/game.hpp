#include <iostream>
#include <SDL.h>

//#include <map>
//#include <iterator>

#include <player.hpp>
//#include <player-action.hpp>
#include <level.hpp>
#include <sprite-type.hpp>
#include <levels.hpp>

#ifndef GAME
#define GAME

class Game {
    public:
        //Game();
        ~Game();
        std::string name = "Zelda";
        int height = 500;
        int width = 600;
        int loopDelay = 100;        

        Player *player;
        Level *currentLevel;
        
        //void init();
        void addLevel(Levels level);
        void displayDashboard();
        void renderView();
        void startLoop();

        void up();
        void down();
        void right();
        void left();
        void attack();
        
        //void cleanup();
};

#endif