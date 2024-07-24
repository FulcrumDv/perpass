#pragma once

#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>

class Utilities {
public:
  std::string generateMasterKey();
  std::string generatePassword();
};

#endif // !UTILITIES_H
