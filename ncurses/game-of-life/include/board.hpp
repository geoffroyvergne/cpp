#ifndef PLATEAU_H
#define PLATEAU_H

#include <array>
#include <ncurses.h>
#include <iostream>
#include <unordered_set>

class Board {
    public :
        Board();
        ~Board(); 

        std::vector<std::vector<int>> current;
        std::vector<std::vector<int>> next;
        std::unordered_set<std::string> history;

        int rows, cols;

        int iterations = 0;
        int running = 1;

        void handle_resize();
        void handle_resize(int newRows, int newCols);
        void display(); 

        void clear();

        void randomize(int density = 20);

        std::string boardHash() const;

        void update();
        int randomState();

        void toggleCell(int x, int y);
        int aliveCount() const;

        int countAliveNeighbours(int x, int y);
        int nextState(int x, int y);

        void addBlinker(int x = 10, int y = 10);
        void addGlider(int x = 10, int y = 10);
        void addPulsar(int x = 10, int y = 10);
};

#endif