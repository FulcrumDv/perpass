#include "utilities.h"
#include <random>
#include <string>
#include <iostream>
#include <iomanip>


std::string Utilities::generateMasterKey() {
  const std::string chars =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  std::random_device re;
  std::mt19937_64 mt(re());
  std::uniform_int_distribution<int> dist(0, chars.size() - 1);

  std::string key;
  for (int i = 0; i < 256; ++i) {
    key += chars[dist(mt)];
  }

  return key;
}


std::string Utilities::masterKeyCheck() {
    std::string key;
    std::string input;
    bool validInput = false;

    while (!validInput) {
        // clear the screen
        std::cout << "\033[2J\033[1;1H";

        std::cout << "\n" << std::setfill('=') << std::setw(50) << "" << std::endl;
        std::cout << std::setfill(' ') << std::setw(30) << "Master Key Setup" << std::endl;
        std::cout << std::setfill('=') << std::setw(50) << "" << std::endl << std::endl;

        std::cout << "Do you have your master key?" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << std::setw(4) << "" << "[Y] Yes, I have it" << std::endl;
        std::cout << std::setw(4) << "" << "[N] No, generate one for me" << std::endl;
        std::cout << std::setw(4) << "" << "[Q] Exit" << std::endl << std::endl;

        std::cout << "Your choice: ";
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "\nNo input received. Please enter Y, N, or Q." << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.get();
            continue;
        }

        char choice = std::tolower(input[0]);
        switch (choice) {
            case 'y':
                std::cout << "\nEnter your master key: ";
                std::getline(std::cin, key);
                if (key.empty()) {
                    std::cout << "\nMaster key cannot be empty. Please try again." << std::endl;
                    std::cout << "Press Enter to continue...";
                    std::cin.get();
                    continue;
                }else if (key.length() != 256) {
                    std::cout << "\nMaster key must be 256 characters long. Please try again." << std::endl;
                    std::cout << "Press Enter to continue...";
                    std::cin.get();
                    continue;
                }
                validInput = true;
                break;
            case 'n':
                key = generateMasterKey();
                std::cout << "\n" << std::setfill('*') << std::setw(50) << "" << std::endl;
                std::cout << "Your new master key is:" << std::endl;
                std::cout << key << std::endl;
                std::cout << std::setfill('*') << std::setw(50) << "" << std::endl << std::endl;
                std::cout << "Please save this key in a secure location." << std::endl;
                std::cout << "You will need it to decrypt your files." << std::endl << std::endl;
                std::cout << "Press Enter to continue...";
                std::cin.get();
                return masterKeyCheck();
            case 'q':
                allExit();
                break;
            default:
                std::cout << "\nInvalid choice. Please enter Y, N, or Q." << std::endl;
                std::cout << "Press Enter to continue...";
                std::cin.get();
                break;
        }
    }
    return key;
}

void Utilities::allExit() {
  std::cout << "Exiting...";
  exit(0);
}
