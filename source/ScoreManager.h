#pragma once

#include <string>
#include <unordered_map>

class ScoreManager {
private:
    std::string filename;

public:
    explicit ScoreManager(const std::string& file);

    void saveScores(const std::unordered_map<std::string, int>& scores);
    std::unordered_map<std::string, int> loadScores();
    void printScores();
    void clearScores();

};
