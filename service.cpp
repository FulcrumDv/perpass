#include "service.h"
#include <iostream>

Service::Service() : pm(), display(pm), filename("passwords.txt") {
    Utilities util;
    key = util.masterKeyCheck();
    if (pm.loadPasswordsFromFile(filename, key)) {
        std::cout << "Passwords loaded successfully!" << std::endl;
    } else {
        std::cout << "No existing passwords found or unable to load passwords." << std::endl;
    }
}

void Service::run() {
    bool continueRunning = true;
    while (continueRunning) {
        display.menu();
        continueRunning = display.selection(filename, key);
        if (continueRunning) {
            // After each operation, save the passwords
            pm.savePasswordToFile(filename, key);
        }
    }
    std::cout << "Exiting program. Goodbye!" << std::endl;
}
