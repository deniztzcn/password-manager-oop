#include <iostream>
#include <vector>
#include "PasswordEntry.h"
#include <ranges>
#include <map>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "PasswordManager.h"
#include <thread>
#include <chrono>
#include "EncryptionOperations.h"
#include <fmt/core.h>
#include <fmt/ranges.h>


void menu() {
    std::cout << "1-Add category\t\t"
                 "2-Add password\n"
                 "3-Sort passwords\t"
                 "4-Edit password\n"
                 "5-Delete password(s)\t"
                 "6-Search passwords\n"
                 "7-Delete category\t"
                 "8-Show passwords\n"
                 "9-Exit\n";
}

int main() {
    std::string master_password{};
    std::string operation{};
    std::string source_file{};
    std::cout << "Please provide a file path or give a file title from program's folder:" << std::endl;
    std::cin >> source_file;

    std::cout << "Please enter master password:" << std::endl;
    std::cin >> master_password;
    PasswordManager manager{source_file, master_password};
    EncryptionOperations operations{source_file, master_password};
    manager.load_data(source_file);

    while (true) {
        menu();
        std::cout << "Please choose an operation: " << std::endl;
        std::cin >> operation;

        try {
            switch (std::stoi(operation)) {
                case 1: {
                    std::string category{};
                    std::cout << "Please enter a category name: " << std::endl;
                    std::cin.ignore();
                    std::getline(std::cin, category);

                    manager.add_category(category);
                }
                    break;
                case 2: {
                    std::string title{};
                    std::string category{};
                    std::string password{};
                    if (manager.get_categoryList().empty()) {
                        std::cerr << "Category list is empty.\n"
                                     "Please add category before adding password.\n"
                                     "You are being Forwarded to the menu..." << std::endl;
                        using namespace std::chrono_literals;
                        std::this_thread::sleep_for(1s);
                        continue;
                    }

                    std::cout << "Please enter a title for the password:" << std::endl;
                    std::cin.ignore();
                    std::getline(std::cin, title);

                    while (true) {
                        manager.show_categories();
                        std::cout << "Please enter category name:" << std::endl;
                        std::getline(std::cin, category);
                        if (!manager.select_category(category)) {
                            std::cerr << "Category doesn't exist please choose category from given list." << std::endl;
                            using namespace std::chrono_literals;
                            std::this_thread::sleep_for(1s);
                            continue;
                        }
                        break;
                    }
                    std::string operation2{};
                    while (true) {
                        std::cout << "Please choose an operation:\n"
                                     "1-Create your own password\n"
                                     "2-Generate a password" << std::endl;
                        std::cin >> operation2;
                        try {
                            if (std::stoi(operation2) != 1 && std::stoi(operation2) != 2) {
                                std::cerr << "Operation doesn't exist! Please choose operation from given options."
                                          << std::endl;
                                using namespace std::chrono_literals;
                                std::this_thread::sleep_for(1s);
                                continue;
                            }
                            break;
                        } catch (const std::invalid_argument &e) {
                            std::cerr << "Invalid input! Please enter a number." << std::endl;
                            using namespace std::chrono_literals;
                            std::this_thread::sleep_for(1s);
                            continue;
                        }
                    }

                    while (true) {
                        try {
                            if (std::stoi(operation2) == 1) {
                                while (true) {
                                    std::cout << "Please enter your password:" << std::endl;
                                    std::cin >> password;

                                    if (!manager.password_control(password)) {
                                        std::cout << "Would you like to edit your password?" << std::endl;
                                        std::string command{};
                                        std::cout << "1-Yes\n"
                                                     "2-No" << std::endl;
                                        std::cin >> command;

                                        try {
                                            if (std::stoi(command) == 1) {
                                                continue;
                                            } else if (std::stoi(command) != 1 && std::stoi(command) != 2) {
                                                std::cerr
                                                        << "Operation doesn't exist! Please choose operation from given options."
                                                        << std::endl;
                                                using namespace std::chrono_literals;
                                                std::this_thread::sleep_for(1s);
                                                continue;
                                            }
                                        } catch (const std::invalid_argument &e) {
                                            std::cerr << "Invalid input! Please enter a number." << std::endl;
                                            using namespace std::chrono_literals;
                                            std::this_thread::sleep_for(1s);
                                            continue;
                                        }
                                    }
                                    break;
                                }
                                using namespace std::chrono_literals;
                                std::this_thread::sleep_for(1s);
                                manager.add_password({title, password, category});
                                operations.write_password({title, password, category});
                                std::cout << "The password is added." << std::endl;
                                std::this_thread::sleep_for(1s);
                            }

                            if (std::stoi(operation2) == 2) {
                                std::string command{};
                                std::string length{};
                                bool include_uppercase = false;
                                bool include_lowercase = false;
                                bool include_special_character = false;
                                bool include_number = false;


                                while (true) {
                                    std::cout << "How many characters?" << std::endl;
                                    std::cin >> length;
                                    try {
                                        if (std::stoi(length) <= 6) {
                                            std::cerr << "Password length must be between 6 and 16."
                                                      << std::endl;
                                            using namespace std::chrono_literals;
                                            std::this_thread::sleep_for(1s);
                                            continue;
                                        }
                                        break;
                                    } catch (const std::invalid_argument &e) {
                                        std::cerr << "Invalid input! Please enter number." << std::endl;
                                        using namespace std::chrono_literals;
                                        std::this_thread::sleep_for(1s);
                                        continue;
                                    }
                                }
                                while (true) {
                                    std::cout << "Uppercase letter?" << std::endl;
                                    std::cout << "1-Yes\n"
                                                 "2-No" << std::endl;
                                    std::cin >> command;
                                    try {
                                        if (std::stoi(command) == 1) {
                                            include_uppercase = true;
                                        } else if (std::stoi(command) == 2) {
                                            include_uppercase = false;
                                        } else {
                                            std::cerr
                                                    << "Operation doesn't exist! Please choose operation from given options."
                                                    << std::endl;
                                            using namespace std::chrono_literals;
                                            std::this_thread::sleep_for(1s);
                                            continue;
                                        }
                                        break;
                                    } catch (const std::invalid_argument &e) {
                                        std::cerr << "Invalid input! Please enter number." << std::endl;
                                        using namespace std::chrono_literals;
                                        std::this_thread::sleep_for(1s);
                                        continue;
                                    }

                                }
                                while (true) {
                                    std::cout << "Lowercase letter?" << std::endl;
                                    std::cout << "1-Yes\n"
                                                 "2-No" << std::endl;
                                    std::cin >> command;
                                    try {
                                        if (std::stoi(command) == 1) {
                                            include_lowercase = true;
                                        } else if (std::stoi(command) == 2) {
                                            include_lowercase = false;
                                        } else {
                                            std::cerr
                                                    << "Operation doesn't exist! Please choose operation from given options."
                                                    << std::endl;
                                            using namespace std::chrono_literals;
                                            std::this_thread::sleep_for(1s);
                                            continue;
                                        }
                                        break;
                                    } catch (const std::invalid_argument &e) {
                                        std::cerr << "Invalid input! Please enter a number." << std::endl;
                                        using namespace std::chrono_literals;
                                        std::this_thread::sleep_for(1s);
                                        continue;
                                    }
                                }
                                while (true) {
                                    std::cout << "Special character?" << std::endl;
                                    std::cout << "1-Yes\n"
                                                 "2-No" << std::endl;
                                    std::cin >> command;
                                    try {
                                        if (std::stoi(command) == 1) {
                                            include_special_character = true;
                                        } else if (std::stoi(command) == 2) {
                                            include_special_character = false;
                                        } else {
                                            std::cerr
                                                    << "Operation doesn't exist! Please choose operation from given options."
                                                    << std::endl;
                                            using namespace std::chrono_literals;
                                            std::this_thread::sleep_for(1s);
                                            continue;
                                        }
                                        break;
                                    } catch (const std::invalid_argument &e) {
                                        std::cerr << "Invalid input! Please enter a number." << std::endl;
                                        using namespace std::chrono_literals;
                                        std::this_thread::sleep_for(1s);
                                        continue;
                                    }
                                }
                                while (true) {
                                    std::cout << "Number?" << std::endl;
                                    std::cout << "1-Yes\n"
                                                 "2-No" << std::endl;
                                    std::cin >> command;
                                    try {
                                        if (std::stoi(command) == 1) {
                                            include_number = true;
                                        } else if (std::stoi(command) == 2) {
                                            include_number = false;
                                        } else {
                                            std::cerr
                                                    << "Operation doesn't exist! Please choose operation from given options."
                                                    << std::endl;
                                            using namespace std::chrono_literals;
                                            std::this_thread::sleep_for(1s);
                                            continue;
                                        }
                                        break;
                                    } catch (const std::invalid_argument &e) {
                                        std::cerr << "Invalid input! Please enter number." << std::endl;
                                        using namespace std::chrono_literals;
                                        std::this_thread::sleep_for(1s);
                                        continue;
                                    }
                                }

                                if (!(include_lowercase || include_uppercase || include_special_character ||
                                      include_number)) {
                                    std::cerr << "Please choose at least 1 criteria." << std::endl;
                                    using namespace std::chrono_literals;
                                    std::this_thread::sleep_for(1s);
                                    continue;
                                }

                                while (true) {
                                    password = manager.generate_password(std::stoi(length), include_uppercase,
                                                                         include_lowercase,
                                                                         include_special_character, include_number);
                                    std::cout << "Generated password: " << password << std::endl;
                                    std::cout << "Would you like to re-generate?" << std::endl;

                                    std::cout << "1-Yes\n"
                                                 "2-No" << std::endl;
                                    std::cin >> command;
                                    try {
                                        if (std::stoi(command) == 1) {
                                            continue;
                                        } else if (std::stoi(command) == 2) {
                                            break;
                                        } else {
                                            std::cerr
                                                    << "Operation doesn't exist! Please choose operation from given options."
                                                    << std::endl;
                                            using namespace std::chrono_literals;
                                            std::this_thread::sleep_for(1s);
                                            continue;
                                        }
                                    } catch (const std::invalid_argument &e) {
                                        std::cerr << "Invalid input! Please enter a number." << std::endl;
                                        using namespace std::chrono_literals;
                                        std::this_thread::sleep_for(1s);
                                        continue;
                                    }
                                }

                                manager.add_password({title, password, category});
                                operations.write_password({title, password, category});
                                std::cout << "Password is added." << std::endl;
                                using namespace std::chrono_literals;
                                std::this_thread::sleep_for(1s);
                            }
                            break;
                        } catch (const std::invalid_argument &e) {
                            std::cerr << "Invalid input! Please enter a number." << std::endl;
                            continue;
                        } catch (const PasswordLengthException &e) {
                            std::cerr << e.what() << std::endl;
                            using namespace std::chrono_literals;
                            std::this_thread::sleep_for(1s);
                            continue;
                        } catch (const PasswordExistException &e) {
                            std::cerr << e.what() << std::endl;
                            using namespace std::chrono_literals;
                            std::this_thread::sleep_for(1s);
                            continue;
                        }
                    }
                }
                    break;
                case 3: {
                    std::string parameter1{};
                    std::string parameter2{};
                    while (true) {
                        std::cout << "Please enter 2 parameters from list to sort\n"
                                     "[category,title,password]" << std::endl;
                        std::cin >> parameter1 >> parameter2;
                        if (!manager.sort_passwords(parameter1, parameter2)) {
                            std::cerr << "Parameter is not in the list, please choose from the given list."
                                      << std::endl;
                            continue;
                        } else break;
                    }
                    manager.show_passwords();
                }
                    break;
                case 4: {
                    if (manager.get_passwordList().empty()) {
                        std::cerr << "Password list is empty!\n"
                                     "Please add password before editing password\n"
                                     "You are being forwarded to the menu..." << std::endl;
                        using namespace std::chrono_literals;
                        std::this_thread::sleep_for(1s);
                        continue;
                    }
                    std::string password{};
                    std::string new_password{};
                    bool valid_password{false};
                    manager.show_passwords();
                    std::cout << "Please enter a password to edit:" << std::endl;
                    std::cin >> password;
                    std::cout << manager.select_password(password) << std::endl;

                    while (!valid_password) {
                        std::cout << "Please enter your new password:" << std::endl;
                        std::cin >> new_password;

                        try {
                            if (!manager.password_control(new_password)) {
                                std::cout << "Would you like to edit your password?" << std::endl;
                                int command{};
                                std::cout << "1-Yes\n"
                                             "2-No" << std::endl;
                                std::cin >> command;

                                if (command == 1)
                                    continue;
                            }
                            valid_password = true;
                            using namespace std::chrono_literals;
                            std::this_thread::sleep_for(1s);
                        } catch (const PasswordLengthException &e) {
                            std::cerr << e.what() << std::endl;
                            using namespace std::chrono_literals;
                            std::this_thread::sleep_for(1s);
                            continue;
                        }
                    }
                    manager.edit_password(password, new_password);
                    operations.write_all_passwords(manager.get_passwordList());
                    std::cout << "Your new password: " << manager.select_password(new_password).get_password() << std::endl;
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(1s);
                }
                    break;

                case 5:
                    if (manager.get_passwordList().empty()) {
                        std::cerr << "Password list is empty.\n"
                                     "Please add password before deleting password.\n"
                                     "You are being Forwarded to the menu..." << std::endl;
                        using namespace std::chrono_literals;
                        std::this_thread::sleep_for(1s);
                        continue;
                    }
                    manager.show_passwords();
                    manager.delete_password();
                    operations.write_all_passwords(manager.get_passwordList());
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(1s);
                    break;
                case 6: {
                    std::string parameter{};
                    std::cout << "Please input parameter to search password:" << std::endl;
                    std::cin >> parameter;
                    if (!(manager.search_password(parameter))) {
                        std::cerr << "Password is not found." << std::endl;
                        using namespace std::chrono_literals;
                        std::this_thread::sleep_for(1s);
                    }
                }
                    break;
                case 7: {
                    std::cin.ignore();
                    std::string category{};
                    while (true) {
                        manager.show_categories();
                        std::cout << "Please enter category name to delete:" << std::endl;
                        std::getline(std::cin, category);

                        if (manager.delete_category(category)) {
                            operations.write_all_passwords(manager.get_passwordList());
                            std::cout << category << " deleted" << std::endl;
                            using namespace std::chrono_literals;
                            std::this_thread::sleep_for(1s);
                            break;
                        } else {
                            std::cerr << "Category doesn't exist, please choose category from category list."
                                      << std::endl;
                            using namespace std::chrono_literals;
                            std::this_thread::sleep_for(1s);
                            continue;
                        }

                    }

                } break;
                case 8:
                    if (manager.get_passwordList().empty()) {
                        std::cerr << "Password list is empty!\n"
                                     "Please add password before printing passwords\n"
                                     "You are being forwarded to the menu..." << std::endl;
                        using namespace std::chrono_literals;
                        std::this_thread::sleep_for(1s);
                        continue;
                    }
                    manager.show_passwords();
                    break;
                case 9:
                    return 0;
                default:
                    std::cerr << "Operation doesn't exist! Please choose operation from given options."
                              << std::endl;
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(1s);
                    continue;
            }
        } catch (const std::invalid_argument &e) {
            std::cerr << "Invalid input! Please enter a number from given menu. " << std::endl;
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1s);
            continue;
        } catch (const CategoryExistException &e) {
            std::cerr << e.what() << std::endl;
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1s);
            continue;
        } catch (const PasswordExistException &e) {
            std::cerr << e.what() << std::endl;
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1s);
            continue;
        } catch (const PasswordDoesntExistException &e){
            std::cerr << e.what() << std::endl;
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1s);
            continue;
        }
    }
}
