//
// Created by Vali on 09/04/2025.
//
#pragma once
#ifndef QUESTIONKILLER_H
#define QUESTIONKILLER_H
#include <unordered_map>

#include "Question.h"
/*Un question killer este o intrebare foarte grea, care are un singur raspuns corect. O familie
are voie sa foloseasca maxim 2 intrebari QuestionKiller pe meci, prin care poate sa ia toate punctele
de la intrebarea initiala */




class QuestionKiller : public Question {

    int calculateDeductedPoints();

    static std::unordered_map<std::string, int> usedQuestionKillers;

public:
    static void takeActionNegative(Family& leaderFamily);
    void takeAction(Family& leaderFamily, Family &f1, Family &f2) override;
    bool useQuestion(Family& family) override;
    QuestionKiller(const std::string& text_, const std::vector<std::pair<std::string, int>>& answers_);
    const std::string& get_question_text() override;
    bool isAnswerRight(std::string &userString, int &score, std::string &foundAnswer) override;
};



#endif //QUESTIONKILLER_H
