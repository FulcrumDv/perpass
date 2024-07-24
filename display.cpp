#include "display.h"
#include "passManager.h"
#include <iostream>

void Display::menu(){
    callASCIIScript();
    std::cout << "Please select one of the following: " << std::endl;
    std::cout << "1. View all Accounts" << std::endl;
    std::cout << "2. Add a new Account" << std::endl;
    std::cout << "3. Edit current Account" << std::endl;
    std::cout << "4. Delete an Account" << std::endl;
    std::cout << "5. Search for an Account" << std::endl;
    std::cout << "6. Generate a master key" << std::endl;
    std::cout << "7. Save and Exit" << std::endl;
}

void Display::selection(const std::string &filename){
    PassManager pm;
    int choice;
    std::string masterKey;
    std::cin >> choice;
    switch(choice){
        case 1:

            std::cout << "Please enter the master key: ";
            pm.viewAllPasses(filename);
            break;
        case 2:
            addAccount();
            break;
        case 3:
            editAccount();
            break;
        case 4:
            deleteAccount();
            break;
        case 5:
            searchAccount();
            break;
        case 6:
            saveAndExit();
            break;
        default:
            std::cout << "Invalid selection, please try again" << std::endl;
            break;
    }
}

void Display::callASCIIScript(){
    std::string command = "python3 ascii_art.py";

    int result = system(command.c_str());
    if(result != 0){
        std::cerr << "Failed to run python script, Error code: " << result << std::endl;
    }

}
