//
// Created by Vali on 05/04/2025.
//
#pragma once
#ifndef QUESTION_H
#define QUESTION_H
//#define NOMINMAX //windows headers definesc min si max(eroare la distanta levenstein)


#include <memory>
#include <string>
#include <vector>

#include "Family.h"


class Question {
    static void formatAnswer(std::string &s);

    double similarity_percentage(const std::string &s1, const std::string &s2);



protected:
    std::string m_text;
    std::vector<std::pair<std::string, int>> answers;
public:
    virtual std::unique_ptr<Question> clone() const;


    virtual bool useQuestion(Family& family);

    virtual void takeAction(Family& leaderFamily, Family &f1, Family& f2);

    explicit Question(std::string text_, const std::vector<std::pair<std::string, int>> &answers_);

    virtual const std::string &get_question_text();

    const std::vector<std::pair<std::string, int>> &get_answers() const;

    virtual bool isAnswerRight(std::string &userString, int &score, std::string &foundAnswer);

    Question(const Question &other);
    virtual ~Question() = default;

    friend void swap(Question &lhs, Question &rhs) noexcept;

    Question(Question &&other) noexcept;




    Question &operator=(const Question &other);
    friend std::ostream& operator<<(std::ostream& os, Question& q);
};



#endif //QUESTION_H
