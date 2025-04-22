//
// Created by Vali on 17/04/2025.
//

#include "FileReadException.h"
FileReadException::FileReadException(const std::string& file)
        : message("Eroare la citirea fișierului: " + file) {}

const char* FileReadException::what() const noexcept{
    return message.c_str();
}