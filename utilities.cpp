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

bool Utilities::masterKeyCheck() {
  std::cout << "Have you got your master Key? If not you can generate one!";
  std::cout << "Yes I have it - (Y)";
  std::cout << "No, generate one for me - (N)";
  std::cout << "Exit - (Q)";
  char choice;
  std::cin >> choice;
  if (choice == 'Y' || choice == 'y') {
    std::cout << "Enter master key: ";
    std::string key;
    std::cin >> key;
    return true;
  } else if (choice == 'N' || choice == 'n') {
    generateMasterKey();
    masterKeyCheck();
  } else if (choice == 'Q' || choice == 'q') {
    allExit();
  } else {
    std::cout << "Invalid choice, please try again!";
    masterKeyCheck();
  }

  return false;
}

void Utilities::allExit() {
  std::cout << "Exiting...";
  exit(0);
}
