#include "life.hpp"
using namespace std;

void Life::init() {
    board = new bool*[height];
    buffer = new bool*[height];
    for (int y = 0; y < height; y++) {
        board[y] = new bool[width];
        buffer[y] = new bool[width];
        for (int x = 0; x < width; x++) {
            board[y][x] = false;
            buffer[y][x] = false;
        }
    }
}

Life::Life(int w, int h, int seed) {
    width = w;
    height = h;
    init();
    for (int i = 0; i < seed; i++) {
        board[rand() % height][rand() % width] = true;
    }
    pass = true;
}

Life::Life(const Life& life) {
    width = life.width;
    height = life.height;
    init();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            board[y][x] = life.board[y][x];
            buffer[y][x] = life.buffer[y][x];
        }
    }
}

Life& Life::operator=(const Life& life) {
    width = life.width;
    height = life.height;
    init();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            board[y][x] = life.board[y][x];
            buffer[y][x] = life.buffer[y][x];
        }
    }
    return *this;
}

Life::~Life() {
    for (int i = 0; i < height; i++) {
        delete [] board[i];
        delete [] buffer[i];
    }
    delete [] board;
    delete [] buffer;
}

vector<pair<float,float>> Life::doTick() {
    liveCoords.clear();
    bool **currentGeneration = pass ? board:buffer;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            evaluatePosition(currentGeneration, x, y);
        }
    }
    pass = !pass;
    ticks++;
    return liveCoords;
}


bool Life::isAlive(bool **curr, int x, int y) {
    return curr[y][x];
}
int Life::checkNeighbors(bool **curr, int x, int y) {
    int lc = 0;
    int dx[8] = {-1, 0, 1,1,1,-1, 0,-1};
    int dy[8] = {-1,-1,-1,0,1, 1, 1, 0};
    for (int i = 0; i < 8; i++) {
        int nx = ((dx[i]+x)+width) % width;
        int ny = ((dy[i]+y)+height) % height;
        lc += isAlive(curr, nx, ny);
    }
    return lc;
}
void Life::lives(int x, int y) {
    if (!pass) {
        board[y][x] = true;
    } else {
        buffer[y][x] = true;
    }
    liveCoords.push_back(make_pair((float)x,(float)y));
}
void Life::dies(int x, int y) {
    if (!pass) {
        board[y][x] = false;
    } else {
        buffer[y][x] = false;
    }
}
void Life::evaluatePosition(bool** generation, int x, int y) {
    int lc = checkNeighbors(generation, x, y);
    if (isAlive(generation, x, y)) {
        if (lc == 2 || lc == 3) {
            lives(x, y);
        } else {
            dies(x, y);
        }
    } else {
        if (lc == 3) {
            lives(x, y);
        } else {
            dies(x, y);
        }
    }
}