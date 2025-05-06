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
    Question* generateSpecialQuestion(Family*) override;

public:
    SpecialRound(int round_id_, json& data_, json &dataQO_, json &dataQK, json &dataQRB);
    ~SpecialRound() override = default;
 SpecialRound(const SpecialRound &other)
    : Round(other),
      dataQO(other.dataQO),
          dataQK(other.dataQK),
          dataQRB(other.dataQRB),
          NUMBER_OF_DERIVED(other.NUMBER_OF_DERIVED) {
    }

    SpecialRound & operator=(SpecialRound other) {
        using std::swap;
        swap(*this, other);
        return *this;
    }
};



#endif //SPECIALROUND_H
