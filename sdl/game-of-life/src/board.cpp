#include <iostream>
#include <board.hpp>
#include <cell.hpp>
#include <SDL2_gfxPrimitives.h>
#include <sdl-core.hpp>

Board::Board() {

}

Board::~Board() {

}

void Board::initTable(Pattern pattern) {
    boardData = setPattern(pattern);

    int caseNumber = 0;

    for (int i = 0; i < boardData.size(); i++) {
        for (int j = 0; j < boardData[i].size(); j++) {
            //SDL_Log("caseNumber %d i %d j %d", caseNumber, i, j);
            boardData[i][j].position = { caseNumber, j, i };
            caseNumber++;
        }
    }
}

void Board::display() {
    for (int i = 0; i < boardData.size(); i++) {
        for (int j = 0; j < boardData[i].size(); j++) {
            std::cout << boardData[i][j].state << " ";
            //std::cout << i << "" << j << ":" << boardData[i][j] << " - ";
        }    
        std::cout << " " << std::endl;
    }
    std::cout << " " << std::endl;
}

void Board::displayCells() {
    for (int i = 0; i < boardData.size(); i++) {
        for (int j = 0; j < boardData[i].size(); j++) {
            boardData[i][j].display();     
        }
    }
}

void Board::cellsEnvironment() {
    std::vector<NewCell> newCellBoard;

    int newCellValue = -1;
    for (int i = 0; i < boardData.size(); i++) {
        for (int j = 0; j < boardData[i].size(); j++) {
            newCellValue = checkCellEnvironment(i, j);
            newCellBoard.push_back({ newCellValue, i, j });
        }
    }

    for (NewCell newCell : newCellBoard) {
        boardData[newCell.x][newCell.y].state = newCell.state;
    }
}

int Board::checkCellEnvironment(int x, int y) {
    int aliveCount = 0;
    int deadCount = 0;

    Cell cell = boardData[x][y];

    // 1- left y-1
    if(y -1 >= 0) {
        if(boardData[x][y -1].state == 1) aliveCount++;
        else deadCount++;
    }

    // 2- right y+1
    if(y +1 <= boardData[x].size() -1) {
        if(boardData[x][y +1].state == 1) aliveCount++;
        else deadCount++;
    }

    // 3- up x-1
    if(x -1 >= 0) {
        if(boardData[x -1][y].state == 1) aliveCount++;
        else deadCount++; 
    }

    // 4- down x+1
    if(x +1 <= boardData.size() -1) {
        if(boardData[x +1][y].state == 1) aliveCount++;
        else deadCount++;
    }

    // regular diagonal 

    // 5- right->up y+1 x-1
    if(y +1 <= boardData[x].size() -1 && x -1 >= 0) {
        if(boardData[x -1][y +1].state == 1) aliveCount++;
        else deadCount++;
    }

    // 6- left->down y-1 x+1
    if(y -1 >= 0 && x +1 <= boardData.size() -1) {
        if(boardData[x +1][y -1].state == 1) aliveCount++;
        else deadCount++;
    }

    // reverse diagonal

    // 7- left->up y-1 x-1
    if(y -1 >= 0 && x -1 >= 0) {
        if(boardData[x -1][y -1].state == 1) aliveCount++;
        else deadCount++;
    }

    // 8- right->down y+1 x+1
    if(y +1 <= boardData[x].size() -1 && x +1 <= boardData.size() -1) {
        if(boardData[x +1][y +1].state == 1) aliveCount++;
        else deadCount++;
    }

    //std::cout << "cell : " << cell << " - " << x << "-" << y << " - alive: " << aliveCount << " - dead: " << deadCount << " - total: " << aliveCount + deadCount << std::endl;

    // si une cellule a exactement trois voisines vivantes, elle est vivante à l’étape suivante.
    if(aliveCount == 3) return 1;

    // si une cellule a exactement deux voisines vivantes, elle reste dans son état actuel à l’étape suivante.
    if(aliveCount == 2) return cell.state;

    // si une cellule a strictement moins de deux ou strictement plus de trois voisines vivantes, elle est morte à l’étape suivante.
    if(aliveCount < 2 || aliveCount >3) return 0;

    return -1;
}

std::vector<std::vector<Cell>> Board::setPattern(Pattern pattern) {
    std::vector<std::vector<Cell>> boardData;

    Cell* d = new Cell();
    d->state = 0;

    Cell* a = new Cell();
    a->state = 1;
    
    switch(pattern) {
        case Pattern::full:
            boardData = {
                {*a,*a,*a,*a,*a},
                {*a,*a,*a,*a,*a},
                {*a,*a,*a,*a,*a},
                {*a,*a,*a,*a,*a},
                {*a,*a,*a,*a,*a}
            };
            break;
        
        case Pattern::blinker:
            boardData = {
                {*d,*d,*d,*d,*d},
                {*d,*d,*a,*d,*d},
                {*d,*d,*a,*d,*d},
                {*d,*d,*a,*d,*d},
                {*d,*d,*d,*d,*d}
            };
            
            break;

        case Pattern::glider:
            boardData = {
                {*d,*d,*d,*d,*d},
                {*d,*d,*a,*d,*d},
                {*d,*d,*d,*a,*d},
                {*d,*a,*a,*a,*d},
                {*d,*d,*d,*d,*d}
            };
            break;

        case Pattern::light_ship:
            boardData = {
                {*d,*d,*d,*d,*d,*d},
                {*d,*d,*a,*d,*d,*a},
                {*d,*d,*d,*d,*d,*d},
                {*d,*d,*a,*d,*d,*d},
                {*d,*d,*d,*a,*a,*a},
                {*d,*d,*d,*d,*d,*d},
                {*d,*d,*d,*d,*d,*d}
            };
            break;

        

        case Pattern::bloc:
            boardData = {
                {*d,*d,*d,*d},
                {*d,*a,*a,*d},
                {*d,*a,*a,*d},
                {*d,*d,*d,*d}
            };
            break;

        case Pattern::frog:
            boardData = {
                {*d,*d,*d,*d,*d},
                {*d,*a,*a,*a,*d},
                {*a,*a,*a,*d,*d},
                {*d,*d,*d,*d,*d},
                {*d,*d,*d,*d,*d}
            };
            break;

        default:
            boardData = {
                {*d,*d,*d,*d,*d},
                {*d,*d,*d,*d,*d},
                {*d,*d,*d,*d,*d},
                {*d,*d,*d,*d,*d},
                {*d,*d,*d,*d,*d}
            };
            break;
    }
    
    return boardData;
}
