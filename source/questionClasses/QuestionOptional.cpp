//
// Created by Vali on 10/04/2025.
//

#include "QuestionOptional.h"

#include <iostream>
#include <ostream>

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
bool QuestionOptional::useQuestion(Family &f) {
    std::cout<<"Doresti sa folosesti intrebarea optionala? (da/nu)"<<std::endl;
    std::string answer;
    std::cin>>answer;
    if(answer == "da")
    {
        return true;
    }
    if(answer == "nu")
    {
        return false;
    }

    std::cout<<"Raspuns invalid. Te rugam sa introduci 'da' sau 'nu'."<<std::endl;
    return useQuestion(f);
}
bool QuestionOptional::isAnswerRight(std::string &userString, int &score, std::string &foundAnswer) {
    std::cout<<"Raspuns corect! Felicitari!"<<'\n';
    foundAnswer = userString;
    score = 10;
    std::cout<<"Scorul tau a crescut cu 10%!"<<'\n';
    return true;

}
void QuestionOptional::takeAction(Family &leaderFamily, Family&, Family&) {
    leaderFamily.set_family_score(110*leaderFamily.get_family_score()/100);

}
