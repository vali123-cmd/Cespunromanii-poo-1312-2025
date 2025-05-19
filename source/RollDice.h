//
// Created by danciu-valentin-nicolae on 18.05.2025.
//

#ifndef ROLLDICE_H
#define ROLLDICE_H
#include <iostream>
#include <random>

#include "Family.h"


class Family;

template <typename T>
class RollDice {
    T generateRandomNumber() {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        if constexpr (std::is_integral<T>::value) {
            std::uniform_int_distribution<T> dist(1, 10);
            return dist(gen);
        } else if constexpr (std::is_floating_point<T>::value) {
            std::uniform_real_distribution<T> dist(0, 1);
            return dist(gen);
        }
    }
public:
    bool takeGuess(T& guess) {
        T num = generateRandomNumber();
        if (guess == num) {
            return true;
        }

            if constexpr(std::is_floating_point<T>::value) {
                num = num *100;
                guess = guess *100;
                if (abs(num - guess) <= 1) {
                    return true;
                }
            }
            return false;


    }
    void takeAction(const bool& wasGood, Family& fam) {
        if (wasGood) {
            std::cout<<"Raspuns corect."<<'\n';
            fam.set_family_score(fam.get_family_score() + 20);
        } else {
            std::cout << "Ai gresit!\n";
        }
    }
};



#endif //ROLLDICE_H
