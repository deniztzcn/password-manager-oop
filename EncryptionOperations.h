//
// Created by tezca on 1.06.2023.
//

#ifndef PASSWORDMANAGER_ENCRYPTIONOPERATIONS_H
#define PASSWORDMANAGER_ENCRYPTIONOPERATIONS_H


#include <string>
#include <vector>
#include "PasswordEntry.h"

/**
 * @brief The EncryptionOperations class provides functionality for encrypting and decrypting passwords.
 *
 * The EncryptionOperations class is responsible for handling encryption and decryption operations on passwords.
 * It uses an encryption key and a source file to perform these operations.
 */
class EncryptionOperations {
private:
    std::string encryption_key;
    std::string source_file;
public:
    /**
     * @brief Constructs an EncryptionOperations object with the specified source file and encryption key.
     *
     * @param source The source file for reading and writing passwords.
     * @param key The encryption key used for encryption and decryption operations.
     */
    EncryptionOperations(const std::string &source, const std::string &key)
    : source_file {source}, encryption_key{key}{}
    /**
     * @brief Writes the encrypted password entry to the source file.
     *
     * @param password The password entry to be written.
     */
    void write_password(const PasswordEntry &password);
    /**
     * @brief Encrypts the provided string using the encryption key.
     *
     * @param to_encrypt The string to be encrypted.
     *
     * @return The encrypted string.
     */
    std::string encrypt(const std::string &to_encrypt);
    /**
     * @brief Decrypts the provided string using the encryption key.
     *
     * @param to_decrypt The string to be decrypted.
     *
     * @return The decrypted string.
     */
    std::string decrypt(const std::string &to_decrypt);
    /**
     * @brief Writes all passwords from the provided vector to the source file, encrypting them before writing.
     *
     * @param passwords objects representing the passwords to be written.
     */
    void write_all_passwords(const std::vector<PasswordEntry> &passwords);
    //void write_timestamp(const std::vector<PasswordEntry> &passwords);
};


#endif //PASSWORDMANAGER_ENCRYPTIONOPERATIONS_H
