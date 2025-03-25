
#define NOMINMAX //windows headers definesc min si max(eroare la distanta levenstein)
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
///////////////////////////////////////////
//nlohmann::json pt parsare de fisiere json
#include <json.hpp>                     ///
///////////////////////////////////////////


///////////////////////////////////////////
//// CPR pt a descarca date din api     ///
#include <cpr/cpr.h>                    ///
///////////////////////////////////////////


///////////////////////////////////////////////////////////////////
//// Vom folosi simsimd pentru a calcula similaritatea cosinus ////
#include <simsimd/simsimd.h>                                   ////
///////////////////////////////////////////////////////////////////


#include <random>
#include <cmath>
#include <algorithm>



#define ANSWERS_LIMIT 5

using json = nlohmann::json;

/*const std::string API_URL = "http://127.0.0.1:8080";

std::vector<simsimd_f32_t> getEmbeddings(const std::string& word)
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

class Player {
    int m_score=0;
    std::string m_name;
    std::string m_family;
    int answer_streak = 0;


public:
    void increaseScore( int points_given, int bonus_multiplier) {
        m_score+= points_given*bonus_multiplier;
        //Functie care incrementeaza scorul in functie de punctele raspunsului si bonusul rundei.
    }
    void resetAnswerStreak() {
        answer_streak = 0;
    }
    void increaseAnswerStreak() {
        answer_streak++;
    }


    [[nodiscard]] int get_player_score() const {
        return m_score;
    }

    Player(const Player &other)
        : m_score(other.m_score),
          m_name(other.m_name),
          m_family(other.m_family),
           answer_streak(other.answer_streak) {
    }

    Player & operator=(const Player &other) {
        if (this == &other)
            return *this;
        m_score = other.m_score;
        m_name = other.m_name;
        m_family = other.m_family;
        answer_streak = other.answer_streak;
        return *this;
    }


    Player(const std::string& name, const std::string& family): m_name(name), m_family(family) {
        std::cout<<"Jucatorul "<<m_name<<" din familia "<<m_family<<" a fost initializat cu succes."<<'\n';
    }
    friend std::ostream& operator<<(std::ostream& os, const Player& p);

};
std::ostream& operator<<(std::ostream& os, const Player& p ) {

    std::cout<<"Nume jucator: "<<p.m_name<<" din familia "<< p.m_family<<'\n';
    return os;

}
class Family{
    std::string family_name;
    int family_score = 0;
    int strikes = 0;
    std::vector<Player> players;
    [[nodiscard]] int calculate_total_score()  const {
        int family_score_temp = 0;
        for (const auto& player : players) {
            family_score_temp += player.get_player_score();
        }
        return family_score_temp;
    }

public:
    void resetStrikes() {
        strikes = 0;
    }

    Family(const Family &other)
        : family_name(other.family_name),
          family_score(other.family_score),

          strikes(other.strikes),
          players(other.players) {
    }

    Family & operator=(const Family &other) {
        if (this == &other)
            return *this;
        family_name = other.family_name;
        family_score = other.family_score;
        strikes = other.strikes;
        players = other.players;
        return *this;
    }

    bool checkStrikes() {
        if (strikes == 3) {

            return true;
        }
        return false;
    }
    void increaseStrikes() {
        strikes++;
    }
    [[nodiscard]] const std::string& get_family_name() const {
        return family_name;
    }

    [[nodiscard]]  std::vector<Player>& get_players() {
        return players;
    }

    void set_family_score(int family_score_temp) {
        this->family_score = family_score_temp;
    }
   [[nodiscard]]  int get_family_score()  {
        int computedScore = calculate_total_score();
        return computedScore;
    }
    explicit Family(const std::string &family_name, const int family_score=0, const std::vector<Player> &players = {})
        : family_name(family_name),
          family_score(family_score),
          players(players) {
    }
    friend std::ostream& operator<<(std::ostream& os, const Family& f);
};
std::ostream& operator<<(std::ostream& os, const Family& family) {

    os<<family.get_family_name()<<": "<<family.family_score<<'\n'<<family.players[0]; //NOTA:Adaugare compunere de apeluri <<
    os<<"Strikes: "<<family.strikes<<'\n';
    return os;
}
bool operator==(const Family& f1, const Family& f2) {
    return f1.get_family_name() == f2.get_family_name();
}
class Question {
    std::string m_text;
    std::vector<std::pair<std::string, int>> answers;
    void formatAnswer(std::string& s) {

        if (s.length() == 1) {
            s[0] = std::toupper(s[0]);
        }

        else {
            s[0] = std::toupper(s[0]);
            for (unsigned long long int i = 1; i < s.length(); i++) {
                s[i] = std::tolower(s[i]);
            }

        }
    }
    double similarity_percentage(const std::string& s1,const std::string& s2) {
        //Functie care calculeaza procentul de similaritate dintre doua stringuri.
        int n = s1.length();
        int m = s2.length();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0) {
                    dp[i][j] = j;
                } else if (j == 0) {
                    dp[i][j] = i;
                } else if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + std::min(dp[i - 1][j - 1], std::min(dp[i - 1][j], dp[i][j - 1]));
                }
            }
        }
        return 100 - (dp[n][m] * 100.0 / std::max(n, m));
        //Am implementat distanta levenstein pentru a calcula procentul de similaritate, dar
        //in viitoare release-uri voi folosi un AI pentru a calcula procentul de similaritate.
        //TODO: Comportament neasteptat pentru raspunsuri absolut identice ???! (de verificat)
    }

public:
    explicit Question(const std::string& text_, const std::vector<std::pair<std::string, int>>& answers_):
    m_text(text_), answers(answers_) {

    }

    [[nodiscard]] const std::string& get_question_text() const {
        return m_text;
    }

    [[nodiscard]] const std::vector<std::pair<std::string, int>>& get_answers() const {
        return answers;
    }

    bool isAnswerRight(std::string& userString, int& score, std::string& foundAnswer) {
        //formatare pentru precizie mai buna cu ajutorul formatAnswer().
        formatAnswer(userString);
        for (const auto& item : answers) {
            if (similarity_percentage(userString, item.first) > 70) {
                //NOTA: 70% este un prag de similaritate,poate varia in urmatoarele release-uri,
                //in viitor vom folosi un AI pentru a calcula procentul de similaritate.
                score = item.second;
                foundAnswer = item.first;
                answers.erase(std::find_if(answers.begin(), answers.end(),[&](const std::pair<std::string, int>& p) {
                    return p.first == item.first;
                }));
                return 1;
            }
        }
        return 0;
    }

    Question(const Question &other)
        : m_text(other.m_text),
          answers(other.answers) {
    }

    Question & operator=(const Question &other) {
        if (this == &other)
            return *this;
        m_text = other.m_text;
        answers = other.answers;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Question& q);
};
std::ostream& operator<<(std::ostream& os, const Question& q) {
    os<<q.get_question_text()<<'\n'<<q.m_text;
    return os;
}


class Round {
    std::vector<std::pair<std::string, int>> answers_given;
    int round_id = 1;
    json data;


    static void printCurrentAnswers(const std::vector<std::pair<std::string, int>>& answers) {
        for (const auto& item : answers) {
            std::cout << item.first << " " << item.second << '\n';
        }
    }
    void printAllAnswers(const Question& question) {
        std::cout<<"Doriti sa vedeti toate raspunsurile posibile la intrebarea primita?"<<'\n';
        std::string see_all_answers;
        std::cin>>see_all_answers;
        if(see_all_answers == "da") {
            std::cout<<"BAREMUL DE RASPUNSURI: ";
            for (const auto& item: question.get_answers()) {
                std::cout<<item.first<<" "<<item.second<<'\n';
            }
        }
    }

    static int pickRandIndex(const json &data) {
        if (data["intrebari"].empty()) {
            return -1;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, data["intrebari"].size() - 1);

        return distr(gen);
    }

    Question getQuestion(json &data_) {
        int randindex = pickRandIndex(data_);
        std::vector<std::pair<std::string, int>> answers;
        for (const auto& item : data_["intrebari"][randindex]["raspunsuri"]) {
            answers.emplace_back(item["raspuns"], item["punctaj"]);
        }
        Question q = Question(data_["intrebari"][randindex]["intrebare"], answers);
        data_["intrebari"].erase(randindex);
        //BUG FIX: nu se sterge intrebarea din json dupa ce a fost folosita.
        return q;
    }
    Family& whoPressedFirst(Family& f1, Family& f2) {
        //FIXED BUG: Daca cineva introduce un string in loc de un numar, programul intra in bucla infinita.
        int pick;
        while (true) {
            std::cout << "Cine a apasat primul? Scrie 1 pentru familia " << f1.get_family_name() << " si 2 pentru familia " << f2.get_family_name() << '\n';
            std::cin >> pick;

            if (std::cin.fail() || (pick != 1 && pick != 2)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                std::cout << "Ai introdus un numar gresit! Introdu 1 sau 2!" << '\n';
            } else {
                break;
            }
        }
    if (pick==1) {
        return f1;
    }
        return f2;


    }

    void SwitchFamily(Family*& currentFamily, Family& f1, Family& f2) {
        if (currentFamily == &f1) {
            currentFamily = &f2;
        } else {
            currentFamily = &f1;
        }
    }


public:
    [[nodiscard]] int get_round_id() const {
        return round_id;
    }

    Round(int round_id_,  json &data_, Family& f1, Family& f2) : data(data_) {
        bool family_switched = false;
        round_id = round_id_;

        std::cout << "Runda " << round_id << " a inceput" << '\n';

        Question currentQuestion = getQuestion(data_);
        std::cout << currentQuestion;
        Family* leaderFamily = &whoPressedFirst(f1, f2);
        std::string answer;
        std::string givenAns;
        std::cout << *leaderFamily;
        bool terminateRound = false;
        while (answers_given.size() <= ANSWERS_LIMIT && (!family_switched || leaderFamily->checkStrikes() == 0)) {
            for (auto& jucator : leaderFamily->get_players()) {
                std::cout << jucator << " te rugam sa introduci un raspuns popular: " << "\n";
                std::cin.clear();
                std::cin.ignore();
                std::getline(std::cin, answer);
                int givenScore = 0;
                int bonus_multiplier = 1;

                if (get_round_id() == 6) {
                    bonus_multiplier = 2;
                }
                if (currentQuestion.isAnswerRight(answer, givenScore, givenAns)) {
                    std::cout << "Raspuns corect! Felicitari!" << '\n';
                    answers_given.emplace_back(givenAns, givenScore);
                    printCurrentAnswers(answers_given);
                    jucator.increaseScore(givenScore, bonus_multiplier);
                    jucator.increaseAnswerStreak();
                    if (answers_given.size() == ANSWERS_LIMIT) {
                        std::cout << "Ai raspuns la toate intrebarile! S-a terminat runda!" << '\n';
                        leaderFamily->set_family_score(leaderFamily->get_family_score());
                        terminateRound = true;
                        break;
                    }
                } else {
                    jucator.resetAnswerStreak();
                    std::cout << "Raspuns gresit! Mai incearca!" << '\n';
                    leaderFamily->increaseStrikes();
                    leaderFamily->set_family_score(leaderFamily->get_family_score());

                    std::cout << *leaderFamily;
                    if (leaderFamily->checkStrikes() == 1 && !family_switched) {
                        std::cout << "Ai primit 3 strikes! Se schimba familia!" << '\n';
                        leaderFamily->set_family_score(leaderFamily->get_family_score());
                        leaderFamily->resetStrikes();
                        SwitchFamily(leaderFamily, f1, f2);
                        family_switched = true;
                        break;
                    }
                    if (leaderFamily->checkStrikes() == 1 && family_switched) {
                        std::cout << "Noua familie a primit si ea 3 strikes! S-a terminat runda." << '\n';
                        leaderFamily->resetStrikes();
                        leaderFamily->set_family_score(leaderFamily->get_family_score());
                        terminateRound = true;
                        break;
                    }
                }
            }
            if (terminateRound) {
                break;
            }
        }
        leaderFamily->resetStrikes();
        leaderFamily->set_family_score(leaderFamily->get_family_score());

        std::cout << f1 << f2 << '\n';
        printAllAnswers(currentQuestion);
    }

    ~Round() = default;

    Round(const Round &other)
        : answers_given(other.answers_given),
          round_id(other.round_id),
          data(other.data) {
    }

    Round & operator=(const Round &other) {
        if (this == &other)
            return *this;
        answers_given = other.answers_given;
        round_id = other.round_id;
        data = other.data;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Round& q);

    /* Scopul constructorului de copiere, ti-au placut intrebarile dintr-o runda si vrei sa
     * o poti da si altor oameni/prieteni sa o joace sau optiune de 'Genereaza runda custom
     * pe baza acestei runde!' */
};
std::ostream& operator<<(std::ostream& os, const Round& q) {
    os<<q.get_round_id()<<'\n'<<q.answers_given[0].first;
    return os;
}


