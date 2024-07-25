#pragma once

#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
#include <string>

class Utilities {
public:
  std::string masterKeyCheck();
  std::string generateMasterKey();
  std::string generatePassword();
  void allExit();
};

#endif // !UTILITIES_H
