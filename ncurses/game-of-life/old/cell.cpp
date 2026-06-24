#include<iostream>
#include <cell.hpp>

Cell::Cell() {

}

Cell::Cell(int state, int x, int y) {
    this->state = state;
    this->x = x;
    this->y = y;
}

Cell::~Cell() {

}

void Cell::display() {
    mvaddstr(this->x, this->y, NcursesCore::getInstance()->getStr(this->state).c_str());
}

void Cell::cleanUp() {

}

void Cell::log() {
    std::cout << "Cell : " << this->state << " " << this->x << " " << this->y << std::endl;
}