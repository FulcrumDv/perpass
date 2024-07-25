#include "service.h"
#include <iostream>
#include <limits>

Service::Service() : pm(), display(), filename("passwords.txt") {
    Utilities util;
    key = util.masterKeyCheck();
    if (pm.loadPasswordsFromFile(filename, key)) {
        std::cout << "Passwords loaded successfully!" << std::endl;
    } else {
        std::cout << "No existing passwords found or unable to load passwords." << std::endl;
    }
    display.setPassManager(&pm);
    std::cout << "Debug: PassManager set in Display" << std::endl;
}

void Service::run() {
    bool continueRunning = true;
    while (continueRunning) {
        display.menu();
        bool accountModified = display.selection(filename, key);
        if (accountModified) {
            pm.savePasswordToFile(filename, key);
            std::cout << "Changes saved successfully!" << std::endl;
        }
        if (!continueRunning) {
            break;
        }
        char choice;
        std::cout << "Do you want to perform another operation? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continueRunning = (choice == 'y' || choice == 'Y');
    }
    std::cout << "Exiting program. Goodbye!" << std::endl;
}
