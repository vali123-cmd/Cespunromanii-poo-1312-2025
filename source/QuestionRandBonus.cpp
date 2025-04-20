//
// Created by Vali on 10/04/2025.
//

#include "QuestionRandBonus.h"

#include <iostream>
#include <random>

const std::string& QuestionRandBonus::get_question_text() {
    m_text  = "----------------------------------------------------------------------------------------------------------------"
               "\n"
               "               Question Random Bonus\n"
               "-----------------------------------------------------------------------------------------------------\n"
               "               Acesta este un QuestionRandomBonus. Raspunsul tau corect iti va oferi un bonus \n"
                "              generat random intre 0 si 10%. Ai dreptul la o astfel de intrebare cand unul din jucatorii"
               "               echipei tale atinge un answer streak egal cu 3.\n"
               "-----------------------------------------------------------------------------------------------------\n"
                + m_text;
    return m_text;
}

bool QuestionRandBonus::useQuestion(Family &f) {
    std::cout<<"Doresti sa folosesti intrebarea bonus? (da/nu)"<<std::endl;
    std::string answer;
    std::cin>>answer;
    if(answer == "da")
    {
        return true;
    }
    else if(answer == "nu")
    {
        return false;
    }
    else
    {
        std::cout<<"Raspuns invalid. Te rugam sa introduci 'da' sau 'nu'."<<std::endl;
        return useQuestion(f);
    }
}
double QuestionRandBonus::generateBonus() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 10);
    return dis(gen);
}
QuestionRandBonus::QuestionRandBonus(const std::string &text_, const std::vector<std::pair<std::string, int> > &answers_):
        Question(text_, answers_) {
}

bool QuestionRandBonus::isAnswerRight(std::string &userString, int &score, std::string &foundAnswer) {
    // Verificam daca raspunsul este corect
    for (const auto& answer : answers) {
        if (userString == answer.first) {
            foundAnswer = answer.first;
            score = static_cast<int>(generateBonus());
            return true;
        }
    }
    return false;
}