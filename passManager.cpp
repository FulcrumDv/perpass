#include "passManager.h"
#include "encryption.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <string>
#include <vector>
#include <algorithm>

void PassManager::savePasswordToFile(const std::string &filename,
                                     const std::string &masterPass) {
  Encryption enc;
  std::ofstream file(filename, std::ios::binary | std::ios::trunc);
  if (!file) {
    std::cerr << "Error opening file for writing: " << filename << std::endl;
    return;
  }
  for (const auto &[website, accountList] : accounts) {
    for (const auto &account : accountList) {
      std::string beforeEnc =
          website + "|" + account.username + "|" + account.password;
      std::vector<unsigned char> encrypted =
          enc.encryptLine(beforeEnc, masterPass);

      // Write the size of the encrypted data first
      uint32_t size = encrypted.size();
      file.write(reinterpret_cast<const char *>(&size), sizeof(size));

      // Then write the encrypted data
      file.write(reinterpret_cast<const char *>(encrypted.data()),
                 encrypted.size());
    }
  }
  file.close();
}

bool PassManager::loadPasswordsFromFile(const std::string &filename, const std::string &masterKey) {
    Encryption enc;
     std::ifstream file(filename, std::ios::binary);
     if (!file) {
         std::cerr << "Error opening file for reading: " << filename << std::endl;
         return false;
     }
     accounts.clear();

     while (file) {
         uint32_t size;
         file.read(reinterpret_cast<char *>(&size), sizeof(size));
         if (file.eof()) break;

         std::vector<unsigned char> encryptedData(size);
         file.read(reinterpret_cast<char *>(encryptedData.data()), size);

         try {
             std::string decryptedLine = enc.decryptLine(encryptedData, masterKey);
             std::istringstream iss(decryptedLine);
             std::string website, username, password;

             if (std::getline(iss, website, '|') && std::getline(iss, username, '|') && std::getline(iss, password)) {
                 accounts[website].push_back({username, password});
             } else {
                 std::cerr << "Invalid line format: " << decryptedLine << std::endl;
             }
         } catch (const std::exception &e) {
             std::cerr << "Error decrypting entry: " << e.what() << std::endl;
         }
     }
     file.close();
     std::cout << "Loaded " << accounts.size() << " websites from file." << std::endl;
     return !accounts.empty();
 }

 void PassManager::addAccount(const std::string &website,
                              const std::string &username,
                              const std::string &pass) {
   std::cout << "Adding account for website: " << website << std::endl;
   std::cout << "Username: " << username << std::endl;
   std::cout << "Password: " << pass << std::endl;

   accounts[website].push_back({username, pass});

   std::cout << "Account added successfully. Total accounts for " << website << ": " << accounts[website].size() << std::endl;
 }
void PassManager::removePass(const std::string &website, const std::string &username) {
  auto iter = accounts.find(website);
  if (iter != accounts.end()) {
    auto &accountList = iter->second;
    accountList.erase(
      std::remove_if(accountList.begin(), accountList.end(),
        [&username](const accountInfo &account) {
          return account.username == username;
        }),
      accountList.end()
    );
  }else{
      std::cout << "No such website exists" << std::endl;
  }
}

bool PassManager::editPass(const std::string &website,
                           const std::string &username, std::string &pass,
                           std::string &newPass) {
  auto iter = accounts.find(website);
  if (iter != accounts.end()) {
    auto &accountsList = iter->second;
    for (auto &account : accountsList) {
      if (account.username == username && account.password == pass) {
        account.password = newPass;
        return true;
      }
    }
  }
  return false;
}

void PassManager::viewPass(const std::string &website) {
  auto iter = accounts.find(website);
  if (iter != accounts.end()) {
    for (const auto &account : iter->second) {
      std::cout << "Website: " << website << std::endl;
      std::cout << "Username: " << account.username << std::endl;
      std::cout << "Password: " << account.password << std::endl;
      std::cout << std::endl;
    }
  }else{
        std::cout << "No such website exists" << std::endl;
  }
}

void PassManager::viewAllPasses(const std::string& filename) {
        std::cout << "Number of websites: " << accounts.size() << std::endl;
        if (accounts.empty()) {
            std::cout << "No accounts found." << std::endl;
            return;
        }

        for (const auto& [website, accountList] : accounts) {
            for (const auto& account : accountList) {
                std::cout << "Website: " << website << std::endl;
                std::cout << "Username: " << account.username << std::endl;
                std::cout << "Password: " << account.password << std::endl;
                std::cout << std::endl;
            }
        }
    }
