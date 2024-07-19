#pragma once

#ifndef PASSMANAGER_H
#define PASSMANAGER_H

#include <string>

class PassManager
{

public:
    void savePasswordsToFile(const std::string &filename);
    void loadPasswordsFromFile();
    void addPass(const std::string &website, const std::string &username, const std::string &pass);
    void removePass(const std::string &website, const std::string &username);
    void editPass(const std::string &website, const std::string &username, std::string &pass);
    void viewPass(const std::string &website, const std::string &username);
    void viewAllPasses(const std::string &masterPass, const std::string &filename);
};

#endif // !PASSMANAGER_H