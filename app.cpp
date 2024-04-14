#include "app.hpp"

App::App(int w, int h) {
    height = h;
    width = w;
    life = Life(width, height);
}

void App::start() {
    sf::Event event;
    window = new sf::RenderWindow(sf::VideoMode(width*10, height*10), "The Game of Life");
    window->setFramerateLimit(60);
    while (window->isOpen()) {
        while (window->pollEvent(event)) {
            handleEvent(event);
        }
        render();
    }
}

void App::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window->close();
    }
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::R:
                window->clear();
                life = Life(width, height);
                break;
            case sf::Keyboard::Q:
            case sf::Keyboard::Escape:
                window->close();
                break;
            default:
                break;
        }
    }
}

void App::sleep() {
    std::this_thread::sleep_for(350ms);
}

void App::drawLiveCells() {
    float XSCALE = 10.0, YSCALE = 10.0;
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(XSCALE, YSCALE));
    rect.setFillColor(sf::Color::Green);
    auto coords = life.doTick();
    for (auto m : coords) {
        rect.setPosition(m.first*XSCALE, m.second*YSCALE);
        window->draw(rect);
    }
}

void App::render() {
    window->clear(sf::Color::Black);
    drawLiveCells();
    window->display();
    sleep();
}