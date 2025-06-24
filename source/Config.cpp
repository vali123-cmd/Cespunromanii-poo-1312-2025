//
// Created by danciu-valentin-nicolae on 23.06.2025.
//

#include "Config.h"

#include <iostream>
#include <sstream>

#include "json.hpp"
#include <fstream>
using json = nlohmann::json;

Config::Config() {
    // Inițializăm valorile implicite
    ConfigureJSON();
}

void Config::ConfigureJSON() {
     json jsonConfig;
    std::string filetext;
    std::ifstream configFile("configure.json");
    if (!configFile.is_open()) {
        std::cerr << "Error: Could not open configure.json file. Using default:\n";
        return;
    }
    try{
            std::ostringstream buffer; // use ostringstream to avoid implicit conversion
            buffer << configFile.rdbuf();
            filetext = buffer.str();
            jsonConfig = json::parse(filetext);

    } catch (const json::parse_error& e) {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
        return;
    }

    // Configurăm URL-ul ENDPOINTULUI,TIMEOUTULUI si PROMPTULUI din fisierul JSON
    api_endpoint = "127.0.0.1:11434/api/chat";
    timeout = "5000";
    model = "llama3";
    custom_prompt = "Compare the level of similarity between the following two romanian words based on their meanings and usage. Provide a float value between 0 and 1, where 0 means no similarity and 1 means identical meaning. The words are: ";
    if (jsonConfig.contains("api-endpoint")) {
        api_endpoint = jsonConfig["api-endpoint"].get<std::string>();
    } else {
        std::cerr << "Warning: 'api-endpoint' not found in JSON configuration. Using default: " << api_endpoint << "\n";
    }
    if (jsonConfig.contains("timeout")) {
        timeout = jsonConfig["timeout"];
    } else {
        std::cerr << "Warning: 'timeout' not found in JSON configuration. Using default: " << timeout<< "\n";
    }
    if (jsonConfig.contains("custom-prompt")) {
        custom_prompt = jsonConfig["custom-prompt"].get<std::string>();
    } else {
        std::cerr << "Warning: 'custom-prompt' not found in JSON configuration. Using default: " << custom_prompt << "\n";
    }
    if (jsonConfig.contains("model")) {
        model = jsonConfig["model"];
    } else {
        std::cerr << "Warning: 'model' not found in JSON configuration. Using default: " << model << "\n";
    }
}
const std::string& Config::getApiEndpoint() {
    return api_endpoint;
}

Config& Config::getInstance() {
    static Config instance;
    instance.ConfigureJSON();
    return instance;
}

int Config::getParsedTimeout() {
    try {
        return std::stoi(timeout);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing timeout: " << e.what() << "\n";
        return 5000; // Default timeout
    }
}

const std::string& Config::getCustomPrompt() {
    return custom_prompt;
}
const std::string& Config::getModel() {
    return model;
}
