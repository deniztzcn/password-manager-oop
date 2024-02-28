//
// Created by tezca on 25.04.2023.
//

#include <iostream>
#include "PasswordManager.h"
#include <sstream>
#include <algorithm>
#include <fstream>
#include <fmt/core.h>
#include <fmt/ranges.h>

std::set<std::string> PasswordManager::get_categoryList() const {
    return category_list;
}

void PasswordManager::add_category(const std::string &category) {
    std::string lowerc_category {};
    for(const auto &c : category){
        lowerc_category += std::tolower(c);
    }

    auto it = std::find_if(category_list.begin(), category_list.end(), [&lowerc_category](const std::string &category1) {
        std::string lowerc_category_from_list {};
        for(const auto &c : category1){
            lowerc_category_from_list += std::tolower(c);
        }
        return lowerc_category == lowerc_category_from_list;
    });
    if (it == category_list.end()) {
        category_list.insert(category);
    } else
        throw CategoryExistException{"Category " + category + " already exist.\n"
                                                                         "You are being forwarded to the menu..."};
}

bool PasswordManager::delete_category(const std::string &category) {
    auto it = std::find_if(category_list.begin(), category_list.end(), [&category](const std::string &category1) {
        return category == category1;
    });
    if(it != category_list.end()) {
        category_list.erase(it, category_list.end());
        auto it2 = std::remove_if(password_list.begin(), password_list.end(), [&category](PasswordEntry const &password) {
            return password.get_category() == category;
        });
        password_list.erase(it2, password_list.end());
        return true;
    } else
        return false;
}

std::vector<PasswordEntry> PasswordManager::get_passwordList() const {
    return password_list;
}

void PasswordManager::add_password(PasswordEntry const &password) {
    password_list.push_back(password);
    std::string lowerc_category {};
    for(const auto &c : password.get_category()){
        lowerc_category += std::tolower(c);
    }

    auto it = std::find_if(category_list.begin(), category_list.end(), [&lowerc_category](const std::string &category1) {
        std::string lowerc_category_from_list {};
        for(const auto &c : category1){
            lowerc_category_from_list += std::tolower(c);
        }
        return lowerc_category == lowerc_category_from_list;
    });
    if (it == category_list.end()) {
        category_list.insert(password.get_category());
    }
}

void PasswordManager::delete_password() {
    int counter{0};
    std::cin.ignore();
    std::string input{};
    std::cout << "Please enter the password(s) to delete: " << std::endl;
    std::getline(std::cin, input);
    auto stream = std::stringstream(input);
    std::string pass {};
    while (stream >> pass) {

        auto it = std::remove_if(password_list.begin(), password_list.end(), [&pass](const PasswordEntry &password) {
            return password.get_password() == pass;
        });
        if(it != password_list.end()) {
            password_list.erase(it, password_list.end());
            counter++;

            operations.write_all_passwords(password_list);
        }
    }
    if (counter == 1) {
        std::cout << "The password is deleted.\n"
                     "You are being forwarded to the menu..." << std::endl;
    } else if(counter >= 1){
        std::cout << "The passwords are deleted.\n"
                     "You are being forwarded to the menu..." << std::endl;
    } else
        std::cout << "Password is not found." << std::endl;
}

void PasswordManager::show_categories() const {
    fmt::print("{}\n", category_list) ;
}

void PasswordManager::show_passwords()  {
    for (const auto &password: password_list) {
        std::cout << password << std::endl;
    }

}

bool PasswordManager::select_category(const std::string &category) const {
    std::string lowerc_category {};
    for(const auto &c : category){
        lowerc_category += std::tolower(c);
    }

    auto it = std::find_if(category_list.begin(), category_list.end(), [&lowerc_category](const std::string &category1) {
        std::string lowerc_category_from_list {};
        for(const auto &c : category1){
            lowerc_category_from_list += std::tolower(c);
        }
        return lowerc_category == lowerc_category_from_list;
    });

    if (it != category_list.end()) {
        return true;
    } else {
        return false;
    }
}

bool PasswordManager::password_control(const std::string &password) const {
    if (is_password_used(password))
        throw PasswordExistException("Password already exists.");

    if (password.length() <= 6 || password.length() >= 16)
        throw PasswordLengthException("Password length must be between 6 and 16.");

    if (password_score(password) >= 12) {
        std::cout << "Password strength : Strong" << std::endl;
        std::cout << "The password is unique" << std::endl;
        return true;
    } else if (password_score(password) >= 8) {
        std::cout << "Password strength : Normal" << std::endl;
        std::cout << "The password is unique" << std::endl;
        return true;
    } else {
        std::cout << "Password strength : Weak" << std::endl;
        return false;
    }

}

std::string
PasswordManager::generate_password(const int &number_of_chars, const bool &upper_case, const bool &lower_case,
                                   const bool &special, const bool &number) {
    std::string password{};
    const std::string upper_case_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string lower_case_letters = "abcdefghijklmnopqrstuvwxyz";
    const std::string special_chars = "!@#$%&*_-+~=.,:;?/\\|(){}[]<>";
    const std::string numbers = "0123456789";

    std::string chars{};

    srand(unsigned(time(0)));

    if (upper_case) {
        int random_index = (int) (rand() / (RAND_MAX + 1.) * (upper_case_letters.length() - 1)) + 1;
        password += upper_case_letters[random_index];
        chars += upper_case_letters;
    }
    if (lower_case) {
        int random_index = (int) (rand() / (RAND_MAX + 1.) * (lower_case_letters.length() - 1)) + 1;
        password += lower_case_letters[random_index];
        chars += lower_case_letters;
    }
    if (special) {
        int random_index = (int) (rand() / (RAND_MAX + 1.) * (special_chars.length() - 1)) + 1;
        password += special_chars[random_index];
        chars += special_chars;
    }
    if (number) {
        int random_index = (int) (rand() / (RAND_MAX + 1.) * (numbers.length() - 1)) + 1;
        password += numbers[random_index];
        chars += numbers;
    }

    int temp = password.length();

    for (int i = 0; i < number_of_chars - temp; i++) {
        int random_index = (int) (rand() / (RAND_MAX + 1.) * (chars.length() - 1)) + 1;
        password += chars[random_index];
    }
    std::random_shuffle(password.begin(),password.end());
    while (is_password_used(password))
        std::random_shuffle(password.begin(), password.end());
    return password;

}

