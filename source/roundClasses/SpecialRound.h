//
// Created by Vali on 17/04/2025.
//

#ifndef SPECIALROUND_H
#define SPECIALROUND_H
#include "Round.h"


class SpecialRound : public Round {
    json dataQO;
    json dataQK;
    json dataQRB;
    const int NUMBER_OF_DERIVED = 3; //de modificat daca se adauga tipuri de intrebari noi
    void generateSpecialQuestion(Family*, Question& question) override;

public:
    SpecialRound(int round_id_, json& data_, json &dataQO_, json &dataQK, json &dataQRB);



};



#endif //SPECIALROUND_H
