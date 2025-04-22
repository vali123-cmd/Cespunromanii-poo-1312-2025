//
// Created by Vali on 05/04/2025.
//

#include "Game.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <bits/random.h>

#include "AI.h"
#include "Family.h"
#include "exceptions/FileReadException.h"
#include "NormalGame.h"
#include "Player.h"
#include "roundClasses/Round.h"
#include "SpecialGame.h"
/* bool buttonPressed() {
        O functie care ar trebui sa detecteze daca un buton a fost apasat,
          un pic de bataie de cap aici, deoarece trebuie sa facem asta diferit
          pe Windows/Linux/Mac (cred?!)

        return 1;
    }*/
    void Game::establishWinner(Family &firstFam, Family &secondFam)  {
        if(firstFam.get_family_score()>secondFam.get_family_score()) {
            std::cout<<"Familia "<<firstFam.get_family_name()<<" a castigat!"<<'\n';
        }
        else {
            std::cout<<"Familia "<<secondFam.get_family_name()<<" a castigat!"<<'\n';
        }
    }

    void Game::askForAI() {
        AI helper;
        AI::switchAIErrors();
    }
    void Game::setUp(std::string& family1, std::string& family2) {
        std::cout << "Salut! Bine ai venit la Family feud/(Ce spun romanii?)! Eu sunt gazda emisiunii, Cabral./"
                "Te rog sa introduci mai jos numele celor doua familii:" << '\n';
        std::cout << "Nume familie 1: " << '\n';
        std::cin >> family1;
        std::cout << "Nume familie 2: " << '\n';
        std::cin >> family2;
    }
    void Game::initPlayers(std::vector<Player>& players_, const std::string& family_name)
    {
        std::cout << "Introdu 5 membri ai familiei: " << '\n';
        for (int i=0;i<5;i++) {
            std::string member_name;
            std::cout<<"Membru "<< i+1<<": "<<'\n';
            std::cin>>member_name;
            Player player(member_name, family_name);
            players_.push_back(player);

        }
    }
    void Game::parseJson(const std::string& filePath, json& data_) {
        std::ifstream file(filePath);
    if (!file.is_open()) {
        throw FileReadException("Nu am putut deschide fisierul.");
        //NOTA: De inchis fereastra atunci cand se intampla asta.
    }
    file >> data_;
    file.close();
    }
void Game::initFiles() {
        parseJson("intrebari.json", data);
    }
void Game::playGame() {

        std::string family1;
        std::string family2;
        setUp(family1, family2);
        initPlayers(players1, family1);
        Family firstFam(family1, 0, players1);
        initPlayers(players2, family2);
        Family secondFam(family2, 0, players2);
        makeRounds(firstFam, secondFam);
        playAgain();
    }
    void Game::playAgain() {
        std::cout<<"Doriti sa jucati din nou? Da/Nu"<<'\n';
        std::string answer;
        std::cin>>answer;
        if(answer == "Da") {
            std::cout<<"Reincepem jocul!"<<'\n';
            std::string gameType;
            std::cout << "Introdu tipul jocului (Normal/Special): ";
            std::cin>> gameType;
            if (gameType == "Normal") {
                NormalGame game;
                game.playGame();
            } else if (gameType == "Special") {
                SpecialGame game;
                game.playGame();
            } else {
                std::cout << "Tip de joc invalid!" << '\n';
            }
        }
        else {
            std::cout<<"Multumim pentru participare!"<<'\n';
        }
    }





bool Game::getRandomBool() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 1);
        return dis(gen) == 1;
    }


std::ostream& operator<<(std::ostream& os, const Game &g) {
    os<<"Game currently initiated and running. Enjoy! -From Cabral himself. Captains: "<<'\n';
    os<<g.players1[0]<<'\n'<<g.players2[0]<<'\n';

    return os;
}