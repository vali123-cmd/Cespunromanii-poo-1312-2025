//
// Created by Vali on 05/04/2025.
//
#pragma once

#include <string>
#include <vector>

#include "Player.h"


class Question;

class Family {
    std::string family_name;
    int family_score = 0;
    int strikes = 0;
    std::vector<Player> players;
    [[nodiscard]] int calculate_total_score() const;
public:
    bool useQuestion(Question& question);
    void resetStrikes();
    Family(const Family &other);
    Family & operator=(const Family &other);
    bool checkStrikes();
    void increaseStrikes();
    [[nodiscard]] const std::string& get_family_name() const;
    [[nodiscard]] std::vector<Player>& get_players();
    void set_family_score(int family_score_temp);
    [[nodiscard]] int get_family_score();

    explicit Family(const std::string &family_name, int family_score=0, const std::vector<Player> &players = {});
    friend void swap(Family &lhs, Family &rhs);

    friend std::ostream& operator<<(std::ostream &os, const Family &family);
    bool operator==( const Family& f1) const;

};



