#include <plateau.hpp>

Plateau::Plateau() {

}

Plateau::~Plateau() {

}

void Plateau::init_plateau() {
    for (int i = 0; i < LINES; ++i) {
        std::vector<Cell*> plateau_line;
        for (int j = 0; j < COLS; ++j) {            
            Cell* cell = new Cell(this->randomState(), i, j);
            plateau_line.push_back(cell);
        }
        plateau_array.push_back(plateau_line);
    }

    display_plateau();
}

void Plateau::update_plateau() {
    std::vector<std::vector<Cell*>> temp_plateau_array = plateau_array;    

    /*int newCellValue = 0;
    for (int i = 0; i < plateau_array.size(); ++i) {
        std::vector<Cell*> plateau_line;
        std::vector<Cell*> temp_plateau_line;
        for (int j = 0; j < plateau_array[i].size(); ++j) {     
            newCellValue = checkCellEnvironment(i, j, plateau_array[i][j]->state);

            Cell* newCell = new Cell(this->randomState(), i, j);

            temp_plateau_line.push_back(newCell);
        }
        temp_plateau_array.push_back(temp_plateau_line);
    }*/

    for (int i = 0; i < temp_plateau_array.size(); ++i) {
        for (int j = 0; j < temp_plateau_array[i].size(); ++j) {            
            Cell* cell = plateau_array[i][j];
            Cell* tempCell = temp_plateau_array[i][j];
            //cell->state = this->randomState();

            cell->state = checkCellEnvironment(tempCell->x, tempCell->y, tempCell->state);
        }
    }
    display_plateau();
}

int Plateau::checkCellEnvironment(const int x, const int y, const int state) {

    //if(state == 0) return 1;
    //else return state;

    //if(state == 1) return 0;
    //else return state;

    int aliveCount = 0;
    int deadCount = 0;

    // 1- left y-1
    if(y > 0) {
        if(plateau_array[x][y -1]->state == 1) aliveCount++;
        else deadCount++;
    }

    // 2- right y+1
    if(y+1 < plateau_array[x].size()-1) {
        if(plateau_array[x][y +1]->state == 1) aliveCount++;
        else deadCount++;
    }

    // 3- up x-1
    if(x-1 >= 0) {
        if(plateau_array[x -1][y]->state == 1) aliveCount++;
        else deadCount++; 
    }

    // 4- down x+1
    if(x+1 <= plateau_array.size()-1) {
        if(plateau_array[x +1][y]->state == 1) aliveCount++;
        else deadCount++;
    }

    // regular diagonal 
    // 5- right->up y+1 x-1
    if(y+1 <= plateau_array[x].size() -1 && x-1 >= 0) {
        if(plateau_array[x -1][y +1]->state == 1) aliveCount++;
        else deadCount++;
    }

    // 6- left->down y-1 x+1
    if(y -1 >= 0 && x +1 <= plateau_array.size()-1) {
        if(plateau_array[x +1][y -1]->state == 1) aliveCount++;
        else deadCount++;
    }

    // reverse diagonal
    // 7- left->up y-1 x-1
    if(y -1 >= 0 && x -1 >= 0) {
        if(plateau_array[x -1][y -1]->state == 1) aliveCount++;
        else deadCount++;
    }

    // 8- right->down y+1 x+1
    if(y +1 <= plateau_array[x].size() -1 && x +1 <= plateau_array.size() -1) {
        if(plateau_array[x +1][y +1]->state == 1) aliveCount++;
        else deadCount++;
    }

    // si une cellule a exactement trois voisines vivantes, elle est vivante à l’étape suivante.
    if(aliveCount == 3) return 1;

    // si une cellule a exactement deux voisines vivantes, elle reste dans son état actuel à l’étape suivante.
    if(aliveCount == 2) return state;

    // si une cellule a strictement moins de deux ou strictement plus de trois voisines vivantes, elle est morte à l’étape suivante.
    if(aliveCount < 2 || aliveCount >3) return 0;

    return 0;
}

void Plateau::display_plateau() {
    for (int i = 0; i < plateau_array.size(); ++i) {
        for (int j = 0; j < plateau_array[i].size(); ++j) {                
            Cell* cell = plateau_array[i][j];
            cell->display();
        }
    }
}

int Plateau::randomState() {
    int display_cell = rand()% 2;    
    if (display_cell) return 1;
    else return 0;
}