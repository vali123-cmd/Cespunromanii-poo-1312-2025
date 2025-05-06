//
// Created by Vali on 02/04/2025.
//
#pragma once

#include <string>


class AI {
    std::string api_url = "127.0.0.1:11434/api/chat";
     static bool useAIErrors;
public:
    static void switchAIErrors();
    float getScore(const std::string& word1, const std::string& word2) const;

};



