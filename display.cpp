#include "display.h"
#include "passManager.h"
#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include <iomanip>

void Display::callASCIIScript() {
    std::string command = "python3 ascii_art.py";
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Failed to run Python script. Error code: " << result << std::endl;
    }
}

void Display::setPassManager(PassManager* manager) {
    pm = manager;
}

void Display::menu() {
    const int WIDTH = 50;
    const std::string BOLD = "\033[1m";
    const std::string RESET = "\033[0m";
    const std::string BLUE = "\033[34m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";

    // Clear the screen
    std::cout << "\033[2J\033[1;1H";

    std::cout << std::setfill('=') << std::setw(WIDTH) << "" << std::endl;
    std::cout << BOLD << RED << std::setfill(' ') << std::setw((WIDTH + 15) / 2) << "PERPASS MENU" << RESET << std::endl;
    std::cout << std::setfill('=') << std::setw(WIDTH) << "" << std::endl << std::endl;

    std::cout << GREEN << "Successfully loaded " << BOLD << pm->getAccountSize() << RESET << GREEN << " accounts from file." << RESET << "\n\n";

    std::cout << BOLD << "Please select one of the following options:" << RESET << std::endl << std::endl;

    const std::string options[] = {
        "View all Accounts",
        "Add a new Account",
        "Edit current Account",
        "Delete an Account",
        "Search for an Account",
        "Save and Exit"
    };

    for (int i = 0; i < 6; ++i) {
        std::cout << std::setw(4) << "" << BOLD << "[" << (i + 1) << "]" << RESET << " " << options[i] << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::setfill('=') << std::setw(WIDTH) << "" << std::endl;
}

bool Display::selection(const std::string &filename, const std::string &masterKey) {
    int choice;
    bool accountModified = false;
    while (true) {
        std::cout << "Enter your choice: ";
        if (std::cin >> choice) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << std::endl;
            break;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
        }
    }
    switch (choice) {
    case 1:
        pm->viewAllPasses(filename);
        break;
    case 2: {
        std::string website, username, password;
        std::cout << "Please enter the following:\n";
        std::cout << "Website: ";
        std::getline(std::cin, website);
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::cout << "Password: ";
        std::getline(std::cin, password);
        pm->addAccount(website, username, password);
        std::cout << "Account added successfully!" << std::endl;
        accountModified = true;
        break;
    }
    case 3: {
        std::string website, username, currentPassword, newPassword;
        std::cout << "Please enter the following:\n";
        std::cout << "Website: ";
        std::getline(std::cin, website);
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::cout << "Current password: ";
        std::getline(std::cin, currentPassword);
        std::cout << "New password: ";
        std::getline(std::cin, newPassword);
        if (pm->editPass(website, username, currentPassword, newPassword)) {
            std::cout << "Password updated successfully!" << std::endl;
            accountModified = true;
        } else {
            std::cout << "Failed to update password. Please check your inputs." << std::endl;
        }
        break;
    }
    case 4: {
        std::string website, username;
        std::cout << "Please enter the following:\n";
        std::cout << "Website: ";
        std::getline(std::cin, website);
        std::cout << "Username: ";
        std::getline(std::cin, username);
        pm->removePass(website, username);
        std::cout << "Account removed successfully!" << std::endl;
        accountModified = true;
        break;
    }
    case 5: {
        std::string website;
        std::cout << "Please enter the following:\n";
        std::cout << "Website: ";
        std::getline(std::cin, website);
        pm->viewPass(website);
        break;
    }
    case 6:
        std::cout << "Exiting..." << std::endl;
        return false;
    default:
        std::cout << "Invalid selection, please try again" << std::endl;
        break;
    }
    return accountModified;
}
