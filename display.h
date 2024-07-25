#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include "passManager.h"
#include "utilities.h"

class Display {
private:
    PassManager* pm;
    Utilities util;  // Changed to object instead of pointer

public:
    Display() : pm(nullptr) {}
    void setPassManager(PassManager* manager);
    void menu();
    bool selection(const std::string &filename, const std::string &masterKey);
    void callASCIIScript();
    void run(const std::string &filename, const std::string &masterKey);
};

#endif // DISPLAY_H
