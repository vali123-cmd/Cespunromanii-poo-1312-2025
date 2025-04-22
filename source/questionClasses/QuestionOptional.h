//
// Created by Vali on 10/04/2025.
//

#ifndef QUESTIONOPTIONAL_H
#define QUESTIONOPTIONAL_H
#include "Family.h"
#include "Question.h"

//O intrebare care iti mareste scorul cu 10% daca raspunzi corect,
//ai dreptul la aceasta, daca o familie castiga fara sa ia vreun streak in vreo runda

class QuestionOptional :public Question{



public:
    QuestionOptional(const std::string& text_, const std::vector<std::pair<std::string, int>>& answers_);
    bool useQuestion(Family &f) override;
    bool isAnswerRight(std::string &userString, int &score, std::string &foundAnswer) override;
    const std::string& get_question_text() override;
    void takeAction(Family& leaderFamily, Family&  f1, Family& f2) override;
};

#endif //QUESTIONOPTIONAL_H
