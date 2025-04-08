//
// Created by Vali on 05/04/2025.
//
#pragma once
#ifndef ROUND_H
#define ROUND_H
#include <json.hpp>

#include "Family.h"
#include "Question.h"

using json = nlohmann::json;
class Round {
    std::vector<std::pair<std::string, int>> answers_given;
    int round_id = 1;
    json data;

    void printCurrentAnswers();
    void printAllAnswers(const Question& question);

    static int pickRandIndex(json &data);

    Question getQuestion(json &data_);

    Family &whoPressedFirst(Family &f1, Family &f2);

    void SwitchFamily(Family *&currentFamily, Family &f1, Family &f2);
public:
    int get_round_id() const;

    Round(int round_id_, json &data_, Family &f1, Family &f2);

    ~Round();

    Round(const Round &other);

    Round &operator=(const Round &other);

    friend std::ostream& operator<<(std::ostream& os, const Round& q);
};



#endif //ROUND_H
