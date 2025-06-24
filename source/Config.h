//
// Created by danciu-valentin-nicolae on 23.06.2025.
//

#ifndef CONFIG_H
#define CONFIG_H
#include <string>

#include "gameClasses/Game.h"


class Config {

    std::string api_endpoint;
    std::string timeout;
     std::string custom_prompt;
     std::string model;

    Config();
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

public:
    static Config& getInstance();

    void ConfigureJSON();
   int getParsedTimeout() ;
    const std::string& getCustomPrompt() ;
    const std::string& getApiEndpoint();
    const std::string& getModel();

};




#endif //CONFIG_H
