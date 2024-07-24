#include "display.h"
#include "passManager.h"
#include "utilities.h"
#include <iostream>
#include <limits>
#include <string>

void Display::menu() {
// calls python script to display ASCII art
  callASCIIScript();
  std::cout << "Please select one of the following: " << std::endl;
  std::cout << "1. View all Accounts" << std::endl;
  std::cout << "2. Add a new Account" << std::endl;
  std::cout << "3. Edit current Account" << std::endl;
  std::cout << "4. Delete an Account" << std::endl;
  std::cout << "5. Search for an Account" << std::endl;
  std::cout << "6. Save and Exit" << std::endl;
}

void Display::selection(const std::string &filename, const std::string &masterKey) {
    PassManager pm;
    Utilities util;
    int choice;

    // Clear any leftover characters in the input buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!(std::cin >> choice)) {
        std::cout << "Invalid input. Please enter a number." << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
    case 1:
        pm.viewAllPasses(filename);
        break;
    case 2:
    {
        std::string website, username, password;
        std::cout << "Please enter the following:\n";
        std::cout << "Website: ";
        std::getline(std::cin, website);
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::cout << "Password: ";
        std::getline(std::cin, password);
        pm.addAccount(website, username, password);
        std::cout << "Account added successfully!" << std::endl;
        break;
    }
    case 3:
    {
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
        if (pm.editPass(website, username, currentPassword, newPassword)) {
            std::cout << "Password updated successfully!" << std::endl;
        } else {
            std::cout << "Failed to update password. Please check your inputs." << std::endl;
        }
        break;
    }
    case 4:
    {
        std::string website, username;
        std::cout << "Please enter the following:\n";
        std::cout << "Website: ";
        std::getline(std::cin, website);
        std::cout << "Username: ";
        std::getline(std::cin, username);
        pm.removePass(website, username);
        std::cout << "Account removed successfully!" << std::endl;
        break;
    }
    case 5:
    {
        std::string website;
        std::cout << "Please enter the following:\n";
        std::cout << "Website: ";
        std::getline(std::cin, website);
        pm.viewPass(website);
        break;
    }
    case 6:
        pm.savePasswordToFile(filename, masterKey);
        std::cout << "Passwords saved successfully!" << std::endl;
        break;
    default:
        std::cout << "Invalid selection, please try again" << std::endl;
        break;
    }
}
