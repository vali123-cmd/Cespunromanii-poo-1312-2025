//
// Created by Vali on 05/04/2025.
//

#include "Family.h"
#include "questionClasses/Question.h"
#include <iostream>



bool Family::useQuestion(Question& question) {
       return question.useQuestion(*this);
}

void Family::resetStrikes() {
    strikes = 0;
}
[[nodiscard]] int Family::calculate_total_score()  const {
    int family_score_temp = 0;
    for (const auto& player : players) {
        family_score_temp += player.get_player_score();
    }
    return family_score_temp;
}

Family::Family(const Family &other)
    : family_name(other.family_name),
      family_score(other.family_score),

      strikes(other.strikes),
      players(other.players) {
}

Family& Family::operator=(const Family &other) {
    if (this == &other)
        return *this;
    family_name = other.family_name;
    family_score = other.family_score;
    strikes = other.strikes;
    players = other.players;
    return *this;
}

bool Family::checkStrikes() {
    if (strikes == 3) {

        return true;
    }
    return false;
}
void Family::increaseStrikes() {
    strikes++;
}
[[nodiscard]] const std::string& Family::get_family_name() const {
    return family_name;
}

[[nodiscard]]  std::vector<Player>& Family::get_players() {
    return players;
}

void Family::set_family_score(int family_score_temp) {
    this->family_score = family_score_temp;
}
[[nodiscard]]  int Family::get_family_score()  {
    int computedScore = calculate_total_score();
    return computedScore;
}
 Family::Family(const std::string &family_name, const int family_score, const std::vector<Player> &players)
    : family_name(family_name),
      family_score(family_score),
      players(players) {
}
std::ostream& operator<<(std::ostream &os, const Family &family) {
    os<<family.get_family_name()<<": "<<family.family_score<<'\n'<<"CAPITAN: "<<family.players[0]; //NOTA:Adaugare compunere de apeluri <<
    os<<"Strikes: "<<family.strikes<<'\n';
    return os;
}

bool Family::operator==(const Family& f1) {
    return this->get_family_name() == f1.get_family_name();
}