class Game {

    std::vector<Player> players1;
    std::vector<Player> players2;
    json data;
   /* bool buttonPressed() {
        O functie care ar trebui sa detecteze daca un buton a fost apasat,
          un pic de bataie de cap aici, deoarece trebuie sa facem asta diferit
          pe Windows/Linux/Mac (cred?!)

        return 1;
    }*/
    void getPlayers(std::vector<Player>& players_, const std::string& family_name)
    {
        for (int i=0;i<5;i++) {
            std::string member_name;
            std::cout<<"Membru "<< i+1<<": "<<'\n';
            std::cin>>member_name;
            Player player(member_name, family_name);
            players_.push_back(player);

        }
    }
    void parseJson() {
        std::ifstream file("intrebari.json");
    if (!file.is_open()) {
        std::cerr<<"Nu am putut deschide fisierul json!"<<'\n';
        //NOTA: De inchis fereastra atunci cand se intampla asta.
    }
    file >> this->data;
    file.close();
    }
    void playAgain() {
        std::cout<<"Doriti sa jucati din nou? Da/Nu"<<'\n';
        std::string answer;
        std::cin>>answer;
        if(answer == "Da") {
            Game newGame;
        }
        else {
            std::cout<<"Multumim pentru participare!"<<'\n';
        }
    }

