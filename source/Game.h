//
// Created by Vali on 05/04/2025.
//
#pragma once

#include "json.hpp"


#include "Player.h"
using json = nlohmann::json;

class Game {
    std::vector<Player> players1;
    std::vector<Player> players2;
    nlohmann::json data;

    void getPlayers(std::vector<Player> &players_, const std::string &family_name);

    void parseJson();

    void playAgain();
public:
    Game();

    ~Game();

    friend std::ostream& operator<<(std::ostream& os, const Game &g);


};



