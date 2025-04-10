//
// Created by Vali on 09/04/2025.
//

#include "QuestionKiller.h"

#include <iostream>

const std::string& QuestionKiller::get_question_text(){

    m_text  = "----------------------------------------------------------------------------------------------------------------"
               "\n"
               "               Question Killer\n"
               "-----------------------------------------------------------------------------------------------------\n"
               "               Acesta este un QuestionKiller. Raspunsul tau le poate scadea celeilalte familii din punctaj\n"
                "              cu 50% din punctajul maxim al intrebarii, daca raspunsul este corect."
               "               Le poate oferi randul de a raspunde imediat celeilalte familii. Este permis un singur strike.\n"
               "-----------------------------------------------------------------------------------------------------\n"
                + m_text;
    return m_text;


}
int QuestionKiller::calculateDeductedPoints() {
    int totalPoints = 0;
    for (const auto& answer : answers) {
        totalPoints += answer.second;
    }
    int deductedPoints = totalPoints/2;
    return deductedPoints;
}

bool QuestionKiller::useQuestion() {
    std::cout<<"Doriti sa folositi un Question Killer? (da/nu)"<<'\n';
    std::string answer;
    std::cin>>answer;
    if (answer == "da") {
        std::cout<<"Folositi-l cu intelepciune!"<<'\n';
        return true;
    } else {
        std::cout<<"Succes la intrebarea rundei!"<<'\n';
        return false;
    }
}

QuestionKiller::QuestionKiller(const std::string &text_, const std::vector<std::pair<std::string, int> > &answers_):
Question(text_, answers_) {




}

