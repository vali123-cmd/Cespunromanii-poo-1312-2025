//
// Created by Vali on 11/04/2025.
//

#ifndef SPECIALGAME_H
#define SPECIALGAME_H
#include "Game.h"
#include <fstream>


class SpecialGame : public Game {

    nlohmann::json dataQK;
    nlohmann::json dataQO;
    nlohmann::json dataQRB;
    nlohmann::json dataQM;
    void initFiles() override;
    void makeRounds(Family &f1, Family &f2)  override;

};



#endif //SPECIALGAME_H
