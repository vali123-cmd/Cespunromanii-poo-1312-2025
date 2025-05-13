#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Tracker.h"
#include "Star.h"
#include "Observer.h"
#include "FallingObjectFactory.h"

class Game {
    sf::RenderWindow window;
    sf::RectangleShape basket;
    std::vector<std::shared_ptr<Star>> stars;
    sf::Clock clock;
    Tracker<int> score;
    Tracker<int> lives;
    Observer* observer;
    float spawnTimer = 0.f;

public:
    Game();
    void setObserver(Observer* obs);
    void run(bool& result);

private:
    void handleEvents();
    void update(float dt, bool& result);
    void render();
};