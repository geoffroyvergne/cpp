#include <board.hpp>

Board::Board() {

}

Board::~Board() {

}

std::vector<std::vector<int>> Board::setPattern(Type type) {
    std::vector<std::vector<int>> boardData;
    
    switch(type) {
        case Type::ship:
            boardData = {
                {0,0,0,1,0},
                {0,0,1,0,0},
                {0,0,1,1,1},
                {0,0,0,0,0},
                {0,0,0,0,0}
            };
            break;

        case Type::blinker:
            boardData = {
                {0,0,0,0,0},
                {0,0,1,0,0},
                {0,0,1,0,0},
                {0,0,1,0,0},
                {0,0,0,0,0}
            };
            
            break;

        default:
            boardData = {
                {0,0,0,0,0},
                {0,0,0,0,0},
                {0,0,0,0,0},
                {0,0,0,0,0},
                {0,0,0,0,0}
            };
            break;
    }
    
    return boardData;
}

void Board::initTable(Type type) {
    boardData = setPattern(type);
}

void Board::display() {
    std::cout << " " << std::endl;

    /*for (int i = 0; i < boardData.size(); i++) {
        for (int j = 0; j < boardData[i].size(); j++) {
            //std::cout << boardData[i][j] << " ";
            std::cout << i << "" << j << ":" << boardData[i][j] << " - ";
        }    
        std::cout << " " << std::endl;
    }
    std::cout << " " << std::endl;*/

    for (int i = 0; i < boardData.size(); i++) {
        for (int j = 0; j < boardData[i].size(); j++) {
            std::cout << boardData[i][j] << " ";
            //std::cout << i << "" << j << ":" << boardData[i][j] << " - ";
        }    
        std::cout << " " << std::endl;
    }
    std::cout << " " << std::endl;
}

void Board::cellsEnvironment() {
    std::vector<Cell> newCellBoard;
    
    /*int countAlive = 0;
    int countDead = 0;

    for(std::vector cellList : boardData) {
        for(int cellInList : cellList) {                        
            if(cellInList == 1) countAlive++;
            if(cellInList == 0) countDead++;
        }
    }*/

    //std::cout << "countAlive : " << countAlive << " countDead : " << countDead << " total : " << countDead + countAlive << std::endl;

    int newCellValue = -1;
    for (int i = 0; i < boardData.size(); i++) {
        for (int j = 0; j < boardData[i].size(); j++) {
            newCellValue = checkCellEnvironment(i, j);

            //Cell c = {newCellValue, i, j};
            /*c.state = newCellValue;
            c.x = i;
            c.y = j;*/
            newCellBoard.push_back({newCellValue, i, j});
            //std::cout << "i" << i << " j" << j << " : " << boardData[i][j] << " -> " << newCellValue << std::endl;     
            //if(newCellValue > -1) boardData[i][j] = newCellValue;
        }
    }

    for (Cell cell : newCellBoard) {
        boardData[cell.x][cell.y] = cell.state;
    }
}

int Board::checkCellEnvironment(int x, int y) {
    int aliveCount = 0;
    int deadCount = 0;

    int cell = boardData[x][y];

    // 1- left y-1
    if(y -1 >= 0) {
        if(boardData[x][y -1] == 1) aliveCount++;
        else deadCount++;
    }

    // 2- right y+1
    if(y +1 <= boardData[x].size() -1) {
        if(boardData[x][y +1] == 1) aliveCount++;
        else deadCount++;
    }

    // 3- up x-1
    if(x -1 >= 0) {
        if(boardData[x -1][y] == 1) aliveCount++;
        else deadCount++; 
    }

    // 4- down x+1
    if(x +1 <= boardData.size() -1) {
        if(boardData[x +1][y] == 1) aliveCount++;
        else deadCount++;
    }

    // regular diagonal 

    // 5- right->up y+1 x-1
    if(y +1 <= boardData[x].size() -1 && x -1 >= 0) {
        if(boardData[x -1][y +1] == 1) aliveCount++;
        else deadCount++;
    }

    // 6- left->down y-1 x+1
    if(y -1 >= 0 && x +1 <= boardData.size() -1) {
        if(boardData[x +1][y -1] == 1) aliveCount++;
        else deadCount++;
    }

    // reverse diagonal

    // 7- left->up y-1 x-1
    if(y -1 >= 0 && x -1 >= 0) {
        if(boardData[x -1][y -1] == 1) aliveCount++;
        else deadCount++;
    }

    // 8- right->down y+1 x+1
    if(y +1 <= boardData[x].size() -1 && x +1 <= boardData.size() -1) {
        if(boardData[x +1][y +1] == 1) aliveCount++;
        else deadCount++;
    }

    //std::cout << "cell : " << cell << " - " << x << "-" << y << " - alive: " << aliveCount << " - dead: " << deadCount << " - total: " << aliveCount + deadCount << std::endl;

    // si une cellule a exactement trois voisines vivantes, elle est vivante à l’étape suivante.
    if(aliveCount == 3) return 1;

    // si une cellule a exactement deux voisines vivantes, elle reste dans son état actuel à l’étape suivante.
    if(aliveCount == 2) return cell;

    // si une cellule a strictement moins de deux ou strictement plus de trois voisines vivantes, elle est morte à l’étape suivante.
    if(aliveCount < 2 || aliveCount >3) return 0;

    return -1;
}
