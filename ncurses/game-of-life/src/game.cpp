#include <unistd.h>
#include <ncurses.h>
#include <cstdint>
#include <string>
#include <iostream>
#include <array>
#include <game.hpp>

#include <ncurses-core.hpp>

Game::Game() {

}

Game::~Game() {

}

void Game::run() {        

    int in_char;

    bool exit_requested = false;

    plateau->init_plateau();

    while(1) {
        in_char = wgetch(NcursesCore::getInstance()->getWindow());

        clear();
        
        plateau->update_plateau();
        
        switch(in_char) {
            case 'q':
                exit_requested = true;
                break;
            default:
                break;
        }
                    
        setTitle("Game of life");

        if(exit_requested) break;

        usleep(100000); // 100 ms

        refresh();
        
    }
}

void Game::setTitle(std::string title) {
    mvaddstr(0, COLS /2 - title.size()/2, title.c_str());
}

void Game::close() {
    endwin();
}
