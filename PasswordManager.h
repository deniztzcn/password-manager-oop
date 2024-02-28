//
// Created by tezca on 25.04.2023.
//

#ifndef PASSWORDMANAGER_PASSWORDMANAGER_H
#define PASSWORDMANAGER_PASSWORDMANAGER_H


#include <set>
#include <map>
#include <vector>
#include "PasswordEntry.h"
#include "EncryptionOperations.h"
#include "CategoryExistException.h"

/**
 * \brief Represents operations for passwords
 *
 * The PasswordManager class provides functionality for managing passwords and categories.
 * It supports operations such as adding and deleting passwords, managing categories, generating passwords, and more.
 *
 */

class PasswordManager {
private:
    EncryptionOperations operations;
    std::set<std::string> category_list;
    std::vector<PasswordEntry> password_list;
public:
    /**
     * @brief Constructs a PasswordManager object
     *
     * This constructor initializes a PasswordManager object with the specified source file and encryption key.
     * The source file is used for saving passwords, and the key is used for encryption purposes.
     *
     * @param source_file The file's name where the passwords will be saved.
     * @param key An encryption key based on master password
     */
    PasswordManager(const std::string &source_file, const std::string &key)
    :operations {source_file, key}{}
    /**
     * @brief Gets the list of categories.
     *
     * @return The set of category names.
     */
    std::set<std::string> get_categoryList() const;
    /**
     * @brief Gets the list of passwords.
     *
     * @return The vector of PasswordEntry objects.
     */
    std::vector<PasswordEntry> get_passwordList() const;
    /**
     * @brief Adds category name to the category list.
     *
     * @param category The name of the category to be added.
     */
    void add_category(const std::string &category);
    /**
     * @brief Deletes category from the category list and the passwords associated with that category.
     *
     * If the category exists and is successfully deleted, it returns true; otherwise, it returns false.
     *
     * @param category The name of the category to be deleted.
     *
     * @return True if the category is successfully deleted, false otherwise.
     */
    bool delete_category(const std::string &category);
    /**
     * @brief Adds password to the password list.
     *
     * This function adds the provided password entry to the password list to be saved in the source file.
     *
     * @param password The PasswordEntry object to be added.
     */
    void add_password(PasswordEntry const& password);
    /**
     * @brief Deletes password(s) from the password list.
     *
     * This function allows the user to enter one or more passwords to delete from the password list.
     * After deletion, the updated password list is written to the source file.
     * If no passwords are deleted, the function displays a message indicating that the password(s) were not found.
     */
    void delete_password();
    /**
     * @brief Displays the list of categories.
     *
     * This function prints the list of categories currently stored in the category list.
     */
    void show_categories() const;
    /**
     * @brief Displays the list of passwords.
     * This function prints the passwords currently stored in the password list.
     */
    void show_passwords();
    /**
     * @brief Checks if a category exists in the category list.
     *
     * This function checks if the provided category exists in the category list.
     * The comparison is case-insensitive, meaning it ignores the case of the characters.
     *
     * @param category The category to search for.
     *
     * @return True if the category exists in the category list, false otherwise.
     */
    bool select_category(const std::string &category) const;
    /**
     * @brief Searches for a password entry with a given password.
     *
     * This function searches for a password entry in the password list with a password that matches the provided pass parameter.
     * It returns the PasswordEntry object if a match is found.
     *
     * @param password The password to search for.
     *
     * @return The PasswordEntry object matching the given password.
     *
     * @throws PasswordDoesntExistException if the given password doesn't exist in the password list.
     */
    PasswordEntry &select_password(const std::string &password);
    /**
     * @brief Performs password control and checks its strength.
     *
     * This function performs various checks on the provided password to determine its strength and uniqueness.
     * It throws a PasswordExistException if the password already exists in the password list.
     * It throws a PasswordLengthException if the password length is not between 6 and 16 characters.
     *
     * @param password The password to be checked.
     *
     * @return True if the password is not weak and is unique, false otherwise.
     *
     * @throws PasswordExistException if the password already exists.
     * @throws PasswordLengthException if the password length is invalid.
     */
    bool password_control(const std::string &password) const;
    /**
     * @brief Generates a password with specified characteristics.
     *
     * The generated password can include uppercase letters, lowercase letters, special characters, and numbers,
     * based on the provided boolean flags. The function ensures that the generated password is unique by checking
     * if it is already used.
     *
     * @param number_of_chars The desired number of characters in the password.
     * @param upper_case Specifies whether to include uppercase letters in the password.
     * @param lower_case Specifies whether to include lowercase letters in the password.
     * @param special Specifies whether to include special characters in the password.
     * @param number Specifies whether to include numbers in the password.
     *
     * @return The generated password.
     */
    std::string generate_password(const int &number_of_chars, const bool &upper_case, const bool &lower_case, const bool &special, const bool &number);
    /**
     * @brief Checks if a password is already used.
     *
     * This function checks if the specified password is already present in the password list.
     *
     * @param password The password to check.
     *
     * @return True if the password is already used, false otherwise.
     */
    bool is_password_used(const std::string &password) const;
    /**
     * @brief Calculates the score of a password.
     *
     * This function calculates the score of a password based on its complexity and strength.
     *
     * @param password The password to calculate the score for.
     *
     * @return The score of the password.
     */
    int password_score(const std::string &password) const;
    /**
     * @brief Sorts the password list based on specified parameters.
     *
     * This function sorts the password list based on the provided parameters. The sorting can be performed on three
     * attributes: "password", "category", and "title". The function checks the validity of the parameters and applies the
     * sorting accordingly.
     *
     * @param first_parameter The first parameter for sorting.
     * @param second_parameter The second parameter for sorting.
     *
     * @return True if the sorting was successfully applied, false if the parameters are invalid.
     */
    bool sort_passwords(const std::string &first_parameter, const std::string &second_parameter);
    /**
     * @brief Edits the password of a selected entry.
     *
     * This function edits the password of a selected entry in the password list. It first selects the password entry
     * corresponding to the provided password, and then updates its password with the new password provided.
     *
     * @param pass The password of the entry to be edited.
     * @param new_password The new password to replace the existing password.
     *
     * @throws PasswordDoesntExistException if the provided password doesn't exist.
     */
    void edit_password(const std::string &pass, const std::string &new_password);
    /**
     * @brief Searches for passwords matching a given parameter.
     *
     * This function searches for passwords in the password list that contain the given parameter. It iterates through
     * each password entry and checks if the password contains the specified parameter. If a match is found, the function
     * outputs the password entry. The function returns true if at least one match is found, otherwise it returns false.
     *
     * @param parameter The parameter to search for in the passwords.
     *
     * @return True if at least one match is found, false otherwise
     */
    bool search_password(const std::string &parameter) const;
    /**
     * @brief Loads password datas from a source file.
     *
     * This function reads password data from the specified source file and adds it to the PasswordManager.
     * The source file contains encrypted password entries in a specific format. Each entry consists of
     * three lines: title, password, and category. The function decrypts each entry using the encryption key
     * provided during the construction of the PasswordManager.
     *
     * @param source_file The name of the file to load the password data from.
     */
    void load_data(const std::string &source_file);
};


#endif //PASSWORDMANAGER_PASSWORDMANAGER_H
