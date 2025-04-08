#include <fstream>




/*std::vector<simsimd_f32_t> getEmbeddings(const std::string& word)
{
    std::string api_url = API_URL;
    if(const auto* url = std::getenv("LLM_URL")) {
        api_url = url;
    }
    cpr::Url api_link = api_url + "/embedding"; // Link-ul către API

    // Configurăm parametrii să fie URL-encoded
    cpr::Parameters params = {
        {"content", word}
    };

    // Setăm header-ul
    cpr::Header header = {
        {"Content-Type", "application/json"}
    };


    // Adăugăm timeout la request, deoarece pot exista situații când durează foarte mult.
    const int miliseconds = 2000;

    cpr::Response res = cpr::Get(api_link, params, header, cpr::Timeout{miliseconds}); // Facem o cerere la API

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
    std::vector<simsimd_f32_t> embedding = json_resp["embedding"];
    // std::cout << json_resp["embedding"].size() << std::endl;
    return embedding;
}
*/










#include "Game.h"

int main() {
    std::ifstream file("intrebari.json");

    if (!file.is_open()) {
        return 0;
    }

    Game main;



    return 0;


}