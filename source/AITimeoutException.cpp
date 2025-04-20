//
// Created by Vali on 17/04/2025.
//

#include "AITimeoutException.h"


AITimeoutException::AITimeoutException(int timeoutInSeconds)
    : message("AI timeout: operația a depășit limita de " + std::to_string(timeoutInSeconds) + " secunde, fa ceva cu"
                                                                                               "netul tau sau porneste"
                                                                                               "ollama.") {}

const char* AITimeoutException::what() const noexcept {
    return message.c_str();
}