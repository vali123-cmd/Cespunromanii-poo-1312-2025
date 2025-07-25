//
// Created by Vali on 05/04/2025.
//

#include "Question.h"

#include <algorithm>
#include <iostream>
#include <utility>

#include "AI.h"
#include "AIConnectionPool.h"
class Family;

void Question::printTimestamp() {
    //Functie care afiseaza un timestamp in formatul: 2025-05-05 12:34:56
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm *now_tm = std::localtime(&now_c);
    std::cout << "\n\033[90m[" << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S") << "]\033[0m"<< " ";
}

bool Question::useQuestion(Family &family) {
    std::cout << "\n";
    std::cout << family;
    std::cout << "\n";
    return false;
}

void Question::takeAction(Family &leaderFamily, Family &f1, Family &f2) {
    std::cout << "\n";
    if (leaderFamily == f1)
        std::cout << "Familia " << f1.get_family_name() << " a raspuns corect!\n\n";
    else if (leaderFamily == f2)
        std::cout << "Familia " << f2.get_family_name() << " a raspuns corect!\n\n";
}

    void swap(Question &lhs, Question &rhs) noexcept {
    using std::swap;
    swap(lhs.m_text, rhs.m_text);
    swap(lhs.answers, rhs.answers);
}

Question::Question(Question &&other) noexcept
        : m_text(std::move(other.m_text)),
          answers(std::move(other.answers)) {
}

void Question::formatAnswer(std::string& s) {

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
    double Question::similarity_percentage(const std::string& s1,const std::string& s2) {
        //Functie care calculeaza procentul de similaritate dintre doua stringuri.
        int n = s1.length();
        int m = s2.length();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
        if (s1 == s2) {
            return 100;
        }
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

     Question::Question(std::string  text_, const std::vector<std::pair<std::string, int>>& answers_):
    m_text(std::move(text_)), answers(answers_) {
    }

    [[nodiscard]] const std::string& Question::get_question_text() {
        return m_text;
    }

    [[nodiscard]] const std::vector<std::pair<std::string, int>>& Question::get_answers() const {
        return answers;
    }

    std::unique_ptr<Question> Question::clone() const {
        return std::make_unique<Question>(*this);
    }

    bool Question::isAnswerRight(std::string& userString, int& score, std::string& foundAnswer) {
        //formatare pentru precizie mai buna cu ajutorul formatAnswer().
        formatAnswer(userString);
    for (const auto& item : answers) {


        if (userString == item.first) {

                score = item.second;
                std::cout << "\nRaspuns corect! Ai obtinut " << score << " puncte.\n\n";
                return 1;
            }

        }

        AIConnectionPool pool;
        AI* ai = pool.getConnection();
        ai->connect();

        for (const auto& item : answers) {
            std::cout << "\033[90mRaspuns din partea AI: \033[0m";
            printTimestamp();
            std::cout << "\033[90m" << ai->getScore(userString, item.first, pool.getuseAIErrors()) << "\033[0m\n";
            if (similarity_percentage(userString, item.first) > 70 or ai->getScore(userString, item.first, pool.getuseAIErrors())*100 > 70 ) {
                if ( ai->validAnswer(m_text, item.first, pool.getuseAIErrors())) {
                    //NOTA: 70% este un prag de similaritate,poate varia in urmatoarele release-uri,
                    //in viitor vom folosi un AI pentru a calcula procentul de similaritate.
                    score = item.second;
                    foundAnswer = item.first;
                    answers.erase(std::find_if(answers.begin(), answers.end(),[&](const std::pair<std::string, int>& p) {
                        return p.first == item.first;
                    }));
                    ai->disconnect();

                    std::cout << "\nRaspuns corect! Ai obtinut " << score << " puncte.\n\n";
                    return 1;
                }

            }
        }
        ai->disconnect();
        pool.releaseConnection(ai);

        return 0;
    }

    Question::Question(const Question &other)
        : m_text(other.m_text),
          answers(other.answers) {
    }

    Question & Question::operator=(const Question &other) {
        if (this == &other)
            return *this;
        m_text = other.m_text;
        answers = other.answers;
        return *this;
    }


    std::ostream& operator<<(std::ostream& os,  Question& q) {
        os << "\nIntrebare: \033[31m" << q.get_question_text() << "\033[0m\n";
        return os;
    }