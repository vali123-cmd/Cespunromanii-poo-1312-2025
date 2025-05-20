//
// Created by danciu-valentin-nicolae on 06.05.2025.
//

#include "ScoreManager.h"
#include <fstream>
#include <iostream>
#include <json.hpp>

ScoreManager::ScoreManager( const std::string& file) : filename(file) {

}

void ScoreManager::saveScores(const std::unordered_map<std::string, int>& scores) {
    nlohmann::json j;
    for (const auto& [name, score] : scores) {
        j[name] = score;
    }

    std::ofstream out(filename);
    if (out) {
        out << j.dump(4);  // Pretty print
        std::cout << "Scores saved to " << filename << "\n";
    } else {
        std::cout << "Failed to open " << filename << " for writing.\n";
    }
}

std::unordered_map<std::string, int> ScoreManager::loadScores() {
    std::unordered_map<std::string, int> scores;
    std::ifstream in(filename);
    if (!in) {
        std::cout << "File " << filename << " not found.\n";
        return scores;
    }

    nlohmann::json j;
    in >> j;

    for (auto it = j.begin(); it != j.end(); ++it) {
        scores[it.key()] = it.value();
    }

    return scores;
}

void ScoreManager::printScores() {
    auto scores = loadScores();
    std::cout << "Player Scores:\n";
    for (const auto& [name, score] : scores) {
        std::cout << " - " << name << ": " << score << "\n";
    }
}

void ScoreManager::clearScores() {
    try {
        std::ofstream out(filename, std::ios::trunc);
        if (out) {
            out << "{}";  // Clear the file
            std::cout << "Scores cleared.\n";
        } else {
            std::cerr << "Failed to open " << filename << " for writing.\n";
        }
    }
    catch (const::std::exception& e) {
        std::cout<<"Error clearing scores: " << e.what() << "\n";
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////////
//ScoreManager este o clasa care gestioneaza scorurile jucatorilor.
// Aceasta clasa are metode pentru a salva, incarca, afisa si sterge scorurile.
// Scorurile sunt salvate intr-un fisier JSON, iar fiecare jucator are un nume si un scor.
// Metoda saveScores salveaza scorurile intr-un fisier JSON.
// Metoda loadScores incarca scorurile din fisierul JSON.
// Metoda printScores afiseaza scorurile jucatorilor.
// Metoda clearScores sterge scorurile din fisierul JSON.
////////////////////////////////////////////////////////////////////////////////////////////////