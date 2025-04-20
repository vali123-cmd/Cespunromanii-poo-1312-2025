#include <fstream>
#include <iostream>

#include "Game.h"
#include "NormalGame.h"
#include "SpecialGame.h"


int main() {
    std::ifstream file("intrebari.json");

    if (!file.is_open()) {
        return 0;
    }
    std::string gameType;
    std::cout << "Introdu tipul jocului (Normal/Special): ";
    std::cin>> gameType;
    if (gameType == "Normal") {
        NormalGame game;

        game.playGame();
    } else if (gameType == "Special") {
        SpecialGame game;
        game.playGame();
    } else {
        std::cout << "Tip de joc invalid!" << '\n';
    }
    return 0;


}
