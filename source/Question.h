//
// Created by Vali on 05/04/2025.
//
#pragma once
#ifndef QUESTION_H
#define QUESTION_H
//#define NOMINMAX //windows headers definesc min si max(eroare la distanta levenstein)


#include <string>
#include <vector>


class Question {
    std::string m_text;
    std::vector<std::pair<std::string, int>> answers;


    void formatAnswer(std::string &s);

    double similarity_percentage(const std::string &s1, const std::string &s2);
public:
    explicit Question(const std::string &text_, const std::vector<std::pair<std::string, int>> &answers_);

    const std::string &get_question_text() const;

    const std::vector<std::pair<std::string, int>> &get_answers() const;

    bool isAnswerRight(std::string &userString, int &score, std::string &foundAnswer);

    Question(const Question &other);

    Question &operator=(const Question &other);
    friend std::ostream& operator<<(std::ostream& os, const Question& q);
};



#endif //QUESTION_H
