//
// Created by danciu-valentin-nicolae on 07.05.2025.
//

#ifndef QUESTIONMATH_H
#define QUESTIONMATH_H
#include "Question.h"


class QuestionMath : public Question{
    bool isAnswerRight(std::string &userString_, int &score_, std::string &foundAnswer) override;
public:
    QuestionMath* clone() const override;
    QuestionMath(const std::string& text_, const std::vector<std::pair<std::string, int>>& answers_);
    const std::string& get_question_text() override;
    void takeAction(Family& leaderFamily, Family&, Family&) override;

};



#endif //QUESTIONMATH_H
