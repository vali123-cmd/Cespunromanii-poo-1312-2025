// cppcheck-suppress buildinclude
//
// Created by Vali on 05/04/2025.
//

#include "Round.h"
#include <iostream>
#include <random>

#include "Family.h"
#include "RollDice.h"

#include "questionClasses/QuestionKiller.h"
#include "questionClasses/QuestionMath.h"
#include "questionClasses/QuestionOptional.h"
#include "questionClasses/QuestionRandBonus.h"

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
        std::cin.ignore();
        std::cin.clear();
        if(see_all_answers == "da") {
            std::cout<<"BAREMUL DE RASPUNSURI: ";
            for (const auto& item: question.get_answers()) {
                std::cout<<item.first<<" "<<item.second<<'\n';
            }
        }
    }

int Round::pickRandIndex(int maxsize) {
        if (maxsize == 0) {
            return -1;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, maxsize - 1);
        //NOTA: Nu merge cu static deoarece raman initializate cu size-ul vechi...
        return distr(gen);
    }
    void Round::dataSetup(std::vector<std::pair<std::string,int>>& answers, std::string& text, json& data_) {

        int randindex = pickRandIndex(data_["intrebari"].size());

        text = data_["intrebari"][randindex]["intrebare"];
        for (const auto& item : data_["intrebari"][randindex]["raspunsuri"]) {
            answers.emplace_back(item["raspuns"], item["punctaj"]);
        }

        data_["intrebari"].erase(randindex);

    }


    std::unique_ptr<Question> Round::getQuestion(json &data_) {




        std::vector<std::pair<std::string, int>> answers;
        std::string text;
        dataSetup(answers, text, data_);
        std::unique_ptr<Question> q = std::make_unique<Question>(text,answers);


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




    bool Round::isRoundOverAnswers(Family *&leaderFamily, std::vector<std::pair<std::string, int>> &answers_given_,
        Player& jucator, const std::string& givenAns_, const int& givenScore_, const int& bonus_multiplier_) {

        answers_given_.emplace_back(givenAns_, givenScore_);
        printCurrentAnswers();
        jucator.increaseScore(givenScore_, bonus_multiplier_);
        jucator.increaseAnswerStreak();
        if (answers_given_.size() == (unsigned long long int)ANSWER_LIMIT) {

            std::cout << "S-au epuizat toate raspunsurile. S-a terminat runda!" << '\n';
            leaderFamily->set_family_score(leaderFamily->get_family_score());
            return true;

        }
        return false;
    }
    void Round::getAnswerFromPlayer(std::string &answer, const Player& jucator) {
    std::cout << "\033[31m" << currentQuestion->get_question_text() << "\033[0m\n";
    std::cout<<"----------------------------\n";
    std::cout << jucator << " te rugam sa introduci un raspuns popular: " << "\n";
    std::cin.clear();
    std::getline(std::cin, answer);
    answer.erase(0, answer.find_first_not_of(" \t\n\r\f\v"));
    answer.erase(answer.find_last_not_of(" \t\n\r\f\v") + 1);
    }



    [[nodiscard]] int Round::get_round_id() const {
        return round_id;
    }
    void Round::pickBonus(int& bonus_multiplier_) {
    //implementare virtuala ulterioara pentru QRB.
    if (get_round_id() == 6) {
        bonus_multiplier_ = 2;
    }
    }


    void Round::answerWasWrong(Player& jucator, Family*& leaderFamily, Family &f1, Family& f2, bool& family_switched_) {
        jucator.resetAnswerStreak();
        std::cout << "Raspuns gresit! Mai incearca!" << '\n';
        leaderFamily->increaseStrikes();
        leaderFamily->set_family_score(leaderFamily->get_family_score());

        std::cout << *leaderFamily;
        if (leaderFamily->checkStrikes() == 1 && !family_switched_) {
            std::cout << "Ai primit 3 strikes! Se schimba familia!" << '\n';
            leaderFamily->set_family_score(leaderFamily->get_family_score());
            leaderFamily->resetStrikes();
            SwitchFamily(leaderFamily, f1, f2);
            family_switched_ = true;
        }
    }

    std::unique_ptr<Question> Round::generateSpecialQuestion(Family*) {
        return nullptr;
    }

    void Round::loopRound(Family *&leaderFamily, Question &currentQuestion_, Family &f1, Family &f2) {
    Question copy = currentQuestion_;
    bool restart = false;
    while (answers_given.size() <= ANSWER_LIMIT && (!family_switched || leaderFamily->checkStrikes() == 0)) {
        for (auto& jucator : leaderFamily->get_players()) {

            getAnswerFromPlayer(answer, jucator);
            std::cout<<"Raspunsul dat este: "<<answer<<'\n';

            pickBonus(bonus_multiplier);
            if (currentQuestion_.isAnswerRight(answer, givenScore, givenAns)) {
                terminateRound = isRoundOverAnswers(leaderFamily, answers_given, jucator, answer, givenScore, bonus_multiplier);
                if (terminateRound) {
                    break;
                }
            } else {
                answerWasWrong( jucator, leaderFamily, f1, f2, family_switched);
                if (leaderFamily->checkStrikes() and family_switched) {
                    terminateRound = true;
                    break;
                }
                if (family_switched and restart == 0) {restart =true;
                    break;}
            }
        }
        if (terminateRound) {
            break;
        }
    }
    if (leaderFamily->checkStrikes() == 1) {
        std::cout<<"Noua familie a primit si ea 3 strikes. Runda s-a terminat!"<<'\n';
    }
    leaderFamily->resetStrikes();
    leaderFamily->set_family_score(leaderFamily->get_family_score());

    std::cout << f1 << f2 << '\n';
    printAllAnswers(copy);
    }

    void Round::RollTheDice(Family *f) {
    int choice;
    std::cout<<"Roll the dice, doriti numere reale sau intregi?"<<'\n';
    std::cout<<"1. Reale"<<'\n';
    std::cout<<"2. Intregi"<<'\n';
    std::cin>>choice;
    if (choice == 1) {
        RollDice<float> dice;
        float guess;
        std::cout<<"Introduceti un numar real: "<<'\n';
        std::cin>>guess;
        if (dice.takeGuess(guess)) {
            std::cout<<"Ai ghicit!"<<'\n';
            f->set_family_score(f->get_family_score() + 20);
        } else {
            std::cout<<"Ai gresit!"<<'\n';
        }
    } else if (choice == 2) {
        RollDice<int> dice;
        int guess;
        std::cout<<"Introduceti un numar intreg: "<<'\n';
        std::cin>>guess;
        if (dice.takeGuess(guess)) {
            std::cout<<"Ai ghicit!"<<'\n';
            f->set_family_score(f->get_family_score() + 20);
        } else {
            std::cout<<"Ai gresit!"<<'\n';
        }
    }
    }



    void Round::playRound(Family& f1, Family& f2) {
        std::cout << "Runda " << round_id << " a inceput" << '\n';

        currentQuestion = getQuestion(data);
        std::cout << *currentQuestion;
        Family* leaderFamily = &whoPressedFirst(f1, f2);
        std::cout << *leaderFamily;


        std::cin.ignore();
        loopRound(leaderFamily, *currentQuestion, f1, f2);

        currentQuestion = generateSpecialQuestion(leaderFamily);



    }
    Round::Round(int round_id_,  json& data_) : data(data_), round_id(round_id_), currentQuestion(nullptr) {

    }

    Round::~Round() = default;

    Round::Round(const Round &other)
        : answers_given(other.answers_given),
        data(other.data),
        round_id(other.round_id),
        currentQuestion(other.currentQuestion ? other.currentQuestion->clone() : nullptr)
           {}

    Round& Round::operator=(const Round &other) {
        if (this == &other)
            return *this;

        currentQuestion = other.currentQuestion ? other.currentQuestion->clone() : nullptr;
        answers_given = other.answers_given;
        round_id = other.round_id;
        data = other.data;
        givenScore = other.givenScore;
        bonus_multiplier = other.bonus_multiplier;
        ANSWER_LIMIT = other.ANSWER_LIMIT;

        return *this;
    }

    void swap(Round &lhs , Round &rhs) noexcept {
        using std::swap;
        swap(lhs.round_id, rhs.round_id);
        swap(lhs.answers_given, rhs.answers_given);
        swap(lhs.currentQuestion, rhs.currentQuestion);
        swap(lhs.answer, rhs.answer);
        swap(lhs.givenAns, rhs.givenAns);
        swap(lhs.family_switched, rhs.family_switched);
        swap(lhs.givenScore, rhs.givenScore);
        swap(lhs.bonus_multiplier, rhs.bonus_multiplier);
        swap(lhs.terminateRound, rhs.terminateRound);
    }


    /* Scopul constructorului de copiere, ti-au placut intrebarile dintr-o runda si vrei sa
     * o poti da si altor oameni/prieteni sa o joace sau optiune de 'Genereaza runda custom
     * pe baza acestei runde' */


std::ostream& operator<<(std::ostream& os, const Round& q) {
    os << "Round ID: " << q.get_round_id() << '\n';
    os << "Answers Given:\n";
    if (!q.answers_given.empty()) {
        for (const auto& answer : q.answers_given) {
            os << "- " << answer.first << ": " << answer.second << '\n';
        }
    } else {
        os << "No answers given yet.\n";
    }
    return os;
}