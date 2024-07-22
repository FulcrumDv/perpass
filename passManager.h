#pragma once

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
  void savePasswordsToFile(const std::string &filename);
  void loadPasswordsFromFile(const std::string &filename);
  void addPass(const std::string &website, const std::string &username,
               const std::string &pass);
  void removePass(const std::string &website, const std::string &username);
  void editPass(const std::string &website, const std::string &username,
                std::string &pass);
  void viewPass(const std::string &website, const std::string &username);
  void viewAllPasses(const std::string &masterPass,
                     const std::string &filename);
};

#endif // !PASSMANAGER_
