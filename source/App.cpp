//
// Created by danciu-valentin-nicolae on 16.05.2025.
//

#include "App.h"

#include <fstream>
#include <iostream>

#include "ClipArts.h"
#include "exceptions/FileReadException.h"
#include "gameClasses/Game.h"
#include "gameClasses/NormalGame.h"
#include "gameClasses/SpecialGame.h"

App& App::getInstance() {
    static App instance;
    return instance;
}

void App::run() {

    ClipArts art;
    art.printLogo();

    std::cout << "\n";
    std::string gameType;
    std::cout << "Introdu tipul jocului (Normal/Special): ";
    std::cin >> gameType;
    std::cout << "\n";
    Game *game;
    if (gameType == "Normal") {
        game = new NormalGame();
    } else  {

        game = new SpecialGame();
    }

    game->playGame();

    std::cout << "\n";
    delete game;
}