    public:
    Game() {
        parseJson();
        std::string family1;
        std::string family2;
        std::cout << "Salut! Bine ai venit la Family feud/(Ce spun romanii?)! Eu sunt gazda emisiunii, Cabral./"
                "Te rog sa introduci mai jos numele celor doua familii:" << '\n';
        std::cout << "Nume familie 1: " << '\n';
        std::cin >> family1;
        std::cout << "Introdu 5 membri ai primei familii: " << '\n';
        getPlayers(players1, family1);
        Family firstFam(family1, 0, players1);
        std::cout << "Nume familie 2: " << '\n';
        std::cin >> family2;
        getPlayers(players2, family2);
        Family secondFam(family2, 0, players2);

        for (int i=1;i<=6;i++) {

            Round round(i, data,firstFam,secondFam);
        }
        if(firstFam.get_family_score()>secondFam.get_family_score()) {
            std::cout<<"Familia "<<firstFam.get_family_name()<<" a castigat!"<<'\n';
        }
        else {
            std::cout<<"Familia "<<secondFam.get_family_name()<<" a castigat!"<<'\n';
        }
        playAgain();
    }
    ~Game() {
        std::cout<<"Game over! Multumim pentru participare!"<<'\n';
    }
    friend std::ostream& operator<<(std::ostream& os, const Game &g);
};

std::ostream& operator<<(std::ostream& os, const Game &g) {
    std::cout<<"Game currently initiated and running. Enjoy! -From Cabral himself. Captains: "<<'\n';
    std::cout<<g.players1[0]<<'\n'<<g.players2[0]<<'\n';

    return os;
}

int main() {
    std::ifstream file("intrebari.json");

    if (!file.is_open()) {
        return 0;
    }
    Game main;
    return 0;


}