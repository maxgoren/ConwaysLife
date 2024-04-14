#ifndef life_hpp
#define life_hpp
#include <iostream>
#include <vector>
using std::rand;
using std::vector;
using std::pair;
using std::make_pair;

class Life {
    private:
        int ticks;
        bool pass;
        int height;
        int width;
        bool **board;
        bool **buffer;
        vector<pair<float,float>> liveCoords;
        void init();
        void lives(int x, int y);
        void dies(int x, int y);
        bool isAlive(bool **curr, int x, int y);
        int checkNeighbors(bool **curr, int x, int y);
        void evaluatePosition(bool** curr, int x, int y);
    public:
        Life(int w = 100, int h = 50, int seed = 1337);
        Life(const Life& life);
        ~Life();
        vector<pair<float,float>> doTick();
        Life& operator=(const Life& life);
};


#endif