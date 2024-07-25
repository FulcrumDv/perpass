#pragma once

#include <cstddef>
#ifndef PASSMANAGER_H
#define PASSMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>

class PassManager {
private:
  // struct to hold account info
  struct accountInfo {
    std::string username;
    std::string password;
  };

  // map of websites to a vector of accountInfo
  std::unordered_map<std::string, std::vector<accountInfo>> accounts;

public:
  size_t getAccountSize();
  void savePasswordToFile(const std::string &filename, const std::string &masterPass);
  bool  loadPasswordsFromFile(const std::string &filename, const std::string &masterPass);
  void addAccount(const std::string &website, const std::string &username,
               const std::string &pass);
  void removePass(const std::string &website, const std::string &username);
  bool editPass(const std::string &website, const std::string &username,
                std::string &pass, std::string &newPass);
  void viewPass(const std::string &website);
  void viewAllPasses(const std::string &filename);
};

#endif // !PASSMANAGER_
