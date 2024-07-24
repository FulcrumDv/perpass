#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

class Display {
public:
  void menu();
  void selection(const std::string &filename);
  void callASCIIScript();
};

#endif
