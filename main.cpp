
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <random>
#include <cmath>

#include <queue>


using json = nlohmann::json;
class Player {
    int m_score=0;
    std::string m_name;
    std::string m_family;

public:
    void increaseScore( int points_given, int bonus_multiplier) {
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
    friend std::ostream& operator<<(std::ostream& os, const Player& p);

};
std::ostream& operator<<(std::ostream& os, const Player& p ) {

    std::cout<<"Nume jucator: "<<p.m_name<<" din familia"<< p.m_family<<'\n';
    return os;

}
class Family{
    std::string family_name;
    int family_score = 0;
    int strikes = 0;
    std::vector<Player> players;
    int calculate_score()  const {
        int family_score = 0;
        for (const auto& player : players) {
            family_score += player.m_score1();
        }
        return family_score;
    }
    void resetStrikes() {
        strikes = 0;
    }
public:
    bool checkStrikes() {
        if (strikes == 3) {
            resetStrikes();
            return true;
        }
        return false;
    }
    void increaseStrikes() {
        strikes++;
    }
    [[nodiscard]] std::string family_name1() const {
        return family_name;
    }

    [[nodiscard]] std::vector<Player> players1() const {
        return players;
    }

    void set_family_score(int family_score) {
        this->family_score = family_score;
    }
    [[nodiscard]]  int family_score1()  {
        int computedScore = calculate_score();
        set_family_score(computedScore);
        return family_score;
    }
    Family(const std::string &family_name, int family_score=0, const std::vector<Player> &players = {})
        : family_name(family_name),
          family_score(family_score),
          players(players) {
    }
    friend std::ostream& operator<<(std::ostream& os, const Family& f);
};
std::ostream& operator<<(std::ostream& os, const Family& family) {

    os<<family.family_name1()<<": "<<family.family_score<<'\n';
    os<<"Strikes: "<<family.strikes()<<'\n';
    return os;
}
bool operator==(const Family& f1, const Family& f2) {
    return f1.family_name1() == f2.family_name1();
}
class Question {
    std::string m_text;
    std::vector<std::pair<std::string, int>> answers;


public:
    Question(const std::string& text_, const std::vector<std::pair<std::string, int>>& answers_) {
        m_text = text_;
        answers = answers_;
    }

    [[nodiscard]] std::string m_text1() const {
        return m_text;
    }

    [[nodiscard]] std::vector<std::pair<std::string, int>> answers1() const {
        return answers;
    }

    bool isAnswerRight(std::string userString, int& score) {
        for (const auto& item : answers) {
            if (item.first == userString) {
                score = item.second;
                return 1;
            }
        }
        return 0;
    }
};
std::ostream& operator<<(std::ostream& os, const Question& q) {
    os<<q.m_text1()<<'\n';
    return os;
}


class Round {

    int round_id = 1;
    json data;


    static int pickRandIndex(const json &data) {
        //Functie care alege o intrebare random din json,bazata pe mersenne.
        if (data["intrebari"].empty()) {
            return -1;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, data["intrebari"].size() - 1);

        int randomIndex = distr(gen);

        return randomIndex;
    }
    Question getQuestion(const json &data_) {
        int randindex = pickRandIndex(data_);
        std::vector<std::pair<std::string, int>> answers;
        for (const auto& item : data_["intrebari"][randindex]["raspunsuri"]) {
            answers.push_back(std::make_pair(item["raspuns"], item["punctaj"]));
        }
        Question q = Question(data["intrebari"][randindex]["intrebare"],
            answers);
        data["intrebari"].erase(randindex); //nu vrem sa repetam intrebari, deci stergem.
    }
    const Family& whoPressedFirst(const Family& f1, const Family& f2) {
        std::cout<<"Cine a apasat primul? Scrie 1 pentru familia "<<
            f1.family_name1()<<" si 2 pentru familia "<<f2.family_name1()<<'\n';
        int pick=-1;
        while (pick!=1 and pick!=2) {
            std::cin>>pick;
            if (pick!=1 and pick!=2) {
                std::cout<<"Alege ceva legal!"<<'\n';
            }
        }
        if (pick==1) {
            return f1;
        }
        return f2;
    }
    void SwitchFamily(Family& currentFamily, const Family& f1, const Family& f2) {
         if (currentFamily==f1) {
             currentFamily = f2;
         }
        else {
            currentFamily = f1;
        }
    }

public:

    [[nodiscard]] int round_id1() const {
        return round_id;
    }

    Round(int round_id_, const json &data_, const Family& f1,const Family& f2){
        round_id = round_id_;
        data = data_;
        std::cout<<"Runda "<<round_id<<" a inceput"<<'\n';

        Question currentQuestion =  getQuestion(data);
        Family leaderFamily = whoPressedFirst(f1,f2);
        std::cout<<leaderFamily;
        for (auto& jucator: leaderFamily.players1()) {
            std::cout<<jucator<<" te rugam sa introduci un raspuns popular: "<<"\n";
            std::string answer;
            std::cin>>answer;
            int givenScore = 0;
            int bonus_multiplier = 1;

            if (round_id1()==6) {
                bonus_multiplier = 2;
            }
            if  (currentQuestion.isAnswerRight(answer,givenScore)) {
                std::cout<<"Raspuns corect! Felicitari!"<<'\n';
                jucator.increaseScore(givenScore, bonus_multiplier);
            }
            else {
                std::cout<<"Raspuns gresit! Mai incearca!"<<'\n';
                leaderFamily.increaseStrikes();
                if (leaderFamily.checkStrikes() == 1) {
                    std::cout<<"Ai primit 3 strikes! Se schimba familia!"<<'\n';
                    SwitchFamily(leaderFamily,f1,f2);

                }

            }
        }
    }
    /* Scopul constructorului de copiere, ti-au placut intrebarile dintr-o runda si vrei sa
     * o poti da si altor oameni/prieteni sa o joace sau optiune de 'Genereaza runda custom
     * pe baza acestei runde!' */
};
std::ostream& operator<<(std::ostream& os, const Round& q) {
    os<<q.round_id1()<<'\n';
    return os;
}


class Game {

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
        std::ifstream file("../source/data.json");
    if (!file.is_open()) {
        std::cerr<<"Nu am putut deschide fisierul json!"<<'\n';
        //NOTA: De inchis fereastra atunci cand se intampla asta.
    }
    file >> this->data;

    }



    public:
    Game() {
        parseJson();
        std::string family1;
        std::string family2;
        std::cout << "Salut! Bine ai venit la Family feud/(Ce spun romanii?)! Eu sunt gazda emisiunii, Cabral./"
                "Te rog sa introduci mai jos numele celor doua familii:" << '\n';
        std::cout << "Nume familie 1: " << '\n';
        std::cin >> family1;
        std::cout << "Introdu 5 membri ai primei familii: " << '\n';
        getPlayers(players1, family1);
        Family firstFam(family1, 0, players1);
        std::cout << "Nume familie 2: " << '\n';
        std::cin >> family2;
        getPlayers(players2, family2);
        Family secondFam(family2, 0, players2);

        for (int i=1;i<=6;i++) {

            Round round(i, data,family1,family2);
        }
    }
};

std::ostream& operator<<(std::ostream& os, const Game &g) {
    std::cout<<"Game currently initiated and running. Enjoy! -From Cabral himself."<<'\n';
    return os;
}



int main() {

    Game main;

    return 0;
}