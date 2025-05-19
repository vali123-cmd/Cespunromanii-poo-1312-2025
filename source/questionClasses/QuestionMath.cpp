//
// Created by danciu-valentin-nicolae on 07.05.2025.
//

#include "QuestionMath.h"

#include <iostream>

QuestionMath::QuestionMath(const std::string &text_, const std::vector<std::pair<std::string, int> > &answers_):

Question(text_, answers_) {


}


const std::string& QuestionMath::get_question_text() {
    m_text  = "----------------------------------------------------------------------------------------------------------------"
               "\n"
               "               Question Math\n"
                "-----------------------------------------------------------------------------------------------------\n"
                "               Acesta este un Question Math. Raspunsul tau corect iti va mari scorul cu 1% \n"
                "-----------------------------------------------------------------------------------------------------\n"
                 + m_text;
    return m_text;
}

bool QuestionMath::isAnswerRight(std::string &userString_, int &score_, std::string &foundAnswer) {
    if (foundAnswer == answers[0].first and userString_ == answers[0].first) {
        std::cout<<"Raspuns corect"<<std::endl;
        std::cout<<"Scorul tau"<<score_<<" va fi marit cu 1%."<<std::endl;
        return true;
    }

    std::cout<<"Raspuns gresit"<<std::endl;

    return false;
}

void QuestionMath::takeAction(Family &leaderFamily, Family&, Family&) {
    leaderFamily.set_family_score(101*leaderFamily.get_family_score()/100);

}

QuestionMath* QuestionMath::clone() const{
    return new QuestionMath(*this);
}