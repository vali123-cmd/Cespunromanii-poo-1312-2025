//
// Created by Vali on 17/04/2025.
//

#ifndef SPECIALROUND_H
#define SPECIALROUND_H
#include "Round.h"


class SpecialRound : public Round {
    bool isRoundOverAnswers(Family *leaderFamily, std::vector<std::pair<std::string, int>> &answers_given,
        Player& jucator, const std::string& givenAns, const int& givenScore, const int& bonus_multiplier) override;

    bool isRoundOverStreaks(Family* leaderFamily, const bool& Switched) override;

public:
    SpecialRound(int round_id_, json &data_, json &dataQO_, json &dataQK, json &dataQRB, Family &f1, Family &f2);



};



#endif //SPECIALROUND_H
