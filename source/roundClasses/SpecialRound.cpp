//
// Created by Vali on 17/04/2025.
//

#include "SpecialRound.h"

#include <iostream>

#include "exceptions/OutOfRangeException.h"
#include "questionClasses/QuestionKiller.h"
#include "questionClasses/QuestionOptional.h"
#include "questionClasses/QuestionRandBonus.h"

SpecialRound::SpecialRound(int round_id_, json &data_, json &dataQO_, json &dataQK, json &dataQRB):
        Round(round_id_, data_), dataQO(dataQO_), dataQK(dataQK), dataQRB(dataQRB) {


}

void SpecialRound::generateSpecialQuestion(Family* leaderFamily, Question& question) {
    int randomDerived = pickRandIndex(NUMBER_OF_DERIVED);
    std::cout<<randomDerived<<'\n';
    Question* q;
    std::string text;
    std::vector<std::pair<std::string, int>> answers;
    switch (randomDerived) {
        case 0:
            dataSetup(answers, text, dataQO);
            q = new QuestionOptional(text, answers);
            break;
        case 1:
            dataSetup(answers, text, dataQRB);
            q = new QuestionKiller(text, answers);
            break;
        case 2:
            dataSetup(answers, text, dataQK);
            q = new QuestionRandBonus(text, answers);
            break;
        default:
            throw OutOfRangeException(0, NUMBER_OF_DERIVED);

    }
    question = *q;

    delete q;

}

