//
// Created by Vali on 17/04/2025.
//

#ifndef FILEREADEXCEPTION_H
#define FILEREADEXCEPTION_H
#include <exception>
#include <string>



class FileReadException : public std::exception {
    std::string message;
public:
    explicit FileReadException(const std::string& file);

    const char* what() const noexcept override;
    virtual ~FileReadException() noexcept = default;
};






#endif //FILEREADEXCEPTION_H
