//
// Created by Vali on 05/04/2025.
//
#pragma once

#include <json.hpp>


#include "Player.h"
#include "Round.h"
using json = nlohmann::json;

class Game {

    std::vector<Player> players1;
    std::vector<Player> players2;
    nlohmann::json data;
    static void establishWinner(Family &f1, Family &f2);

    static void setUp(std::string& family1, std::string& family2);

    void initPlayers(std::vector<Player> &players_, const std::string &family_name);

    void parseJson();

    void playAgain();

    static void askForAI();

    virtual void makeRounds(Family &f1, Family &f2)  = 0;
    Round *round;

    static bool getRandomBool();



public:
    virtual void playGame();

    virtual ~Game() = default;

    friend std::ostream& operator<<(std::ostream& os, const Game &g);


};



