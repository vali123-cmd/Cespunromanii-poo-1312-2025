//
// Created by Vali on 09/04/2025.
//
#pragma once
#ifndef QUESTIONKILLER_H
#define QUESTIONKILLER_H
#include "Question.h"
/*Un question killer este o intrebare foarte grea, care are un singur raspuns corect. O familie
are voie sa foloseasca maxim 2 intrebari QuestionKiller pe meci, prin care poate sa ia toate punctele
de la intrebarea initiala */


class QuestionKiller : public Question {
    const std::string& get_question_text();
    int calculateDeductedPoints();
    bool useQuestion();
public:
    QuestionKiller(const std::string& text_, const std::vector<std::pair<std::string, int>>& answers_);
};



#endif //QUESTIONKILLER_H
