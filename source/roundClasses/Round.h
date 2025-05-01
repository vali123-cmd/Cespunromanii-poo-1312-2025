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
    json& data;
    int round_id = 1;
    std::vector<std::pair<std::string, int>> answers_given;
    Question* currentQuestion;
    std::string answer;
    std::string givenAns;
    bool family_switched = false;
    int givenScore = 0;
    int bonus_multiplier = 1;
    bool terminateRound = false;
    long unsigned int ANSWER_LIMIT = 5;






    void loopRound(Family* leaderFamily, Question& currentQuestion, Family& f1, Family& f2);
    static void answerWasWrong(Player& jucator, Family* leaderFamily, Family &f1, Family& f2, bool& family_switched);
    void pickBonus(int& bonus_multiplier);
    void printCurrentAnswers();
    void printAllAnswers(const Question& question);
    virtual void generateSpecialQuestion(Family*, Question&);
    static bool checkIfDerived(Question& question);


    static Question* getQuestion(json &data_);

    static Family &whoPressedFirst(Family &f1, Family &f2);

    static void SwitchFamily(Family *&currentFamily, Family &f1, Family &f2);

    bool isRoundOverAnswers(Family *leaderFamily, std::vector<std::pair<std::string, int>> &answers_given,
        Player& jucator, const std::string& givenAns, const int& givenScore, const int& bonus_multiplier);

    //bool isRoundOverStreaks(Family* leaderFamily, const bool& Switched);

    static void getAnswerFromPlayer(std::string& answer, const Player& jucator);
protected:
    static int pickRandIndex(int maxsize);
    static void dataSetup(std::vector<std::pair<std::string,int>>& answers, std::string& text, json& data_);
public:
    int get_round_id() const;

    Round(int round_id_, json& data_);

    void playRound(Family &f1, Family &f2);




    virtual ~Round();

    Round(const Round &other);

    Round &operator=(const Round &other);

    friend std::ostream& operator<<(std::ostream& os, const Round& q);
};



#endif //ROUND_H
