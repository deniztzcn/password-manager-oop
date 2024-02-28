//
// Created by tezca on 14.05.2023.
//

#ifndef PASSWORDMANAGER_PASSWORDLENGTHEXCEPTION_H
#define PASSWORDMANAGER_PASSWORDLENGTHEXCEPTION_H

#include <exception>

class PasswordLengthException : std::exception{
private:
    std::string errorMessage_;
public:
    PasswordLengthException() = default;
    PasswordLengthException(const std::string &errorMessage) noexcept
    : errorMessage_ {errorMessage}{}
    ~PasswordLengthException() = default;
    virtual const char *what() const noexcept{
        return errorMessage_.c_str();
    }
};
#endif //PASSWORDMANAGER_PASSWORDLENGTHEXCEPTION_H
