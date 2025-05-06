#include <fstream>
#include <iostream>

#include "ClipArts.h"
#include "gameClasses/Game.h"
#include "gameClasses/NormalGame.h"
#include "gameClasses/SpecialGame.h"


int main() {
    std::ifstream file("intrebari.json");
    ClipArts art;
    art.printLogo();

    if (!file.is_open()) {
        return 0;
    }
    std::string gameType;
    std::cout << "Introdu tipul jocului (Normal/Special): ";
    std::cin>> gameType;
    Game *game;
    if (gameType == "Normal") {
        game = new NormalGame();


    } else if (gameType == "Special") {
        game = new SpecialGame();
    } else {
        std::cout << "Tip de joc invalid!" << '\n';
        return 0;
    }
    file.close();
    game->playGame();

    delete game;
    return 0;


}
