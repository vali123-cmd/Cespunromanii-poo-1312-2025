//
// Created by Vali on 11/04/2025.
//

#include "SpecialGame.h"

#include <iostream>

#include "Family.h"
#include "exceptions/FileReadException.h"
#include "roundClasses/Round.h"
#include "roundClasses/SpecialRound.h"

void SpecialGame::initFiles() {
    try {
        parseJson("intrebari.json", data);
        parseJson("intrebariQK.json", dataQK);
        parseJson("intrebariQO.json", dataQO);
        parseJson("intrebariQRB.json", dataQRB);
    } catch (const FileReadException& e) {
        std::cerr << e.what() << '\n';
    }
}

void SpecialGame::makeRounds(Family &f1, Family &f2)  {
    for (int i = 1;i<=6;i++) {
        round = new SpecialRound(i, data, dataQK, dataQO, dataQRB,f1, f2);
        round->playRound(f1,f2);
    }

}