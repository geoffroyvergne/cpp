#include <plateau.hpp>

Plateau::Plateau() {

}

Plateau::~Plateau() {

}

void Plateau::fill_plateau() {
    for (int i = 0; i < LINES; ++i) {
        //std::vector<std::string> plateau_line;
        std::vector<Cell*> plateau_line;
        for (int j = 0; j < COLS; ++j) {
            int display_cell = rand()% 2;
            /*if (display_cell) plateau_line.push_back("#");
            else plateau_line.push_back(" ");*/

            int state = 0;
            if (display_cell) state = 1;

            Cell* cell = new Cell(state, i, j);
            plateau_line.push_back(cell);
        }
        plateau_array.push_back(plateau_line);
    }
}

void Plateau::update_plateau() {
    plateau_array.clear();
    fill_plateau();
    display_plateau();
}

void Plateau::display_plateau() {
    for (int i = 0; i < plateau_array.size(); ++i) {
        for (int j = 0; j < plateau_array[i].size(); ++j) {                
            //mvaddstr(i, j, plateau_array[i][j].c_str());
            Cell* cell = plateau_array[i][j];
            cell->display();
            //cell->log();
        }
    }
}