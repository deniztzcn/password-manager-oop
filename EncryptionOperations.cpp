//
// Created by tezca on 1.06.2023.
//

#include <fstream>
#include "EncryptionOperations.h"
#include <ctime>
#include <sstream>
#include <filesystem>

void EncryptionOperations::write_password(const PasswordEntry &password) {
    auto ostream = std::ofstream(source_file, std::fstream::app);
    ostream << encrypt(password.get_title()) << '\n'
            << encrypt(password.get_password()) << '\n' << encrypt(password.get_category())
            << '\n';

}

std::string EncryptionOperations::encrypt(const std::string &to_encrypt) {
    std::string encrypted{};
    for (int i = 0; i < to_encrypt.length(); i++) {
        encrypted += (char) (to_encrypt[i] + encryption_key[i % encryption_key.length()]);
    }
    return encrypted;
}

std::string EncryptionOperations::decrypt(const std::string &to_decrypt) {
    std::string decrypted {};
    for (int i = 0; i < to_decrypt.length(); i++) {
        decrypted += (char) (to_decrypt[i] - encryption_key[i % encryption_key.length()]);
    }
    return decrypted;
}

void EncryptionOperations::write_all_passwords(const std::vector<PasswordEntry> &passwords) {
    auto ostream = std::ofstream(source_file);

    for (const auto &password: passwords) {
        ostream << encrypt(password.get_title()) << '\n'
                << encrypt(password.get_password()) << '\n' << encrypt(password.get_category())
                << '\n';
    }
}
/*
void EncryptionOperations::write_timestamp(const std::vector<PasswordEntry> &passwords) {
    std::string hour {};
    std::string day {};
    std::string month {};
    std::string year {};
    std::string skip {};
    std::string line {};
    int line_number {1};
    auto ifstream = std::ifstream (source_file);
    auto ostream = std::ofstream("temp.txt");
    std::time_t current_time = std::time(nullptr);
    std::string timestamp = std::ctime(&current_time);
    auto sstream = std::stringstream(timestamp);
    sstream >> skip >> day >> month >> hour >> year;
    std::vector<std::string> hours {};
    std::vector<std::string> days {};
    std::vector<std::string> months {};
    std::vector<std::string> years {};

    while(std::getline(ifstream,line,',')){
        if(line_number == 1){
            hours.push_back(line);
        } else if(line_number == 2){
            days.push_back(line);
        } else if(line_number == 3){
            months.push_back(line);
        } else if(line_number == 4){
            years.push_back(line);
        }
        line_number++;
    }
    line_number = 1;
    hours.push_back(hour);
    days.push_back(day);
    months.push_back(month);
    years.push_back(year);

    while(std::getline(ifstream,line,',')){
        if(line_number == 1){
            for(const auto h: hours){
                ostream << h << ',';
            }
        } else if(line_number == 2){
            days.push_back(line);
        } else if(line_number == 3){
            months.push_back(line);
        } else if(line_number == 4){
            years.push_back(line);
        }
        line_number++;
    }
    ifstream.close();
    ostream.close();

    ostream.open(source_file);
    ifstream.open("temp.txt");

    ostream << ifstream.rdbuf();
    std::filesystem::remove("temp.txt");

}
 */
