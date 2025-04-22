//
// Created by Vali on 11/04/2025.
//

#include "NormalGame.h"

#include <iostream>

#include "Family.h"
#include "roundClasses/Round.h"

void NormalGame::makeRounds(Family& f1, Family& f2)  {
    for (int i=1;i<=6;i++) {
        round = new Round(i, data, f1, f2);
        round->playRound(f1,f2);
    }
}


