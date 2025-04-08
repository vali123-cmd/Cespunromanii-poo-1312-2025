//
// Created by Vali on 02/04/2025.
//

#include "AI.h"
#include <iostream>
#include <cpr/cpr.h>
#include <json.hpp>

using json = nlohmann::json;
float AI::getScore(const std::string& word1, const std::string& word2) {
    std::string prompt = std::string("return the cosine similarity between the following words: ") + word1 + " " + word2+
        "respond with a real number between 0 and 1, nothing else.";


    cpr::Url api_link = api_url + "/v1/completions";
    cpr::Header header{
                    {"Content-Type", "application/json"}
    };
    // Adăugăm timeout la request, deoarece pot exista situații când durează foarte mult.
    const int miliseconds = 15000;
    using json = nlohmann::json;
    json json_body;
    json_body["model"] = "local model";

    json_body["messages"] = json::array({
        // json::object({{"role", "system"}, {"content", "You are a helpful assistant"}}),
        json::object({{"role", "user"}, {"content", prompt}, {"temperature", 0.0}, {"seed", 42}})
    });
    // std::cout << "sending " << json_body << "\n";
    cpr::Body body = {json_body.dump()};
    cpr::Response res = cpr::Post(api_link, body, header, cpr::Timeout{miliseconds}); // Facem o cerere la API

    if(res.elapsed * 1000 > miliseconds)
    {
        std::cout << "Request timeout" << std::endl;
        return {};
    }
    if(res.status_code != 200) // Dacă status code-ul nu este 200 înseamnă că a apărut o eroare
    {
        std::cout << "Oops!! Got status " << res.status_code << std::endl;
        return {};
    }
    if(res.text.empty())
    {
        std::cout << "Empty response" << std::endl;
        return {};
    }

    json json_resp = json::parse(res.text); // Parsăm răspunsul primit
    // std::cout << res.text << "\n";
    // std::cout << json_resp["choices"] << "\n";
    std::string str_score = json_resp["choices"][0]["message"]["content"];
    float score = std::stof(str_score);
    return score;
}