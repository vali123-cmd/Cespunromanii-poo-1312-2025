//
// Created by Vali on 17/04/2025.
//

#include "SpecialRound.h"

#include <iostream>

#include "exceptions/OutOfRangeException.h"
#include "questionClasses/QuestionKiller.h"
#include "questionClasses/QuestionOptional.h"
#include "questionClasses/QuestionRandBonus.h"
#include "questionClasses/QuestionMath.h"

SpecialRound::SpecialRound(int round_id_, json &data_, json &dataQO_, json &dataQK, json &dataQRB, json &dataQM):
        Round(round_id_, data_), dataQO(dataQO_), dataQK(dataQK), dataQRB(dataQRB), dataQM(dataQM) {


}

Question* SpecialRound::generateSpecialQuestion(Family*) {
    int randomDerived = pickRandIndex(NUMBER_OF_DERIVED);

    Question* q;
    std::string text;
    std::vector<std::pair<std::string, int>> answers;
    switch (randomDerived) {
        case 0:
            std::cout<<"Intrebare optionala"<<std::endl;
            dataSetup(answers, text, dataQO);

            q = new QuestionOptional(text, answers);
            break;
        case 1:
            std::cout<<"Intrebare killer"<<std::endl;
            dataSetup(answers, text, dataQRB);

            q = new QuestionKiller(text, answers);
            break;
        case 2:
            std::cout<<"Intrebare bonus"<<std::endl;
            dataSetup(answers, text, dataQK);

            q = new QuestionRandBonus(text, answers);
            break;
        case 3:
            std::cout<<"Intrebare matematica"<<std::endl;
            dataSetup(answers, text, dataQM);
            q = new QuestionMath(text, answers);
            break;
        default:
            throw OutOfRangeException(0, NUMBER_OF_DERIVED);
    }
    return q;

}

