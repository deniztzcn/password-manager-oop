//
// Created by tezca on 2.06.2023.
//

#ifndef PASSWORDMANAGER_PASSWORDDOESNTEXISTEXCEPTION_H
#define PASSWORDMANAGER_PASSWORDDOESNTEXISTEXCEPTION_H

#include <string>

class PasswordDoesntExistException : std::exception{
private:
    std::string errorMessage_;
public:
    PasswordDoesntExistException() = default;
    PasswordDoesntExistException(const std::string &errorMessage) noexcept
            : errorMessage_ {errorMessage}{}
    ~PasswordDoesntExistException() = default;
    virtual const char *what() const noexcept{
        return errorMessage_.c_str();
    }
};
#endif //PASSWORDMANAGER_PASSWORDDOESNTEXISTEXCEPTION_H
