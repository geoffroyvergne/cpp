#include <iostream>
#include <SDL.h>

#ifndef CELL
#define CELL

enum class Color {
    black
};

struct Position {
    int caseNumber;
    int x;
    int y;
};

struct NewCell {
    int state;
    int x;
    int y;
};

class Cell {    
    public:
        Cell();
        ~Cell();

        int state = 0;
        Position position;

        SDL_Color color;

        void display();
        void setColor();
        void cleanup();
};

#endif
