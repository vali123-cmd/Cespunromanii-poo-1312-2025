//
// Created by Vali on 05/04/2025.
//

#include "Question.h"

#include <algorithm>
#include <iostream>

#include "AI.h"
class Family;


bool Question::useQuestion(Family &family) {
    return false;
}
void Question::takeAction(Family &leaderFamily, Family &f1, Family &f2) {

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

     Question::Question(const std::string& text_, const std::vector<std::pair<std::string, int>>& answers_):
    m_text(text_), answers(answers_) {
    }

    [[nodiscard]] const std::string& Question::get_question_text() {
        return m_text;
    }

    [[nodiscard]] const std::vector<std::pair<std::string, int>>& Question::get_answers() const {
        return answers;
    }

    bool Question::isAnswerRight(std::string& userString, int& score, std::string& foundAnswer) {
        //formatare pentru precizie mai buna cu ajutorul formatAnswer().
        formatAnswer(userString);

        AI helper; //daca nu s-a creat serverul AI va intoarce automat -1.

        for (const auto& item : answers) {


            if (similarity_percentage(userString, item.first) > 70 or helper.getScore(userString, item.first) > 70) {
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
        os<<q.get_question_text()<<'\n';
        return os;
    }