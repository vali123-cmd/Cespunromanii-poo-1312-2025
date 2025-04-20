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
    bool family_switched = false;
    int givenScore = 0;
    int bonus_multiplier = 1;
    bool terminateRound = false;
    const int ANSWER_LIMIT = 5;
    std::vector<std::pair<std::string, int>> answers_given;
    int round_id = 1;
    json data;
    static void answerWasWrong(Player& jucator, Family* leaderFamily, Family &f1, Family& f2, bool& family_switched);
    void pickBonus(int& bonus_multiplier);
    void printCurrentAnswers();
    void printAllAnswers(const Question& question);

    static int pickRandIndex(json &data);

    Question getQuestion(json &data_);

    static Family &whoPressedFirst(Family &f1, Family &f2);

    static void SwitchFamily(Family *&currentFamily, Family &f1, Family &f2);

    virtual bool isRoundOverAnswers(Family *leaderFamily, std::vector<std::pair<std::string, int>> &answers_given,
        Player& jucator, const std::string& givenAns, const int& givenScore, const int& bonus_multiplier);

    virtual bool isRoundOverStreaks(Family* leaderFamily, const bool& Switched);

    static void getAnswerFromPlayer(std::string& answer, const Player& jucator);

public:
    int get_round_id() const;

    Round(int round_id_, json& data_, Family &f1, Family &f2);

    void playRound(Family &f1, Family &f2);

    //TODO: De adaugat functie virtuala playRound. INTERFATA NON-VIRTUALA


    virtual ~Round();

    Round(const Round &other);

    Round &operator=(const Round &other);

    friend std::ostream& operator<<(std::ostream& os, const Round& q);
};



#endif //ROUND_H
