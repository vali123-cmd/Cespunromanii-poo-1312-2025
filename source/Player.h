//
// Created by Vali on 02/04/2025.
//
#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <string>


class Player {
    int m_score=0;
    std::string m_name;
    std::string m_family;
    int answer_streak = 0;

public:
    void increaseScore( int points_given, int bonus_multiplier);
    void resetAnswerStreak();
    void increaseAnswerStreak();
    [[nodiscard]] int get_player_score() const;
    Player(const Player &other);
    Player & operator=(const Player &other);
    Player(const std::string& name, const std::string& family);
    friend std::ostream& operator<<(std::ostream& os, const Player& p);


};



#endif //PLAYER_H
