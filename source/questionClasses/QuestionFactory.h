//
// Created by danciu-valentin-nicolae on 16.05.2025.
//

#ifndef QUESTIONFACTORY_H
#define QUESTIONFACTORY_H
#include <iostream>
#include <functional>
#include <memory>
#include "Question.h"
#include "QuestionKiller.h"
#include "QuestionOptional.h"
#include "QuestionRandBonus.h"
#include "QuestionMath.h"
#include "exceptions/OutOfRangeException.h"

#include "roundClasses/SpecialRound.h"

class QuestionFactory : public SpecialRound {
public:
   std::unique_ptr<Question> getQuestion();
};

#endif //QUESTIONFACTORY_H
