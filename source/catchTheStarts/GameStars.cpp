#include "GameStars.h"
#include "Utils.h"

GameStars::GameStars() : window(sf::VideoMode(600, 800), "Catch the Falling Star"), score(0), lives(3), observer(nullptr) {
    basket.setSize({80, 20});
    basket.setFillColor(sf::Color::Green);
    basket.setPosition(260, 760);
}

void GameStars::setObserver(Observer* obs) {
    observer = obs;
}

void GameStars::run(bool& result) {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        handleEvents();
        update(dt, result);
        render();
    }
}

void GameStars::handleEvents() {
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        basket.move(-300.f * clock.getElapsedTime().asSeconds(), 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        basket.move(300.f * clock.getElapsedTime().asSeconds(), 0);
}

void GameStars::update(float dt, bool& result) {
    spawnTimer += dt;
    if (spawnTimer >= 1.f) {
        float x = static_cast<float>(rand() % 580);
        stars.push_back(FallingObjectFactory::createStar(x));
        spawnTimer = 0.f;
    }

    for (auto& star : stars)
        star->update(dt);

    auto it = stars.begin();
    while (it != stars.end()) {
        if (checkCollision(basket, **it)) {
            score.add(1);
            it = stars.erase(it);
        } else if ((*it)->getPosition().y > 800) {
            lives.subtract(1);
            it = stars.erase(it);
        } else {
            ++it;
        }
    }

    if (score.get() >= 5) {
        if (observer) observer->onGameEnd(true, result );
        window.close();
    }

    if (lives.get() <= 0) {
        if (observer) observer->onGameEnd(false, result);
        window.close();
    }
}

void GameStars::render() {
    window.clear();
    window.draw(basket);
    for (auto& star : stars)
        window.draw(*star);
    window.display();
}
