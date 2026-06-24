#include <board.hpp>
#include <ncurses.h>
#include <ncurses-core.hpp>

Board::Board()
: current(LINES, std::vector<int>(COLS, 0)),
      next(LINES, std::vector<int>(COLS, 0)) {
}

Board::~Board() {

}

void Board::clear() {
    iterations = 0;
    running = 1;
    current.clear();
    for (int x = 0; x < LINES; x++) {
        std::vector<int> current_line;
        for (int y = 0; y < COLS; y++) {            
            current_line.push_back(0);
        }
        current.push_back(current_line);
    }    
}

void Board::randomize(int density) {
    for (int x = 0; x < LINES; x++) {
        for (int y = 0; y < COLS; y++) {            
            current[x][y] = (rand() % 100 < density) ? 1 : 0;
        }
    }
}

void Board::update() {

    if (aliveCount() == 0) return;
    
    for (int x = 0; x < LINES; x++) {
        for (int y = 0; y < COLS; y++) {
            next[x][y] = nextState(x, y);
        }
    }

    if(current == next) {
        running = 0;        
    } else running = 1;

    if (running == 0) return;

    iterations ++;

    std::swap(current, next);
}

void Board::display() {
    for (int i = 0; i < current.size(); ++i) {
        for (int j = 0; j < current[i].size(); ++j) {                
            mvaddch(i, j, current[i][j] ? ACS_CKBOARD : ' ');
            //mvaddch(i, j, current[i][j] ? '#' : ' ');
        }
    }
}

int Board::randomState() {
    return (rand() % 100 < 20) ? 1 : 0;
}

void Board::toggleCell(int x, int y) {
    if (x < 0 || x >= LINES ||
        y < 0 || y >= COLS)
        return;

    current[x][y] = !current[x][y];
}

int Board::aliveCount() const {
    int count = 0;

    for (const auto& row : current) {
        for (int cell : row) {
            count += cell;
        }
    }

    return count;
}

int Board::countAliveNeighbours(int x, int y) {
    int alive = 0;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx < 0 || nx >= LINES)
                continue;

            if (ny < 0 || ny >= COLS)
                continue;

            if (current[nx][ny] == 1)
                alive++;
        }
    }

    return alive;
}

int Board::nextState(int x, int y) {
    int neighbours = countAliveNeighbours(x, y);

    if (current[x][y] == 1) {
        if (neighbours == 2 || neighbours == 3)
            return 1;

        return 0;
    }

    return (neighbours == 3) ? 1 : 0;
}

void Board::addBlinker(int x, int y) {

    if (x < 0 || x >= LINES)
        return;

    if (y < 1 || y >= COLS - 1)
        return;

    current[x][y - 1] = 1;
    current[x][y]     = 1;
    current[x][y + 1] = 1;
}

void Board::addGlider(int x, int y) {

    if (x + 2 >= LINES ||
        y + 2 >= COLS)
        return;

    current[x][y + 1] = 1;
    current[x + 1][y + 2] = 1;

    current[x + 2][y] = 1;
    current[x + 2][y + 1] = 1;
    current[x + 2][y + 2] = 1;
}

void Board::addPulsar(int x, int y) {
    const int offsets[][2] = {
        {-6,-4},{-6,-3},{-6,-2},
        {-6, 2},{-6, 3},{-6, 4},

        {-1,-4},{-1,-3},{-1,-2},
        {-1, 2},{-1, 3},{-1, 4},

        {-4,-6},{-3,-6},{-2,-6},
        { 2,-6},{ 3,-6},{ 4,-6},

        {-4,-1},{-3,-1},{-2,-1},
        { 2,-1},{ 3,-1},{ 4,-1},

        {-4, 1},{-3, 1},{-2, 1},
        { 2, 1},{ 3, 1},{ 4, 1},

        {-4, 6},{-3, 6},{-2, 6},
        { 2, 6},{ 3, 6},{ 4, 6},

        { 1,-4},{ 1,-3},{ 1,-2},
        { 1, 2},{ 1, 3},{ 1, 4},

        { 6,-4},{ 6,-3},{ 6,-2},
        { 6, 2},{ 6, 3},{ 6, 4}
    };

    for (auto& p : offsets) {
        int nx = x + p[0];
        int ny = y + p[1];

        if (nx >= 0 && nx < LINES &&
            ny >= 0 && ny < COLS) {
            current[nx][ny] = 1;
        }
    }
}
