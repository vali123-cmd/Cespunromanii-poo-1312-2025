//
// Created by Vali on 02/04/2025.
//

#include "Player.h"

#include <iostream>

void Player::increaseScore( int points_given, int bonus_multiplier) {
    m_score+= points_given*bonus_multiplier;
    //Functie care incrementeaza scorul in functie de punctele raspunsului si bonusul rundei.
}
void Player::resetAnswerStreak() {
    answer_streak = 0;
}
void Player::increaseAnswerStreak() {
    answer_streak++;
}


[[nodiscard]] int Player::get_player_score() const {
    return m_score;
}
Player::Player(const Player &other)
        : m_score(other.m_score),
          m_name(other.m_name),
          m_family(other.m_family),
           answer_streak(other.answer_streak) {
}
Player& Player::operator=(const Player &other) {
    if (this == &other)
        return *this;


    m_score = other.m_score;
    m_name = other.m_name;
    m_family = other.m_family;
    answer_streak = other.answer_streak;
    return *this;
}
Player::Player(const std::string& name, const std::string& family): m_name(name), m_family(family) {
    std::cout<<"Jucatorul "<<m_name<<" din familia "<<m_family<<" a fost initializat cu succes."<<'\n';
}

std::ostream& operator<<(std::ostream& os, const Player& p ) {

    std::cout<<"Nume jucator: "<<p.m_name<<" din familia "<< p.m_family<<'\n';
    return os;

}