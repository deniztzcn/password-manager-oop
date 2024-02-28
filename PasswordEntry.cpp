//
// Created by tezca on 24.04.2023.
//

#include <cstring>
#include <ostream>
#include "PasswordEntry.h"
PasswordEntry::PasswordEntry(std::string title, std::string password, std::string category)
: title{title}, password{password}, category{category}{
}

std::string PasswordEntry::get_title() const {
    return title;
}

std::string PasswordEntry::get_password() const {
    return password;
}

std::string PasswordEntry::get_category() const {
    return category;
}

PasswordEntry::PasswordEntry(const PasswordEntry &other)
: title{other.title}, password{other.password}, category{other.category}{}

std::ostream &operator<<(std::ostream &os, const PasswordEntry &rhs) {
    os << rhs.get_category() << std::endl <<
       rhs.get_title() << std::endl <<
    rhs.get_password() << std::endl;
    return os;
}

void PasswordEntry::set_password(const std::string &new_password) {
    password = new_password;
}
