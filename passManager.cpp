#include "passManager.h"
#include "encryption.h"
#include <fstream>
#include <iostream>

void PassManager::savePasswordToFile(const std::string &filename,
                                     const std::string &masterPass) {
  Encryption enc;

  std::ofstream file(filename, std::ios::out | std::ios::app);
  if (!file) {
    std::cerr << "Error opening file for writing:  " << filename << std::endl;
    return;
  }

  for (const auto &[website, accountList] : accounts) {
    // iterate over all accounts for a website
    for (const auto &account : accountList) {
      // account line before encryption
      std::string beforeEnc =
          website + "|" + account.username + "|" + account.password;
      // encrypt account
      std::vector<unsigned char> encrypted =
          enc.encryptLine(beforeEnc, masterPass);

        // write encrypted account to file
      file.write(reinterpret_cast<const char*>(encrypted.data()),
                 encrypted.size());
      file << std::endl;
    }
  }
  file.close();
}

// not implemented
bool PassManager::loadPasswordsFromFile(const std::string &filename,
                                        const std::string &masterPass) {

  return false;
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
void PassManager::viewPass(const std::string &website,
                           const std::string &username) {}
void PassManager::viewAllPasses(const std::string &filename) {}
