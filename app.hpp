#ifndef app_hpp
#define app_hpp
#include "life.hpp"
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
using namespace std;

class App {
    private:
        void sleep();
        void drawLiveCells();
        void render();
        void handleEvent(sf::Event& event);
        int width;
        int height;
        Life life;
        sf::RenderWindow* window;
    public:
        App(int w = 100, int h = 50);
        void start();
};

#endif