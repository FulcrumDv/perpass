#include "utilities.h"
#include <random>
#include <string>

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
        std::cout << "Have you got your master Key? If not you can generate one!\n";
        std::cout << "Yes I have it - (Y)\n";
        std::cout << "No, generate one for me - (N)\n";
        std::cout << "Exit - (Q)\n";
        std::cout << "Your choice: ";

        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "No input received. Please enter Y, N, or Q.\n";
            continue;
        }

        char choice = std::tolower(input[0]);

        switch (choice) {
            case 'y':
                std::cout << "Enter master key: ";
                std::getline(std::cin, key);
                if (key.empty()) {
                    std::cout << "\nMaster key cannot be empty. Please try again.\n";
                    continue;
                }
                validInput = true;
                break;
            case 'n':
                std::cout << "\n\n\n\n\n\n\n";
                key = generateMasterKey();
                validInput = true;
                std::cout << key;
                std::cout << "\n\n\n";

                std::cout << "Please save this key in a safe place. You will need it to decrypt your files.\n\n";
                masterKeyCheck();
                break;
            case 'q':
                allExit();
                break;
            default:
                std::cout << "Invalid choice. Please enter Y, N, or Q.\n";
                break;
        }
    }
    return key;
}

void Utilities::allExit() {
  std::cout << "Exiting...";
  exit(0);
}
