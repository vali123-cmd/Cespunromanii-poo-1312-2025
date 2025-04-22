//
// Created by Vali on 17/04/2025.
//

#ifndef OUTOFRANGEEXCEPTION_H
#define OUTOFRANGEEXCEPTION_H
#include <exception>
#include <string>


class OutOfRangeException : public std::exception {
    std::string message;

public:
    explicit OutOfRangeException(const int& inf, const int& sup);

    const char* what() const noexcept override;

};



#endif //OUTOFRANGEEXCEPTION_H
