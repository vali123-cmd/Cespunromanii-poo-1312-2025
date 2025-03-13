
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <cmath>


using json = nlohmann::json;


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

    [[nodiscard]] int m_score1() const {
        return m_score;
    }

    Player(const std::string& name, const std::string& family) {

        m_name = name;
        m_family = family;
        std::cout<<"Jucatorul "<<m_name<<"din familia "<<m_family<<"a fost initializat cu succes."<<'\n';
    }


};
class Family{
    std::string family_name;
    int family_score;
    std::vector<Player> players;
    void calculate_score(const std::vector<Player>& players) {
        for (const auto& player : players) {
            family_score+=player.m_score1();
        }
    }

public:
    [[nodiscard]] std::string family_name1() const {
        return family_name;
    }

    [[nodiscard]] int family_score1()  {
        calculate_score(players);
        return family_score;
    }

    Family(const std::string &family_name, int family_score=0, const std::vector<Player> &players)
        : family_name(family_name),
          family_score(family_score),
          players(players) {
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
    Family family1;
    Family family2;
    int round_id = 1;
    json data;
public:
    Round(const Family &family1, const Family &family2, int round_id, const json &data)
        : family1(family1),
          family2(family2),
          round_id(round_id),
          data(data) {
    }

    /* Scopul constructorului de copiere, ti-au placut intrebarile dintr-o runda si vrei sa
     * o poti da si altor oameni/prieteni sa o joace sau optiune de 'Genereaza runda custom
     * pe baza acestei runde!' */

};


class Game {
    std::pair<std::string, std::string> families;
    std::vector<Player> players1;
    std::vector<Player> players2;
    std::vector<Question> game_questions;
    std::vector<std::pair<std::string, int>> answers;
    json data;
    bool buttonPressed() {
        /* O functie care ar trebui sa detecteze daca un buton a fost apasat,
         * un pic de bataie de cap aici, deoarece trebuie sa facem asta diferit
         * pe Windows/Linux/Mac (cred?!)
         */
        return 1;
    }
    void getPlayers(std::vector<Player>& players_, const std::string& family_name)
    {
        for (int i=0;i<5;i++) {
            std::string member_name;
            std::cout<<"Membru "<< i+1<<": "<<'\n';
            std::cin>>member_name;
            Player player(member_name, family_name);
            players_.push_back(player);

        }
    }
    void parseJson() {
    std::ifstream file("source/data.json");
    if (!file.is_open()) {
        std::cerr<<"Nu am putut deschide fisierul json!"<<'\n';
        //NOTA: De inchis fereastra atunci cand se intampla asta.
    }
    file >> this->data;

    }



    public:
    Game() {
        std::string family1;
        std::string family2;
        std::cout<<"Salut! Bine ai venit la Family feud/(Ce spun romanii?)! Eu sunt gazda emisiunii, Cabral./"
                   "Te rog sa introduci mai jos numele celor doua familii:"<<'\n';
        std::cout<<"Nume familie 1: "<<'\n';
        std::cin>>family1;
        std::cout<<"Introdu 5 membri ai primei familii: "<<'\n';
        getPlayers(players1, family1);
        Family firstFam(family1, 0, players1);
        std::cout<<"Nume familie 2: "<<'\n';
        std::cin>>family2;
        getPlayers(players2, family2);
        Family secondFam(family2, 0, players2);


    }

};




int main() {


    return 0;







}