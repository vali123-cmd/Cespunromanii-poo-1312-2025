//
// Created by Vali on 05/04/2025.
//
#pragma once
#ifndef ROUND_H
#define ROUND_H
#include <json.hpp>

#include "Family.h"
#include "questionClasses/Question.h"

using json = nlohmann::json;
class Round {


    std::vector<std::pair<std::string, int>> answers_given;



    bool family_switched = false;

    int bonus_multiplier = 1;
    bool terminateRound = false;
    long unsigned int ANSWER_LIMIT = 5;







    static void answerWasWrong(Player& jucator, Family*& leaderFamily, Family &f1, Family& f2, bool& family_switched);
    void pickBonus(int& bonus_multiplier);
    void printCurrentAnswers();
    void printAllAnswers(const Question& question);
    virtual std::unique_ptr<Question> generateSpecialQuestion(Family*);

    static void SwitchFamily(Family *&currentFamily, Family &f1, Family &f2);

    bool isRoundOverAnswers(Family *&leaderFamily, std::vector<std::pair<std::string, int>> &answers_given,
        Player& jucator, const std::string& givenAns, const int& givenScore, const int& bonus_multiplier);






protected:
    json& data;
    int round_id = 1;
    std::unique_ptr<Question> currentQuestion;
    std::string answer;
    std::string givenAns;
    int givenScore = 0;
    void RollTheDice(Family* f);
    static int pickRandIndex(int maxsize);
    static void dataSetup(std::vector<std::pair<std::string,int>>& answers, std::string& text, json& data_);
    static std::unique_ptr<Question> getQuestion(json &data_);
    void loopRound(Family*& leaderFamily, Question& currentQuestion, Family& f1, Family& f2);
    static Family &whoPressedFirst(Family &f1, Family &f2);
    void getAnswerFromPlayer(std::string& answer, const Player& jucator);
public:
    int get_round_id() const;

    Round(int round_id_, json& data_);

    virtual void playRound(Family &f1, Family &f2);

    virtual ~Round();

    Round(const Round &other);

    Round &operator=(const Round &other);

    friend void swap(Round &lhs, Round &rhs) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Round& q);
};



#endif //ROUND_H
