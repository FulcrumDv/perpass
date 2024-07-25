#include "service.h"
#include <iostream>
#include <limits>

Service::Service() : pm(), display(), filename("./pass/passwords.txt") {
    Utilities util;
    key = util.masterKeyCheck();
    pm.loadPasswordsFromFile(filename, key);
    display.setPassManager(&pm);
}

void Service::run() {
    bool continueRunning = true;
    while (continueRunning) {
        display.menu();

        bool accountModified = display.selection(filename, key);
        if (accountModified) {
            pm.savePasswordToFile(filename, key);
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
