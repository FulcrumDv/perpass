#pragma once

#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>

class Utilities {
public:
  bool masterKeyCheck();
  std::string generateMasterKey();
  std::string generatePassword();
  void allExit();
};

#endif // !UTILITIES_H
