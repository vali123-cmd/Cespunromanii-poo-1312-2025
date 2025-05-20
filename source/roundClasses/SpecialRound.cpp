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
#include "RollDice.h"
SpecialRound::SpecialRound(int round_id_, json &data_, json &dataQO_, json &dataQK, json &dataQRB, json &dataQM):
        Round(round_id_, data_), dataQO(dataQO_), dataQK(dataQK), dataQRB(dataQRB), dataQM(dataQM) {


}

std::unique_ptr<Question> SpecialRound::generateSpecialQuestion(Family*) {
    int randomDerived = pickRandIndex(NUMBER_OF_DERIVED);

    std::unique_ptr<Question> q;
    std::string text;
    std::vector<std::pair<std::string, int>> answers;
    switch (randomDerived) {
        case 0:
            std::cout<<"Intrebare optionala"<<std::endl;
            dataSetup(answers, text, dataQO);

            q = std::make_unique<QuestionOptional>(text, answers);
            break;
        case 1:
            std::cout<<"Intrebare killer"<<std::endl;
            dataSetup(answers, text, dataQRB);

            q = std::make_unique<QuestionKiller>(text, answers);
            break;
        case 2:
            std::cout<<"Intrebare bonus"<<std::endl;
            dataSetup(answers, text, dataQK);

            q = std::make_unique<QuestionRandBonus>(text, answers);
            break;
        case 3:
            std::cout<<"Intrebare matematica"<<std::endl;
            dataSetup(answers, text, dataQM);
            q = std::make_unique<QuestionMath>(text, answers);
            break;
        default:
            throw OutOfRangeException(0, NUMBER_OF_DERIVED);
    }
    return q;

}

void SpecialRound::playRound(Family& f1, Family& f2) {
    std::cout << "Runda " << round_id << " a inceput" << '\n';

    currentQuestion = getQuestion(data);
    std::cout << *currentQuestion;
    Family* leaderFamily = &whoPressedFirst(f1, f2);
    std::cout << *leaderFamily;


    std::cin.ignore();
    loopRound(leaderFamily, *currentQuestion, f1, f2);

    currentQuestion = generateSpecialQuestion(leaderFamily);






        std::cout<<*currentQuestion;
        getAnswerFromPlayer(answer, leaderFamily->get_players()[0]);
        if (currentQuestion->isAnswerRight(answer, givenScore, givenAns)) {
            currentQuestion->takeAction(*leaderFamily, f1, f2);
        }
        else if (dynamic_cast<QuestionKiller*>(currentQuestion.get())) {
            QuestionKiller::takeActionNegative(*leaderFamily);


        }
    if (round_id == 6) {
        RollTheDice(leaderFamily);
    }

    }





