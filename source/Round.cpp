//
// Created by Vali on 05/04/2025.
//

#include "Round.h"
#include <iostream>
#include <random>

#include "Family.h"

//Impart in normalRound, specialRound si astfel folosesc functii virtuale pure.
void Round::printCurrentAnswers() {
        for (const auto& item : answers_given) {
            std::cout << item.first << " " << item.second << '\n';
        }
    }
    void Round::printAllAnswers(const Question& question) {
        std::cout<<"Doriti sa vedeti toate raspunsurile posibile la intrebarea primita?"<<'\n';
        std::string see_all_answers;
        std::cin>>see_all_answers;
        if(see_all_answers == "da") {
            std::cout<<"BAREMUL DE RASPUNSURI: ";
            for (const auto& item: question.get_answers()) {
                std::cout<<item.first<<" "<<item.second<<'\n';
            }
        }
    }

int Round::pickRandIndex(json &data) {
        if (data["intrebari"].empty()) {
            return -1;
        }

         std::random_device rd;
         std::mt19937 gen(rd());
         std::uniform_int_distribution<> distr(0, data["intrebari"].size() - 1);
        //NOTA: Nu merge cu static deoarece raman initializate cu size-ul vechi...
        return distr(gen);
    }

    Question Round::getQuestion(json &data_) {

        int randindex = pickRandIndex(data_);


        std::vector<std::pair<std::string, int>> answers;
        for (const auto& item : data_["intrebari"][randindex]["raspunsuri"]) {
            answers.emplace_back(item["raspuns"], item["punctaj"]);
        }
        Question q = Question(data_["intrebari"][randindex]["intrebare"], answers);
        data_["intrebari"].erase(randindex);
        //BUG FIX: nu se sterge intrebarea din json dupa ce a fost folosita.
        return q;
    }
    Family& Round::whoPressedFirst(Family& f1, Family& f2) {
        //FIXED BUG: Daca cineva introduce un string in loc de un numar, programul intra in bucla infinita.
        int pick;
        while (true) {
            std::cout << "Cine a apasat primul? Scrie 1 pentru familia " << f1.get_family_name() << " si 2 pentru familia " << f2.get_family_name() << '\n';
            std::cin >> pick;

            if (std::cin.fail() || (pick != 1 && pick != 2)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                std::cout << "Ai introdus un numar gresit! Introdu 1 sau 2!" << '\n';
            } else {
                break;
            }
        }
    if (pick==1) {
        return f1;
    }
        return f2;


    }

    void Round::SwitchFamily(Family*& currentFamily, Family& f1, Family& f2) {
        if (currentFamily == &f1) {
            currentFamily = &f2;
        } else {
            currentFamily = &f1;
        }
    }


    bool Round::isRoundOverStreaks(Family *leaderFamily, const bool& family_switched) {
    if (leaderFamily->checkStrikes() == 1 && family_switched) {
        std::cout << "Noua familie a primit si ea 3 strikes! S-a terminat runda." << '\n';
        leaderFamily->resetStrikes();
        leaderFamily->set_family_score(leaderFamily->get_family_score());

        return true;
    }
    return false;
    }

    bool Round::isRoundOverAnswers(Family *leaderFamily, std::vector<std::pair<std::string, int>> &answers_given,
        Player& jucator, const std::string& givenAns, const int& givenScore, const int& bonus_multiplier) {
        std::cout << "Raspuns corect! Felicitari!" << '\n';
        answers_given.emplace_back(givenAns, givenScore);
        printCurrentAnswers();
        jucator.increaseScore(givenScore, bonus_multiplier);
        jucator.increaseAnswerStreak();
        if (answers_given.size() == ANSWER_LIMIT) {
            std::cout << "S-au epuizat toate raspunsurile. S-a terminat runda!" << '\n';
            leaderFamily->set_family_score(leaderFamily->get_family_score());
            return true;

        }
        return false;
    }
    void Round::getAnswerFromPlayer(std::string &answer, const Player& jucator) {
    std::cout << jucator << " te rugam sa introduci un raspuns popular: " << "\n";
    std::cin.clear();
    std::getline(std::cin, answer);
    }



    [[nodiscard]] int Round::get_round_id() const {
        return round_id;
    }
    void Round::pickBonus(int& bonus_multiplier) {
    //implementare virtuala ulterioara pentru QRB.
    if (get_round_id() == 6) {
        bonus_multiplier = 2;
    }
    }


    void Round::answerWasWrong(Player& jucator, Family* leaderFamily, Family &f1, Family& f2, bool& family_switched) {
        jucator.resetAnswerStreak();
        std::cout << "Raspuns gresit! Mai incearca!" << '\n';
        leaderFamily->increaseStrikes();
        leaderFamily->set_family_score(leaderFamily->get_family_score());

        std::cout << *leaderFamily;
        if (leaderFamily->checkStrikes() == 1 && !family_switched) {
            std::cout << "Ai primit 3 strikes! Se schimba familia!" << '\n';
            leaderFamily->set_family_score(leaderFamily->get_family_score());
            leaderFamily->resetStrikes();
            SwitchFamily(leaderFamily, f1, f2);
            family_switched = true;
        }
    }

    void Round::playRound(Family& f1, Family& f2) {
        std::cout << "Runda " << round_id << " a inceput" << '\n';

        Question currentQuestion = getQuestion(data);
        std::cout << currentQuestion;
        Family* leaderFamily = &whoPressedFirst(f1, f2);
        std::string givenAns;
        std::cout << *leaderFamily;

        std::string answer;
        std::cin.ignore();

        while (answers_given.size() <= ANSWER_LIMIT && (!family_switched || leaderFamily->checkStrikes() == 0)) {
            for (auto& jucator : leaderFamily->get_players()) {
                getAnswerFromPlayer(answer, jucator);
                pickBonus(bonus_multiplier);
                if (currentQuestion.isAnswerRight(answer, givenScore, givenAns)) {
                    terminateRound = isRoundOverAnswers(leaderFamily, answers_given, jucator, answer, givenScore, bonus_multiplier);
                    if (terminateRound) {
                        break;
                    }
                } else {
                    answerWasWrong( jucator, leaderFamily, f1, f2, family_switched);
                    if (family_switched) {break;}
                    terminateRound = isRoundOverStreaks(leaderFamily,family_switched);
                    if (terminateRound)
                        break;
                }
            }
            if (terminateRound) {
                break;
            }
        }
        leaderFamily->resetStrikes();
        leaderFamily->set_family_score(leaderFamily->get_family_score());
        std::cout << f1 << f2 << '\n';
        printAllAnswers(currentQuestion);
    }

    Round::Round(int round_id_,  json& data_, Family& f1, Family &f2) : data(data_), round_id(round_id_) {

    }

    Round::~Round() = default;


    Round::Round(const Round &other)
        : answers_given(other.answers_given),
          round_id(other.round_id),
          data(other.data) {
    }

    Round& Round::operator=(const Round &other) {
        if (this == &other)
            return *this;
        answers_given = other.answers_given;
        round_id = other.round_id;
        data = other.data;
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const Round& q) {
        os<<q.get_round_id()<<'\n'<<q.answers_given[0].first;
        return os;
    }
    /* Scopul constructorului de copiere, ti-au placut intrebarile dintr-o runda si vrei sa
     * o poti da si altor oameni/prieteni sa o joace sau optiune de 'Genereaza runda custom
     * pe baza acestei runde!' */

