//
// Created by tezca on 24.04.2023.
//

#ifndef PASSWORDMANAGER_PASSWORDENTRY_H
#define PASSWORDMANAGER_PASSWORDENTRY_H
#include <string>
#include "PasswordLengthException.h"
#include "PasswordExistException.h"
#include "PasswordDoesntExistException.h"

/**
 * @brief Represents a single entry of a password in the password manager.
 *
 * The PasswordEntry class stores information about a password, including its title, password value, and category.
 * It provides accessors and mutators for each attribute and supports stream insertion to enable printing of password entries.
 */
class PasswordEntry {
    /**
     * @brief Stream insertion operator overload for PasswordEntry.
     *
     * This operator allows printing a PasswordEntry object to an output stream.
     * It provides a formatted representation of the PasswordEntry, including its title, password, and category.
     *
     * @param os The output stream to insert the PasswordEntry into.
     * @param rhs The PasswordEntry object to be inserted into the output stream.
     *
     * @return The modified output stream after inserting the PasswordEntry.
     */
    friend std::ostream &operator<<(std::ostream& os,const PasswordEntry &rhs);
private:
    std::string title;
    std::string password;
    std::string category;
public:
    /**
     * @brief Constructs a new PasswordEntry object with the specified title, and category.
     *
     * @param title The title of the password entry.
     * @param password The password of the password entry.
     * @param category The category of the password entry.
     */
    PasswordEntry(std::string title, std::string password, std::string category);
    /**
     * @brief Constructs a new PasswordEntry object by copying another PasswordEntry object.
     * @param other The PasswordEntry object to be copied.
     */
    PasswordEntry(const PasswordEntry &other);
    std::string get_title() const;
    std::string get_password() const;
    void set_password(const std::string &new_password);
    std::string get_category() const;

};


#endif //PASSWORDMANAGER_PASSWORDENTRY_H
