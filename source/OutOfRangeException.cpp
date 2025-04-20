//
// Created by Vali on 17/04/2025.
//

#include "OutOfRangeException.h"



OutOfRangeException::OutOfRangeException(const int& inf, const int& sup): message("Numarul introdus este in afara intervalului [" + std::to_string(inf) + ", " + std::to_string(sup) + "]") {

}

const char* OutOfRangeException::what() const noexcept {
    return message.c_str();
}