//
// Created by Vali on 02/04/2025.
//

#include "AI.h"
#include <iostream>
#include <cpr/cpr.h>
#include <json.hpp>

#include "exceptions/AITimeoutException.h"
#include <fstream>

#include "AIConnectionPool.h"
using json = nlohmann::json;

bool AI::validAnswer(const std::string& answer, const std::string& question, const bool& useAIErrors) {
    cpr::Url api_endpoint = config.getApiEndpoint();
    cpr::Header header{
                        {"Content-Type", "application/json"}
    };
    //  Adăugăm timeout la request, deoarece pot exista situații când durează foarte mult.
    const int miliseconds = config.getParsedTimeout();

    json json_body;
    json_body["model"] = config.getModel();
    std::string prompt = "Poate fi considerat următorul răspuns corect la întrebarea: '" + question + "'? Răspunsul este: '" + answer + "'. Răspunde cu '1' sau '0'.";
    json_body["messages"] = json::array({
        // json::object({{"role", "system"}, {"content", "You are a helpful assistant"}}),
        json::object({{"role", "user"}, {"content", prompt}, {"temperature", 0.0}, {"seed", 42}})
    });
    // std::cout << "sending " << json_body << "\n";
    cpr::Body body = {json_body.dump()};
    cpr::Response res = cpr::Post(api_endpoint, body, header, cpr::Timeout{miliseconds}); // Facem o cerere la API

    if(res.elapsed * 1000 > miliseconds)
    {
        if (useAIErrors) {
            throw AITimeoutException(miliseconds / 1000);
        }

    }
    if(res.status_code != 200) // Dacă status code-ul nu este 200 înseamnă că a apărut o eroare
    {
        std::cout<<"branched200";
        return false;
    }
    if(res.text.empty())
    {
        std::cout<<"branchedempty";
        return false;
    }

    std::string accumulated;
    std::istringstream stream(res.text);
    std::string line;

    while (std::getline(stream, line)) {

        if (line.empty()) continue;

        try {

            json j = json::parse(line);


            if (j.contains("message") && j["message"].contains("content")) {
                accumulated += j["message"]["content"].get<std::string>();
            }

            if (j.contains("done") && j["done"] == true) {
                break;
            }

        } catch (const std::exception& e) {
            std::cerr << "Failed to parse line: " << line << "\n";
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
    return accumulated == "1";
}
float AI::getScore(const std::string& word1, const std::string& word2, const bool& useAIErrors)  {
    std::string prompt =  config.getCustomPrompt();
    size_t pos;
    while ((pos = prompt.find("<word1>")) != std::string::npos) {
        prompt.replace(pos, 7, word1);
    }
    while ((pos = prompt.find("<word2>")) != std::string::npos) {
        prompt.replace(pos, 7, word2);
    }
    std::cout << "Prompt: " << prompt << "\n";

    if (useAIErrors == 0 ) {
        std::cout<<"branchedinitial"; //fordebug
        return -1;
    }

    cpr::Url api_endpoint = config.getApiEndpoint();
    cpr::Header header{
                    {"Content-Type", "application/json"}
    };
    //  Adăugăm timeout la request, deoarece pot exista situații când durează foarte mult.
    const int miliseconds = config.getParsedTimeout();

    json json_body;
    json_body["model"] = config.getModel();

    json_body["messages"] = json::array({
        // json::object({{"role", "system"}, {"content", "You are a helpful assistant"}}),
        json::object({{"role", "user"}, {"content", prompt}, {"temperature", 0.0}, {"seed", 42}})
    });
    // std::cout << "sending " << json_body << "\n";
    cpr::Body body = {json_body.dump()};
    cpr::Response res = cpr::Post(api_endpoint, body, header, cpr::Timeout{miliseconds}); // Facem o cerere la API

    if(res.elapsed * 1000 > miliseconds)
    {
        if (useAIErrors) {
            throw AITimeoutException(miliseconds / 1000);
        }

    }
    if(res.status_code != 200) // Dacă status code-ul nu este 200 înseamnă că a apărut o eroare
    {
        std::cout<<"branched200"; //for debug
        return -1;
    }
    if(res.text.empty())
    {
        std::cout<<"branchedempty"; //for debug
        return -1;
    }

    std::string accumulated;
    std::istringstream stream(res.text);
    std::string line;

    while (std::getline(stream, line)) {

        if (line.empty()) continue;

        try {

            json j = json::parse(line);


            if (j.contains("message") && j["message"].contains("content")) {
                accumulated += j["message"]["content"].get<std::string>();
            }

            if (j.contains("done") && j["done"] == true) {
                break;
            }

        } catch (const std::exception& e) {
            std::cerr << "Failed to parse line: " << line << "\n";
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    try {
        return std::stof(accumulated);
    } catch (const std::exception& e) {
        std::cerr << "Failed to convert response to float: '" << accumulated << "'\n" <<e.what();
        return -1.0f;
    }


}

bool AI::isActive() const {
    return active;
}

void AI::disconnect() {
    active = false;

}

void AI::connect() {
    active = true;
}
