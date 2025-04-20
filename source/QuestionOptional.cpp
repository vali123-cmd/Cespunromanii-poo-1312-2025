//
// Created by Vali on 10/04/2025.
//

#include "QuestionOptional.h"

const std::string& QuestionOptional::get_question_text() {
    m_text  = "----------------------------------------------------------------------------------------------------------------"
               "\n"
               "               Question Optional\n"
               "-----------------------------------------------------------------------------------------------------\n"
               "               Acesta este un QuestionOptional. Raspunsul tau corect iti va mari scorul cu 10% \n"
                "              Ai dreptul la o astfel de intrebare cand o familie castiga fara sa ia vreun streak in vreo runda.\n"
               "-----------------------------------------------------------------------------------------------------\n"
                + m_text;
    return m_text;
}

QuestionOptional::QuestionOptional(const std::string &text_, const std::vector<std::pair<std::string, int> > &answers_):

Question(text_, answers_) {
    // Constructorul clasei de baza este apelat automat
    // Nu este nevoie sa facem nimic aici

}

bool QuestionOptional::isAnswerRight(std::string &userString, int &score, std::string &foundAnswer) {
    return true;
}
bool QuestionOptional::useQuestion(Family &f) {
    return true;
}
