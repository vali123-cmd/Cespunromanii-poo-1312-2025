//
// Created by Vali on 09/04/2025.
//

#include "QuestionKiller.h"

#include <iostream>

#include "Family.h"

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

bool QuestionKiller::useQuestion(Family& family) {
    if (!usedQuestionKillers.contains(family.get_family_name())) {
        usedQuestionKillers[family.get_family_name()] = 0;
    }
    usedQuestionKillers[family.get_family_name()] += 1;
    return usedQuestionKillers[family.get_family_name()] <= 2;
}

QuestionKiller::QuestionKiller(const std::string &text_, const std::vector<std::pair<std::string, int> > &answers_):
Question(text_, answers_) {




}

bool QuestionKiller::isAnswerRight(std::string &userString, int &score, std::string &foundAnswer) {
    // Verificam daca raspunsul este corect
    for (const auto& answer : answers) {
        if (userString == answer.first) {
            foundAnswer = answer.first;
            score = calculateDeductedPoints();
            return true;
        }
    }
    return false;
}