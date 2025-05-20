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
std::unique_ptr<Question> QuestionOptional::clone() const {
    return std::make_unique<QuestionOptional>(*this);
}

QuestionOptional::QuestionOptional(const std::string &text_, const std::vector<std::pair<std::string, int> > &answers_):

Question(text_, answers_) {


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
bool QuestionOptional::isAnswerRight(std::string &userString_, int &score_, std::string &foundAnswer) {
    if (foundAnswer == answers[0].first and userString_ == answers[0].first) {
        std::cout<<"Raspuns corect"<<std::endl;
        std::cout<<"Scorul tau"<<score_<<" va fi marit cu 5%."<<std::endl;
        return true;
    }

    std::cout<<"Raspuns gresit"<<std::endl;

    return false;

}
void QuestionOptional::takeAction(Family &leaderFamily, Family&, Family&) {
    leaderFamily.set_family_score(105*leaderFamily.get_family_score()/100);

}

