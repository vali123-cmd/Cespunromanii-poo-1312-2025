//
// Created by Vali on 11/04/2025.
//

#ifndef SPECIALGAME_H
#define SPECIALGAME_H
#include "Game.h"


class SpecialGame : public Game {
    std::vector<Player> players1;
    std::vector<Player> players2;
    nlohmann::json data;
    nlohmann::json dataQK;
    nlohmann::json dataQO;
    nlohmann::json dataQRB;

    void makeRounds(Family &f1, Family &f2)  override;

};



#endif //SPECIALGAME_H
