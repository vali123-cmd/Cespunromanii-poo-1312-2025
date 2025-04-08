//
// Created by Vali on 05/04/2025.
//

#include "Game.h"

#include <iostream>
#include <vector>
#include <fstream>

#include "Family.h"
#include "Player.h"
#include "Round.h"
/* bool buttonPressed() {
        O functie care ar trebui sa detecteze daca un buton a fost apasat,
          un pic de bataie de cap aici, deoarece trebuie sa facem asta diferit
          pe Windows/Linux/Mac (cred?!)

        return 1;
    }*/
    void Game::getPlayers(std::vector<Player>& players_, const std::string& family_name)
    {
        for (int i=0;i<5;i++) {
            std::string member_name;
            std::cout<<"Membru "<< i+1<<": "<<'\n';
            std::cin>>member_name;
            Player player(member_name, family_name);
            players_.push_back(player);

        }
    }
    void Game::parseJson() {
        std::ifstream file("intrebari.json");
    if (!file.is_open()) {
        std::cerr<<"Nu am putut deschide fisierul json!"<<'\n';
        //NOTA: De inchis fereastra atunci cand se intampla asta.
    }
    file >> this->data;
    file.close();
    }
    void Game::playAgain() {
        std::cout<<"Doriti sa jucati din nou? Da/Nu"<<'\n';
        std::string answer;
        std::cin>>answer;
        if(answer == "Da") {
            Game newGame;
        }
        else {
            std::cout<<"Multumim pentru participare!"<<'\n';
        }
    }


    Game::Game() {
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

            Round round(i, data,firstFam,secondFam);
        }
        if(firstFam.get_family_score()>secondFam.get_family_score()) {
            std::cout<<"Familia "<<firstFam.get_family_name()<<" a castigat!"<<'\n';
        }
        else {
            std::cout<<"Familia "<<secondFam.get_family_name()<<" a castigat!"<<'\n';
        }
        playAgain();
    }
    Game::~Game() {
        std::cout<<"Game over! Multumim pentru participare!"<<'\n';
    }



std::ostream& operator<<(std::ostream& os, const Game &g) {
    std::cout<<"Game currently initiated and running. Enjoy! -From Cabral himself. Captains: "<<'\n';
    std::cout<<g.players1[0]<<'\n'<<g.players2[0]<<'\n';

    return os;
}