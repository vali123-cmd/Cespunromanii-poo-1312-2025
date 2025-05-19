//
// Created by Vali on 17/04/2025.
//

#ifndef AI_TIMEOUT_EXCEPTION_H
#define AI_TIMEOUT_EXCEPTION_H

#include <exception>
#include <string>

class AITimeoutException : public std::exception {
    std::string message;

public:
    explicit AITimeoutException(int timeoutInSeconds);
    const char* what() const noexcept override;
    virtual ~AITimeoutException() noexcept = default;
};

#endif // AI_TIMEOUT_EXCEPTION_H
