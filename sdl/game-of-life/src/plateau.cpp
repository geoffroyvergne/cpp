#include <iostream>
#include <plateau.hpp>
#include <cell.hpp>
#include <SDL2_gfxPrimitives.h>
#include <sdl-core.hpp>

Plateau::Plateau() {

}

Plateau::~Plateau() {

}

void Plateau::clearCellTable() {   
    for(int i=0; i<SdlCore::getInstance()->nbCells; i++) {
        for(int j=0; j<SdlCore::getInstance()->nbCells; j++) {
            
            //State state = State::dead;
                        
            Cell* cell = new Cell();
            cell->position.x = i;
            cell->position.y = j;

            if(dataTable[i][j] == 1) cell->state = 1;
            //if(dataTable[i][j] == 0) state = State::dead;

            cellTable[i][j] = cell;
        }
    }
}

void Plateau::display() {
    //boxRGBA(SdlCore::getInstance()->getRender(), 50, 50, 50, 50, 0, 0, 0, 255);
    std::cout << " " << std::endl;

    for(std::array cellList : cellTable) {
        for(Cell* cellInList : cellList) {
            //if(cellInList->state == State::dead) std::cout << "0 ";
            //if(cellInList->state == 1) std::cout << "1 ";
            //else std::cout << "0 ";
            std::cout << cellInList->state << " ";
        }
        std::cout << " " << std::endl;
    }
    std::cout << " " << std::endl;
}

void Plateau::displayCells() {
    for(std::array cellList : cellTable) {
        for(Cell* cellInList : cellList) {
            if(cellInList->state == 0) continue;
            //if(cellInList == nullptr) continue;
            cellInList->display();
        }
    }

    /*for(int i=0; i<SdlCore::getInstance()->nbCells-1; i++) {
        for(int j=0; j<SdlCore::getInstance()->nbCells-1; j++) {
            if(cellTable[i][j]->state == 0) continue;
            cellTable[i][j]->display();
        }
    }*/
}

void Plateau::cellsEnvironment() {
    //SDL_Log("cellsEnvironment");

    int countAlive = 0;
    int countDead = 0;

    for(std::array cellList : cellTable) {
        for(Cell* cellInList : cellList) {                        
            if(cellInList->state == 1) countAlive++;
            if(cellInList->state == 0) countDead++;
        }
    }

    /*for(int i=0; i<SdlCore::getInstance()->nbCells-1; i++) {
        for(int j=0; j<SdlCore::getInstance()->nbCells-1; j++) {
            if(cellTable[i][j]->state == 0) continue;
            //cellTable[i][j]->display();
            if(cellTable[i][j]->state == 1) countAlive++;
            if(cellTable[i][j]->state == 0) countDead++;
        }
    } */ 

    SDL_Log("countAlive %d countDead %d", countAlive, countDead);

    for(std::array cellList : cellTable) {
        for(Cell* cellInList : cellList) {            
            checkCellEnvironment(cellInList);
        }
    }

    /*for(int i=0; i<SdlCore::getInstance()->nbCells-1; i++) {
        for(int j=0; j<SdlCore::getInstance()->nbCells-1; j++) {
            //if(cellTable[i][j]->state == 0) continue;
            //cellTable[i][j]->display();

            checkCellEnvironment(cellTable[i][j]);
        }
    }*/
}

void Plateau::checkCellEnvironment(Cell* cell) {

    /*
    0 0 0
    0 1 0
    0 0 0
    */

    /*
    0 0 0 1 0
    0 0 1 0 0
    0 0 1 1 1
    0 0 0 0 0
    0 0 0 0 0
    */

    int aliveCount = 0;
    int deadCount = 0;

    // 1- up y-1
    if(cell->position.y -1 >= 0) {
        if(cellTable[cell->position.x][cell->position.y-1]->state == 1) aliveCount++;
        else deadCount++; 
    }

    // 2- down y+1
    if(cell->position.y +1 <= SdlCore::getInstance()->nbCells -1) {
        if(cellTable[cell->position.x][cell->position.y +1]->state == 1) aliveCount++;
        else deadCount++; 
    }

    // 3- left x-1
    if(cell->position.x -1 >= 0) {
        if(cellTable[cell->position.x -1][cell->position.y]->state == 1) aliveCount++;
        else deadCount++; 
    }

    // 4- rignt x+1
    if(cell->position.x +1 <= SdlCore::getInstance()->nbCells -1) {
        if(cellTable[cell->position.x +1][cell->position.y]->state == 1) aliveCount++;
        else deadCount++;
    }

    // regular diagonal 
    // 5- right->up x+1 y-1
    if(cell->position.x +1 <= SdlCore::getInstance()->nbCells -1 && cell->position.y -1 >= 0) {
        if(cellTable[cell->position.x +1][cell->position.y -1]->state == 1) aliveCount++;
        else deadCount++; 
    }

    // 6- left->down x-1 y+1
    if(cell->position.x -1 >= 0 && cell->position.y +1 <= SdlCore::getInstance()->nbCells-1) {
        if(cellTable[cell->position.x -1][cell->position.y +1]->state == 1) aliveCount++;
        else deadCount++; 
    }

    // reverse diagonal
    // 7- left->up x-1 y-1
    if(cell->position.x -1 >= 0 && cell->position.y -1 >= 0) {
        if(cellTable[cell->position.x- 1][cell->position.y -1]->state == 1) aliveCount++;
        else deadCount++; 
    }

    // 8- right->down x+1 y+1
    if(cell->position.x +1 <= SdlCore::getInstance()->nbCells -1 && cell->position.y +1 <= SdlCore::getInstance()->nbCells -1) {
        if(cellTable[cell->position.x +1][cell->position.y +1]->state == 1) aliveCount++;
        else deadCount++; 
    }

/*
   0 1 2 3 4
0  0 0 0 0 0  
1  0 0 0 0 0  
2  0 1 1 1 0  
3  0 0 0 0 0  
4  0 0 0 0 0  

   0 1 2 
0  0 0 0  
1  1 1 1  
2  0 0 0    
*/
       
    //SDL_Log("%d-%d a%d d%d total %d", cell->position.x, cell->position.y, aliveCount, deadCount, aliveCount + deadCount);

    // 1 borne
    /*if(aliveCount == 3) cell->state = 1;

    // 2 stase
    //if(aliveCount == 3) cell->state = 1;

    // 3.1 dead isolation
    if(aliveCount <=1) cell->state = 0;

    // 3.1 death overcroad
    if(aliveCount >=5) cell->state = 0;*/


    // ////////////////

    /*
    0 0 0  
    1 1 1  
    0 0 0  

    0 1 0  
    0 1 0  
    0 1 0  
    */

    //Une cellule morte possédant exactement trois voisines vivantes devient vivante. 
    /*if(cell->state == 0) {
        if(aliveCount == 3) cell->state = 1;
    }

    //Une cellule vivante possédant deux ou trois voisines vivantes reste vivante, sinon elle meurt.
    if(cell->state == 1) {
        if(aliveCount == 2 || aliveCount == 3) cell->state = 1;
    } else {
        cell->state = 0;
    }*/

}
