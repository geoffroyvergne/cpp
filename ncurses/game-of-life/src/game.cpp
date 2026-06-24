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

    while(1) {
        
        in_char = wgetch(NcursesCore::getInstance()->getWindow());        
        
        if (in_char != ERR) {
            handleInput(in_char);
        }
        
        if(exit_requested) break;

        board->update();
        board->display();        

        setTitle("Game of life");        

        //usleep(100000); // 100 ms

        refresh();
        napms(100);        
    }
}

void Game::handleInput(int key) {
    switch(key) {
            case 'q':
                exit_requested = true;
                break;
            case 'c':
                board->clear();                
                break;
            case 'r':
                board->randomize();
                break;
            case 'b':
                board->addBlinker();
                break;            
            case 'g':
                board->addGlider(0, 0);
                break;            
            case 'u':
                board->addPulsar();
                break;      
            default:
                break;
        }
}

void Game::setTitle(std::string title) {
    //mvaddstr(0, COLS /2 - title.size()/2, title.c_str());

    mvprintw(0, 
        COLS /2 - title.size()/2,
        "Generation: %ld Alive: %d",
        board->iterations,
        board->aliveCount());
}

void Game::close() {
    endwin();
}
