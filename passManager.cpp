#include "passManager.h"
#include "encryption.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdint.h>

void PassManager::savePasswordToFile(const std::string &filename, const std::string &masterPass) {
    Encryption enc;
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    if (!file) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    for (const auto &[website, accountList] : accounts) {
        for (const auto &account : accountList) {
            std::string beforeEnc = website + "|" + account.username + "|" + account.password;
            std::vector<unsigned char> encrypted = enc.encryptLine(beforeEnc, masterPass);

            // Write the size of the encrypted data first
            uint32_t size = encrypted.size();
            file.write(reinterpret_cast<const char*>(&size), sizeof(size));

            // Then write the encrypted data
            file.write(reinterpret_cast<const char*>(encrypted.data()), encrypted.size());
        }
    }
    file.close();
}

bool PassManager::loadPasswordsFromFile(const std::string &filename, const std::string &masterPass) {
    Encryption enc;
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return false;
    }
    accounts.clear();

    while (file) {
        uint32_t size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (file.eof()) break;

        std::vector<unsigned char> encryptedData(size);
        file.read(reinterpret_cast<char*>(encryptedData.data()), size);

        try {
            std::string decryptedLine = enc.decryptLine(encryptedData, masterPass);
            std::istringstream iss(decryptedLine);
            std::string website, username, password;

            if (std::getline(iss, website, '|') &&
                std::getline(iss, username, '|') &&
                std::getline(iss, password)) {
                accountInfo info{username, password};
                accounts[website].push_back(info);
            } else {
                std::cerr << "Invalid line format: " << decryptedLine << std::endl;
            }
        } catch (const std::exception &e) {
            std::cerr << "Error decrypting entry: " << e.what() << std::endl;
        }
    }
    file.close();
    return true;
}
void PassManager::addAccount(const std::string &website,
                             const std::string &username,
                             const std::string &pass) {
  accounts[website].push_back({username, pass});
}
void PassManager::removePass(const std::string &website,
                             const std::string &username) {}

bool PassManager::editPass(const std::string &website,
                           const std::string &username, std::string &pass,
                           std::string &newPass) {
  return false;
}
void PassManager::viewPass(const std::string &website) {}
void PassManager::viewAllPasses(const std::string &masterPass) {
    for (const auto &[website, accountList] : accounts) {
        for (const auto &account : accountList) {
            std::cout << "Website: " << website << std::endl;
            std::cout << "Username: " << account.username << std::endl;
            std::cout << "Password: " << account.password << std::endl;
            std::cout << std::endl;
        }
    }
}
