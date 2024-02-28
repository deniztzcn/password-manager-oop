//
// Created by tezca on 23.05.2023.
//

#ifndef PASSWORDMANAGER_CATEGORYEXISTEXCEPTION_H
#define PASSWORDMANAGER_CATEGORYEXISTEXCEPTION_H

#include <exception>
#include <string>

class CategoryExistException : std::exception{
private:
    std::string errorMessage_;
public:
    CategoryExistException() = default;
    CategoryExistException(const std::string &errorMessage) noexcept
            : errorMessage_ {errorMessage}{}
    ~CategoryExistException() = default;
    virtual const char *what() const noexcept{
        return errorMessage_.c_str();
    }
};
#endif //PASSWORDMANAGER_CATEGORYEXISTEXCEPTION_H
