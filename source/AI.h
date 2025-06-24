//
// Created by Vali on 02/04/2025.
//
#pragma once

#include <string>
#include "json.hpp"
#include "Config.h"
using nlohmann::json;

class AI {


    bool active = false;
    Config& config = Config::getInstance();

public:
    void disconnect();

    float getScore(const std::string& word1, const std::string& word2, const bool& useAIErrors);
    bool isActive() const;
    void connect();

};



