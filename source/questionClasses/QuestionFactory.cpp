//
// Created by danciu-valentin-nicolae on 16.05.2025.
//

#include "QuestionFactory.h"

Question *QuestionFactory::getQuestion() {
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