bool PasswordManager::is_password_used(const std::string &password) const {
    auto it = std::find_if(password_list.begin(), password_list.end(), [&password](const PasswordEntry &passEntry) {
        return passEntry.get_password() == password;
    });

    if (it != password_list.end()) {
        return true;
    } else return false;
}

int PasswordManager::password_score(const std::string &password) const {
    const std::string special_chars = "!@#$%&*_-+~=.,:;?/\\|(){}[]<>";

    auto special_found = [&password, &special_chars]() {
        for (const auto &c: password) {
            if (special_chars.find(c) != std::string::npos) {
                return true;
            }
        }
        return false;
    };

    const int length{8};
    int score{};
    bool has_number = false;
    bool has_upperc_letter = false;
    bool has_lowerc_letter = false;
    bool has_special_char = special_found();

    for (const auto &c: password) {
        if (std::isdigit(c) && !has_number) {
            has_number = true;
            score += 2;
        } else if (std::isupper(c) && !has_upperc_letter) {
            has_upperc_letter = true;
            score += 2;
        } else if (std::islower(c) && !has_lowerc_letter) {
            has_lowerc_letter = true;
            score += 2;
        } else if (has_special_char) {
            score += 3;
        }
    }

    if (password.length() >= 8)
        score += 2;

    if (has_number && has_lowerc_letter && has_upperc_letter && has_special_char)
        score += 4;

    return score;
}
bool PasswordManager::sort_passwords(const std::string &first_parameter,const std::string &second_parameter) {
    if ((first_parameter == "password" || first_parameter == "category" || first_parameter == "title") &&
        (second_parameter == "password" || second_parameter == "category" || second_parameter == "title")) {
        if (first_parameter == "password") {
            std::ranges::sort(password_list.begin(), password_list.end(),
                              [](const PasswordEntry &pass1, const PasswordEntry &pass2) {
                                  return pass1.get_password() < pass2.get_password();
                              });
            return true;
        }

        if (first_parameter == "category" && second_parameter == "title") {
            std::ranges::sort(password_list.begin(), password_list.end(),
                              [](const PasswordEntry &pass1, const PasswordEntry &pass2) {
                                  if (pass1.get_category() == pass2.get_category()) {
                                      return pass1.get_title() < pass2.get_title();
                                  } else
                                      return pass1.get_category() < pass2.get_category();
                              });
            return true;
        } else if (first_parameter == "title" && second_parameter == "category") {
            std::ranges::sort(password_list.begin(), password_list.end(),
                              [](const PasswordEntry &pass1, const PasswordEntry &pass2) {
                                  if (pass1.get_title() == pass2.get_title()) {
                                      return pass1.get_category() < pass2.get_category();
                                  } else
                                      return pass1.get_title() < pass2.get_title();
                              });
            return true;
        } else if (first_parameter == "category" && second_parameter == "password") {
            std::ranges::sort(password_list.begin(), password_list.end(),
                              [](const PasswordEntry &pass1, const PasswordEntry &pass2) {
                                  if (pass1.get_category() == pass2.get_category()) {
                                      return pass1.get_password() < pass2.get_password();
                                  } else
                                      return pass1.get_category() < pass2.get_category();
                              });
            return true;
        } else if (first_parameter == "title" && second_parameter == "password") {
            std::ranges::sort(password_list.begin(), password_list.end(),
                              [](const PasswordEntry &pass1, const PasswordEntry &pass2) {
                                  if (pass1.get_title() == pass2.get_title()) {
                                      return pass1.get_password() < pass2.get_password();
                                  } else
                                      return pass1.get_title() < pass2.get_title();
                              });
            return true;
        } else return false;

    }
}

PasswordEntry &PasswordManager::select_password(const std::string &password) {
    auto it = std::find_if(password_list.begin(), password_list.end(), [&password](const PasswordEntry &passwordEntry) {
        return passwordEntry.get_password() == password;
    });

    if (it != password_list.end()) {
        return *it;
    } else {
        throw PasswordDoesntExistException{"Given password doesn't exist."};
    }
}

void PasswordManager::edit_password(const std::string &pass, const std::string &new_password) {
    select_password(pass).set_password(new_password);
}

bool PasswordManager::search_password(const std::string &parameter) const {
    bool isFound = false;
    std::for_each(password_list.begin(), password_list.end(), [&parameter, &isFound](const PasswordEntry &password) {
        if (password.get_password().find(parameter) != std::string::npos) {
            isFound = true;
            std::cout << password << std::endl;
        }
    });
    return isFound;

}

void PasswordManager::load_data(const std::string &source_file) {
    auto istream = std::ifstream(source_file);
    std::string part {};
    std::vector<std::string> split {};

    while(std::getline(istream,part,'\n')){
        split.push_back(part);
    }
    for(int i = 0; i < split.size(); i += 3){
        std::string decrypted_title = operations.decrypt(split[i]);
        std::string decrypted_password = operations.decrypt(split[i + 1]);
        std::string decrypted_category = operations.decrypt(split[i + 2]);
        add_password({decrypted_title, decrypted_password, {decrypted_category}});
    }
}
