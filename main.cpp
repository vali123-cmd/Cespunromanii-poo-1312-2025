#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <json.hpp>
#include <cmath>
#include <curl.h>




class Cabral {
    std::vector<std::string> sayings;
    public:
    explicit Cabral(const std::vector<std::string>& sayings_) {
        sayings = sayings_;
    }


};


class Player {
    int m_score=0;
    std::string m_name;
    std::string m_family;
public:
    void increaseScore(int& m_score, int points_given, int bonus_multiplier) {
        m_score+= points_given*bonus_multiplier;
        //Functie care incrementeaza scorul in functie de punctele raspunsului si bonusul rundei.
    }


    Player(const std::string& name, const std::string& family) {
        m_name = name;
        m_family = family;
    }


};

class Question {
    std::string m_text;
    std::vector<std::pair<std::string, int>> answers;


public:
    explicit Question(const std::string& text_) {
        m_text = text_;
    }

};



class Round {
    std::vector<Question> questions;
    int round_id = 1;
    Player m_p1 = Player("Player1", "Player1");
    Player m_p2 = Player("Player2", "Player2");
public:
    Round(const Player& p1_, const Player& p2_, const std::vector<Question>& questions_, const int round_id_) {
        m_p1 = p1_;
        m_p2 = p2_;
        questions = questions_;
        round_id = round_id_;
    }

    /* Scopul constructorului de copiere, ti-au placut intrebarile dintr-o runda si vrei sa
     * o poti da si altor oameni/prieteni sa o joace sau optiune de 'Genereaza runda custom
     * pe baza acestei runde!' */

    Round(const Round& round_) {
        std::cout <<"Runda a fost copiata cu succes!";
        questions = round_.questions;
        m_p1 = round_.m_p1;
        m_p2 = round_.m_p2;
        round_id = round_.round_id;
    }
    ~Round() {
        std::cout<<"Runda a fost distrusa.";
    }
    Round& operator=(const Round& other) {

        if (this == &other) {
            return *this;
        }
        questions = other.questions;
        m_p1 = other.m_p1;
        m_p2 = other.m_p2;
        round_id = other.round_id;
        return *this;
    }
};


class Game {
    std::vector<Player> players;
    int rounds = 6;
    public:
    explicit Game(const std::vector<Player>& p1_, int number_of_rounds = 6) {
        players = p1_;
        rounds(number_of_rounds);
    }
};



int main() {


    return 0;







}