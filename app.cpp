#include "app.hpp"

App::App(int w, int h) {
    height = h;
    width = w;
    life = Life(width, height);
    isRecording = false;
    tick = 0;
}

void App::start() {
    sf::Event event;
    window = new sf::RenderWindow(sf::VideoMode(width*10, height*10), "The Game of Life");
    texture = new sf::RenderTexture();
    texture->create(width*10, height*10);
    window->setFramerateLimit(60);
    while (window->isOpen()) {
        while (window->pollEvent(event)) {
            handleEvent(event);
        }
        render();
        tick++;
    }
    delete window;
    delete texture;
}

void App::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window->close();
    }
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::R:
                life = Life(width, height);
                break;
            case sf::Keyboard::S:
                isRecording = !isRecording;
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
    texture->clear(sf::Color::Black);
    for (auto m : coords) {
        rect.setPosition(m.first*XSCALE, m.second*YSCALE);
        texture->draw(rect);
    }
    texture->display();
}

void App::render() {
    drawLiveCells();
    window->clear();
    sf::Sprite sprite(texture->getTexture());
    window->draw(sprite);
    window->display();
    if (isRecording) saveDisplay();
    sleep();
}

void App::saveDisplay() {
    string name = "tick" + to_string(tick) + ".png";
    sf::Image image = texture->getTexture().copyToImage();
    image.saveToFile(name);
}