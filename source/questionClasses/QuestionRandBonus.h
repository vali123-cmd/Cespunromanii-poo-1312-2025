//
// Created by Vali on 10/04/2025.
//

#ifndef QUESTIONRANDBONUS_H
#define QUESTIONRANDBONUS_H
#include "Family.h"
#include "Question.h"

/* daca raspunzi corect la aceasta intrebare,
pentru fiecare raspuns corect din intrebarile din runda urmatoarele vei avea un bonus generat random
intre 0 si 10%. ACEASTA VA FI O INTREBARE DE LOGICA
*/

class QuestionRandBonus : public Question
{
    const std::string& get_question_text() override;
public:
    bool useQuestion(Family &f) override;
    std::unique_ptr<Question> clone() const override; // Updated return type
    static double generateBonus();
    QuestionRandBonus(const std::string& text_, const std::vector<std::pair<std::string, int>>& answers_);
    bool isAnswerRight(std::string &userString, int &score, std::string &foundAnswer) override;
    void takeAction(Family& leaderFamily, Family&, Family&) override;
};



#endif //QUESTIONRANDBONUS_H

