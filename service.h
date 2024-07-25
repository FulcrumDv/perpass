#pragma once

#ifndef SERVICE_H
#define SERVICE_H

#include "passManager.h"
#include "display.h"
#include "utilities.h"
#include <string>

class Service {
private:
    PassManager pm;
    std::string filename;
    std::string key;
    Display display;

public:
    Service();
    void run();
};

#endif // SERVICE_H
