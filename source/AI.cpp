//
// Created by Vali on 02/04/2025.
//

#include "AI.h"
#include <iostream>
#include <cpr/cpr.h>
#include <json.hpp>

#include "AITimeoutException.h"

using json = nlohmann::json;
void AI::switchAIErrors() {
    std::cout<<"Doresti sa activezi erorile AI? Daca ai o conexiune de internet slaba sau"
               "nu ai configurat Ollama bine jocul va da crash(vezi tutorial in README) (1 - da, 0 - nu): ";
    std::cin>>useAIErrors;
}

float AI::getScore(const std::string& word1, const std::string& word2) const {
    std::string prompt = std::string("cat de similare sunt urmatoarele cuvinte ca sens, cuvintele sunt in limba romana:  ") + word1 + " " + word2+
        "raspunde cu un numar real intre 0 si 1, vreau doar numarul, fara nimic altceva in raspunsul tau.";


    cpr::Url api_link = api_url;
    cpr::Header header{
                    {"Content-Type", "application/json"}
    };
    // Adăugăm timeout la request, deoarece pot exista situații când durează foarte mult.
    const int miliseconds = 15000;
    using json = nlohmann::json;
    json json_body;
    json_body["model"] = "llama3";

    json_body["messages"] = json::array({
        // json::object({{"role", "system"}, {"content", "You are a helpful assistant"}}),
        json::object({{"role", "user"}, {"content", prompt}, {"temperature", 0.0}, {"seed", 42}})
    });
    // std::cout << "sending " << json_body << "\n";
    cpr::Body body = {json_body.dump()};
    cpr::Response res = cpr::Post(api_link, body, header, cpr::Timeout{miliseconds}); // Facem o cerere la API

    if(res.elapsed * 1000 > miliseconds)
    {
        if (useAIErrors) {
            throw AITimeoutException(miliseconds / 1000);
        }
        return -1;
    }
    if(res.status_code != 200) // Dacă status code-ul nu este 200 înseamnă că a apărut o eroare
    {
        std::cout << "Oops!! Got status " << res.status_code << std::endl;
        return -1;
    }
    if(res.text.empty())
    {
        std::cout << "Empty response" << std::endl;
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
    } catch (...) {
        std::cerr << "Failed to convert response to float: '" << accumulated << "'\n";
        return -1.0f;
    }
    //json json_resp = json::parse(res.text); // Parsăm răspunsul primit
    // std::cout << res.text << "\n";
    // std::cout << json_resp["choices"] << "\n";
    //std::string str_score = json_resp["choices"][0]["message"]["content"];
    //float score = std::stof(str_score);
    //return score;
}
