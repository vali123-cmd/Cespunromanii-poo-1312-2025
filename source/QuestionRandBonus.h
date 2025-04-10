//
// Created by Vali on 10/04/2025.
//

#ifndef QUESTIONRANDBONUS_H
#define QUESTIONRANDBONUS_H
#include "Question.h"

/* daca raspunzi corect la aceasta intrebare,
pentru fiecare raspuns corect din intrebarile din runda urmatoarele vei avea un bonus generat random
intre 0 si 10%. ACEASTA VA FI O INTREBARE DE LOGICA
*/

class QuestionRandBonus : public Question
{
    bool useQuestion();

public:
    double generateBonus();


};



#endif //QUESTIONRANDBONUS_H
