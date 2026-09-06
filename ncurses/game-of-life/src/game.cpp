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
                
            case KEY_RESIZE: // if terminal resize
                int newRows, newCols;
                getmaxyx(stdscr, newRows, newCols);

                board->handle_resize(newRows, newCols);
                break;
            default:
                break;
        }
}

void Game::setTitle(std::string title) {
    mvprintw(0, 
        COLS /2 - title.size()/2,
        "%s Generation: %ld Alive: %d lines : %d cols %d",
        title.c_str(),
        board->iterations,
        board->aliveCount(),
        board->rows,
        board->cols
    );
}

void Game::close() {
    endwin();
}
