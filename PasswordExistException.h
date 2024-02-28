//
// Created by tezca on 23.05.2023.
//

#ifndef PASSWORDMANAGER_PASSWORDEXISTEXCEPTION_H
#define PASSWORDMANAGER_PASSWORDEXISTEXCEPTION_H

#include <exception>
#include <string>

class PasswordExistException : std::exception{
private:
    std::string errorMessage_;
public:
    PasswordExistException() = default;
    PasswordExistException(const std::string &errorMessage) noexcept
            : errorMessage_ {errorMessage}{}
    ~PasswordExistException() = default;
    virtual const char *what() const noexcept{
        return errorMessage_.c_str();
    }
};
#endif //PASSWORDMANAGER_PASSWORDEXISTEXCEPTION_H
