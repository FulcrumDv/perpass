#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

class Display {
public:
    void menu();
    bool selection(const std::string &filename, const std::string &masterKey);
    void callASCIIScript();
    void run(const std::string &filename, const std::string &masterKey);
};

#endif // DISPLAY_H
