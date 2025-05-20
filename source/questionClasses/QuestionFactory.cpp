//
// Created by danciu-valentin-nicolae on 16.05.2025.
//

#include "QuestionFactory.h"

std::unique_ptr<Question> QuestionFactory::getQuestion() {
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
            q =  std::make_unique<QuestionMath>(text, answers);
            break;
        default:
            throw OutOfRangeException(0, NUMBER_OF_DERIVED);

    }
    return q;
}