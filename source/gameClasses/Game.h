//
// Created by Vali on 05/04/2025.
//
#pragma once

#include <json.hpp>


#include "Player.h"
#include "roundClasses/Round.h"
#include "Family.h"
using json = nlohmann::json;

class Game {

    std::vector<Player> players1;
    std::vector<Player> players2;
    nlohmann::json data;
    static void establishWinner(Family &f1, Family &f2);

    static void setUp(std::string& family1, std::string& family2);

    void initPlayers(std::vector<Player> &players_, const std::string &family_name);


    virtual void initFiles();
    void playAgain();

    static void askForAI();

    virtual void makeRounds(Family &f1, Family &f2)  = 0;


    static bool getRandomBool();
protected:
    Round *round;
    static void parseJson(const std::string& filePath, json& data);


public:
    void playGame();

    virtual ~Game() = default;

    friend std::ostream& operator<<(std::ostream& os, const Game &g);


};



